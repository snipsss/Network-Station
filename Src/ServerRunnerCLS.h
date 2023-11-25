#pragma once
#include "includeMe.h"
#include <iostream>
#include <QHBoxLayout>
#include <QTextEdit>
#include "SocketCLS.h"

using namespace PNet;


class RunnerSRV
{
public:
    RunnerSRV(Socket* object,QThread* thread);
    ~RunnerSRV();
    bool ProcessPacket(Packet& packet);
    bool RunThisServer();
    void QuitServer();
    void show();
  //  QHBoxLayout* getQHboxLayout(){return pHBoxlayout;}
    QTextEdit* getTextEdt(){return pOutputTextEdit;}
    void setQTextEdit(QTextEdit* pTextEdit){pOutputTextEdit= pTextEdit;}
    void setMainWidget( QWidget* mainWidget){ pRunnerSRVQWidget = mainWidget;}
    QWidget* getMainWidget(){ return pRunnerSRVQWidget;}

private:
    Socket* m_pSocketObject;
    QThread* m_pThreadServer;
    QHBoxLayout* pHBoxlayout;
    QTextEdit* pOutputTextEdit;
    QWidget* pRunnerSRVQWidget;
};
