#include "NetWorkCLS.h"
#include <iostream>



bool PNet::NetWork::initiaise()
{
    #ifdef _WIN32

    WSADATA data;
    WORD wWerisonRequst = MAKEWORD(2, 2);
    int result = WSAStartup(wWerisonRequst,&data);
    if(result != 0)
    {
        std::cerr << "FAILED to start winSocket API!" << std::endl;
        return false;
    }
    if(LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2)
    {
        std::cerr << "coult not find a usable version of dll file" << std::endl;
        return false;
    }
    #endif
    return true;
}

void PNet::NetWork::shoutDown()
{
    #ifdef _WIN32
    WSACleanup();
    #endif
}
