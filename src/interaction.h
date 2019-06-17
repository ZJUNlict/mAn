#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include <QObject>
#include "visionmodule.h"
#include "staticparams.h"
#include "field.h"
#include "dealball.h"
#include "communicator.h"
class Interaction : public QObject {
    Q_OBJECT
  public:
    explicit Interaction(QObject *parent = nullptr);
    Q_INVOKABLE void setIfEdgeTest(bool);
    Q_INVOKABLE void showIfEdgeTest();
    Q_INVOKABLE bool controlMedusa(bool);
    Q_INVOKABLE bool controlMedusa2(bool);
    Q_INVOKABLE bool controlSim(bool,bool);
    Q_INVOKABLE bool controlCrazy(bool);
    Q_INVOKABLE bool controlMonitor(bool);
    Q_INVOKABLE bool connectRadio(bool,int,int);
    Q_INVOKABLE bool connectSim(bool,int,bool);
    Q_INVOKABLE bool changeMedusaSettings(bool, bool);

    Q_INVOKABLE void setVision(bool, bool);
    Q_INVOKABLE int  getCameraNumber() {
        return PARAM::CAMERA;
    }
    Q_INVOKABLE void controlCamera(int, bool);
    Q_INVOKABLE void controlProcess(int, bool);
    Q_INVOKABLE void kill();
    Q_INVOKABLE int getFPS() {
        return VisionModule::instance()->getFPS();
    }
    Q_INVOKABLE double getBallVelocity() {
        return DealBall::instance()->getBallSpeed();
    }
    Q_INVOKABLE void robotControl(int, int);
//    Q_INVOKABLE bool send(const QString& str) {
//        return ZCommunicator::instance()->testSend(str);
//    }
//    Q_INVOKABLE QStringList getNetworkInterfaces() {
//        return ZCommunicator::instance()->updateNetworkInterfaces();
//    }
//    Q_INVOKABLE bool changeConnection(bool sw) {
//        if(sw)
//            return ZCommunicator::instance()->connect();
//        else
//            return ZCommunicator::instance()->disconnect();
//    }
//    Q_INVOKABLE void changeNetworkInterface(int index) {
//        ZCommunicator::instance()->changeNetworkInterface(index);
//    }
    ~Interaction();
public slots:
    void medusaPrint();
};

#endif // __INTERACTION_H__
