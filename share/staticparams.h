#ifndef STATICPARAMS_H
#define STATICPARAMS_H
//change param for 2018 rule
//wait for change camera number
#include <QString>
namespace PARAM {
const bool DEBUG = false;
const int CAMERA = 8;
const int SENDROBOTNUM = 8;
const int ROBOTNUM = 16;// max allow robot on the playgroung
const int ROBOTMAXID = 16;
const int BALLNUM = 20;
const int BLUE = 0;
const int YELLOW = 1;
const int BALLMERGEDISTANCE = 140;
const int ROBOTMERGEDOSTANCE = 100;
const int TEAMS = 2;
}
namespace ZSS {
const QString ZSS_ADDRESS = "233.233.233.233";
const QString SSL_ADDRESS = "224.5.23.2";
const QString REF_ADDRESS = "224.5.23.1";
const QString LOCAL_ADDRESS = "127.0.0.1";
namespace Jupyter {
const int CONTROL_BACK_SEND = 10002;
const int CONTROL_RECEIVE = 10001;
}
namespace Medusa {
const int DEBUG_MSG_SEND[2] = {20001, 20002};
const int DEBUG_SCORE_SEND[2] = {20003, 20004};
}
namespace Sim {
const int SIM_RECEIVE = 30001;
const double G = 9.8;
const double PI = 3.14159265358979323846;
const int CHIP_ANGLE = 45;
const int BLUE_STATUS_PORT = 30011;
const int YELLOW_STATUS_PORT = 30012;
}
namespace Athena {
const int CONTROL_SEND[PARAM::TEAMS] = {50001, 50002};
const int CONTROL_BACK_RECEIVE[PARAM::TEAMS] = {60001, 60002};
const int VISION_SEND[PARAM::TEAMS] = {23333, 23334};
const int SEND_TO_PYTHON = 41001;
const int DEBUG_MSG_RECEIVE[2] = {20001, 20002};
const int DEBUG_SCORE_RECEIVE[2] = {20003, 20004};
const int SIM_SEND = 20011;
const double FRAME_RATE = 75;
const double V_SWITCH = 2000;
const double ACC_SLIDE = -4000;
const double ACC_ROLL = -325;
const float TOTAL_LATED_FRAME = 4.7f;
const double BALL_DELC_CHANGE_POINT = 250;
const double BALL_FAST_DEC = 360;
const double BALL_SLOW_DEC = 27.5;
namespace Vision {
const int BALL_STORE_BUFFER = 100;
const int ROBOT_STORE_BUFFER = 100;
const int MAINTAIN_STORE_BUFFER = 1000;
}
}
}
#endif // STATICPARAMS_H
