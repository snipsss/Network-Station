#include <includeMe.h>
#include <iostream>

using namespace PNet;

bool ProcessPacket(Packet& packet)
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

int RunThisServer()
    {
    if (PNet::NetWork::initiaise())
    {
        std::cout << "Winsock APi Sucksefully created!" << std::endl;
        Socket socket;
        //142.93.5.18
        if (socket.Create() == Result::P_sucksess)
        {
            std::cout << "Socket succsessfully created!" << std::endl;
            if (socket.Listen(IpEndPoint("0.0.0.0",5000)) == Result::P_sucksess)
            {
                std::cout << "Socket successfully listening on: 5000" << std::endl;
                Socket newConnection;
                if(socket.Accpet(newConnection) == Result::P_sucksess)
                {
                    std::cout << "New connection Accepted!" << std::endl;

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
                }
            }
            else
            {
                std::cerr << "Failed listening on port 5000" << std::endl;
            }
        }
    }
}
