#include "ServerWidget.h"
#include "MainServerRun.h"
#include "ServerRunnerCLS.h"
#include "SocketCLS.h"
#include "NetWorkCLS.h"


ServerInit::ServerInit(RunnerSRV* runnerServerObject): m_pRunnerSRV(runnerServerObject)
{
};

ServerInit::~ServerInit(){delete m_pServerLayout;}


void ServerInit::startUpServer()
{
    m_pRunnerSRV->RunThisServer();
//    object.RunThisServer();
}

void ServerInit::quitServerSession()
{ 
  //  PNet::NetWork::shoutDown();
    std::cout << "Connection Closed" << std::endl;
}
