#pragma once
#include "threadserver.h"
#include "ServerRunnerCLS.h"
#include "SocketCLS.h"
#include <QThread>
#include <QObject>
#include <QHBoxLayout>


class ServerInit: public QThread
{
    Q_OBJECT
public:
    ServerInit(RunnerSRV* runnerServerObject);

    ~ServerInit();
    QHBoxLayout* getLayoutServer() {return m_pServerLayout;}
public slots:
    void startUpServer();
    void quitServerSession();
   // QHBoxLayout* getLayoutServer() {return m_pServerLayout;}
private:
    RunnerSRV* m_pRunnerSRV;
    QHBoxLayout* m_pServerLayout;
};
