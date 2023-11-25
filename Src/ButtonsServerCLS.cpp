#include "ButtonsServerCLS.h"





ServerButtons::ServerButtons(ServerInit* pServerInitParent): m_pServerLayout(new QHBoxLayout)
{
    pQButtonrunServer = new QPushButton("Startup Server");
    pQButtonrunServer->setStyleSheet("background-color: green;");

    m_pServerLayout->addWidget(pQButtonrunServer);

    connect(pQButtonrunServer,SIGNAL(clicked()),pServerInitParent,SLOT(startUpServer()));
}

void ServerButtons::isActivePressedServerConditionButton()
{
}

ServerButtons::~ServerButtons(){delete m_pServerLayout; delete pQButtonrunServer;}


