#include "ServerRunnerCLS.h"
#include "ServerWidget.h"
#include <QLabel>
#include <QDialog>
#include <QTextEdit>
bool RunnerSRV::ProcessPacket(Packet& packet)
{
switch (packet.getType())
{
case PacketType::PT_ChatMessage:
{
    std::string chatMessage;
    packet >> chatMessage;
    std::cout << "Chat Message: " << chatMessage << std::endl;
    break;
}
case PacketType::PT_integerArray:
{
    uint32_t arraySize = 0;
    packet >> arraySize;
    std::cout << "Array Size: " << arraySize << std::endl;
    for (uint32_t i = 0; i < arraySize; i++)
    {
        uint32_t element = 0;
        packet >> element;
        std::cout << "Element [" << i << "] - " << element << std::endl;
    }
    break;
}
default:
    return false;
}

return true;
}
RunnerSRV::RunnerSRV(Socket* object,QThread* thread):m_pSocketObject(object),m_pThreadServer(thread)
{
}
void RunnerSRV::show()
{
    pOutputTextEdit->append("Winsock APi Sucksefully created!");
    // ...
    pOutputTextEdit->append("Socket succsessfully created!");
    // ...
    pOutputTextEdit->append("Socket successfully listening on: 5000");
    // ...
    pOutputTextEdit->append("New connection Accepted!");
    // ..
}


RunnerSRV::~RunnerSRV(){}

void RunnerSRV::QuitServer()
{
    m_pThreadServer->quit();
    m_pThreadServer->terminate();
    m_pSocketObject->CloseSocket();
    PNet::NetWork::shoutDown();
    std::cout << "Connection Closed" << std::endl;
}


bool RunnerSRV::RunThisServer()
{    
        if (PNet::NetWork::initiaise())
        {
            //QDialog* pDialgInitServerInfor = new QDialog;
            std::cout << "Winsock APi Sucksefully created!" << std::endl;
            Socket socket;
            //142.93.5.18
            if (socket.Create() == Result::P_sucksess)
            {
                std::cout << "Socket succsessfully created!" << std::endl;
              //  QLabel* pLabel2 = new QLabel("Socket succsessfully created!");
                //object.getLayoutServer()->addWidget(pLabel2);
                if (socket.Listen(IpEndPoint("0.0.0.0",5000)) == Result::P_sucksess)
                {
                    std::cout << "Socket successfully listening on: 5000" << std::endl;
                  //  QLabel* pLabel3 = new QLabel("Socket successfully listening on: 5000");
                    //object.getLayoutServer()->addWidget(pLabel3);
                    Socket newConnection;
                    if(socket.Accpet(newConnection) == Result::P_sucksess)
                    {
                        std::cout << "New connection Accepted!" << std::endl;
                      //  QLabel* pLabel4 = new QLabel("New connection Accepted!");
                      //  object.getLayoutServer()->addWidget(pLabel4);
                       // pDialgInitServerInfor->setLayout(object.getLayoutServer());
                        Packet packet;
                        while(true)
                        {
                            Result res = newConnection.Recvive(packet);
                            if(res != Result::P_sucksess)
                            {
                                break;
                            }

                            if (!ProcessPacket(packet)) { break; }
                        }
                        newConnection.CloseSocket();
                    }
                    else
                    {
                        std::cerr << "failed! to accept new connection! " << std::endl;
                        return false;
                    }
                }
                else
                {
                    std::cerr << "Failed listening on port 5000" << std::endl;
                    return false;
                }
            }
        }
        return true;

}
