#include "simmodule.h"
#include "parammanager.h"
#include "globaldata.h"
#include "zss_cmd.pb.h"
#include "grSim_Packet.pb.h"
#include "messageinfo.h"
#include "staticparams.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <geometry.h>
#include <qdebug.h>

namespace ZSS {
namespace {
bool trans_dribble(double dribble) {
    return dribble>1;
}
double trans_length(double v) {
    return v / 100.0;
}
double trans_vr(double v) {
    return v;/// 40.0; from angel to 1/40 rad
}
std::thread* blueReceiveThread = nullptr;
std::thread* yellowReceiveThread = nullptr;

grSim_Packet grsim_packet;
grSim_Commands *grsim_commands;
grSim_Robot_Command *grsim_robots[PARAM::ROBOTNUM];

}
SimModule::SimModule(QObject *parent) : QObject(parent) {
    grsim_commands = grsim_packet.mutable_commands();
    for (int i = 0; i < PARAM::ROBOTNUM; i++) {
        grsim_robots[i] = grsim_commands->add_robot_commands();
    }
    for (int i = 0; i < PARAM::ROBOTNUM; i++) {
        grsim_robots[i]->set_id(i);
        grsim_robots[i]->set_kickspeedx(0);
        grsim_robots[i]->set_kickspeedz(0);
        grsim_robots[i]->set_velnormal(0);
        grsim_robots[i]->set_veltangent(0);
        grsim_robots[i]->set_velangular(0);
        grsim_robots[i]->set_spinner(false);
        grsim_robots[i]->set_wheelsspeed(false);
    }
    for(int i = 0; i < PARAM::TEAMS; i++) {
        if(connectSim(i)){
            switch (i) {
            case 0:
                blueReceiveThread = new std::thread([=] {readBlueData();});
                blueReceiveThread->detach();
                break;
            case 1:
                yellowReceiveThread = new std::thread([=] {readYellowData();});
                yellowReceiveThread->detach();
                break;
            }
        }
    }
}

SimModule::~SimModule() {
    yellowReceiveSocket.abort();
    blueReceiveSocket.abort();
}

bool SimModule::connectSim(bool color) {
    if(color) {
        if(yellowReceiveSocket.bind(QHostAddress::AnyIPv4, ZSS::Sim::YELLOW_STATUS_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
            qDebug() << "Yellow connect successfully!!!";
            return true;
        }
        return false;
    }
    if(blueReceiveSocket.bind(QHostAddress::AnyIPv4, ZSS::Sim::BLUE_STATUS_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "Blue connect successfully!!!";
        return true;
    }
    return false;
}

bool SimModule::disconnectSim(bool color) {
    if(color) {
        yellowReceiveSocket.disconnectFromHost();
    } else {
        blueReceiveSocket.disconnectFromHost();
    }
    return true;
}

void SimModule::readBlueData() {
     qDebug() << "Reading Blue Data!";
    QByteArray datagram;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        while(blueReceiveSocket.state() == QUdpSocket::BoundState && blueReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;
            datagram.resize(blueReceiveSocket.pendingDatagramSize());
            blueReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());

            robotInfoMutex.lock();
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::instance()->robotInformation[PARAM::BLUE][id].infrared = infrared;
                GlobalData::instance()->robotInformation[PARAM::BLUE][id].flat = isFlatKick;
                GlobalData::instance()->robotInformation[PARAM::BLUE][id].chip = isChipKick;
//                qDebug() << "Blue id: " << id << "  infrared: " << infrared << "  flat: " << isFlatKick << "  chip: " << isChipKick;
                emit receiveSimInfo(PARAM::BLUE, id);
            }
            robotInfoMutex.unlock();
        }
    }
}

void SimModule::readYellowData() {
     qDebug() << "Reading Yellow Data!";
    QByteArray datagram;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        while(yellowReceiveSocket.state() == QUdpSocket::BoundState && yellowReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;       
            datagram.resize(yellowReceiveSocket.pendingDatagramSize());
            yellowReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());
            robotInfoMutex.lock();
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::instance()->robotInformation[PARAM::YELLOW][id].infrared = infrared;
                GlobalData::instance()->robotInformation[PARAM::YELLOW][id].flat = isFlatKick;
                GlobalData::instance()->robotInformation[PARAM::YELLOW][id].chip = isChipKick;
    //            qDebug() << "Yellow id: " << id << "  infrared: " << infrared << "  flat: " << isFlatKick << "  chip: " << isChipKick;
                emit receiveSimInfo(PARAM::YELLOW, id);
            }
            robotInfoMutex.unlock();
        }
    }
}

void SimModule::sendSim(int t, ZSS::Protocol::Robots_Command& command) {
    grsim_commands->set_timestamp(0);
    if (t == 0) {
        grsim_commands->set_isteamyellow(false);
    } else if (t == 1) {
        grsim_commands->set_isteamyellow(true);
    } else {
        qDebug() << "Team ERROR in Simmodule !";
    }
    int command_size = command.command_size();
    for (int i = 0; i < command_size; i++) {
        auto commands = command.command(i);
        auto id = commands.robot_id();
        grsim_robots[id]->set_id(id);
        grsim_robots[id]->set_wheelsspeed(false);
        //set flatkick or chipk    ick
        if (!commands.kick()) {
            grsim_robots[id]->set_kickspeedz(0);
            grsim_robots[id]->set_kickspeedx(trans_length(commands.power()));
        } else {
            double radian = ZSS::Sim::CHIP_ANGLE * ZSS::Sim::PI / 180.0;
            double vx = sqrt(trans_length(commands.power()) * ZSS::Sim::G / 2.0 / tan(radian));
            double vz = vx * tan(radian);
            grsim_robots[id]->set_kickspeedz(vx);
            grsim_robots[id]->set_kickspeedx(vz);
        }
        //set velocity and dribble
        double vx = commands.velocity_x();
        double vy = commands.velocity_y();
        double vr = commands.velocity_r();
        double dt = 1. / Athena::FRAME_RATE;
        double theta = - vr * dt;
        CVector v(vx, vy);
        v = v.rotate(theta);
        if (fabs(theta) > 0.00001) {
            //            if (i==0) cout << theta << " " <<vx << " "<< vy << " ";
            v = v * theta / (2 * sin(theta / 2));
            vx = v.x();
            vy = v.y();
            //            if (i==0) cout << vx << " "<< vy << " " << endl;
        }

        grsim_robots[id]->set_veltangent(trans_length(vx));
        grsim_robots[id]->set_velnormal(-trans_length(vy));
        grsim_robots[id]->set_velangular(-trans_vr(vr));
        grsim_robots[id]->set_spinner(trans_dribble(commands.dribbler_spin()));
    }
    int size = grsim_packet.ByteSize();
    QByteArray data(size, 0);
    grsim_packet.SerializeToArray(data.data(), data.size());
    command_socket.writeDatagram(data, size, QHostAddress(ZSS::LOCAL_ADDRESS), ZSS::Athena::SIM_SEND);
    for (int i = 0; i < PARAM::ROBOTNUM; i++) {
        grsim_robots[i]->set_id(i);
        grsim_robots[i]->set_kickspeedx(0);
        grsim_robots[i]->set_kickspeedz(0);
        grsim_robots[i]->set_velnormal(0);
        grsim_robots[i]->set_veltangent(0);
        grsim_robots[i]->set_velangular(0);
        grsim_robots[i]->set_spinner(false);
        grsim_robots[i]->set_wheelsspeed(false);
    }
}

}

