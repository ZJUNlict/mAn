#ifndef ZACTIONMODULE_H
#define ZACTIONMODULE_H
#include <QObject>
#include <QMutex>
#include <QUdpSocket>
#include "singleton.hpp"
#include "zss_cmd.pb.h"
#include "staticparams.h"
namespace ZSS {
class ActionModule : public QObject {
    Q_OBJECT
  public:
    ActionModule(QObject *parent = 0);
    ~ActionModule();
    void sendLegacy(int t, const ZSS::Protocol::Robots_Command&);
    bool connectRadio(int, int);
    bool disconnectRadio(int);
    int team[PARAM::TEAMS];
  private slots:
    void readData();
  private:
    void sendStartPacket(int, int);
  private:
    QByteArray tx;
    QByteArray rx;
    QUdpSocket sendSocket;
    QUdpSocket receiveSocket;
    QMutex robotInfoMutex;
  signals:
    void receiveRobotInfo(int, int);
};
typedef Singleton<ActionModule> ZActionModule;
}
#endif // ZACTIONMODULE_H
