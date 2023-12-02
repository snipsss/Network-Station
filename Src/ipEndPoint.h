#pragma once
#include "ipVersion.h"
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#endif
namespace PNet
{
    class IpEndPoint
    {
    public:
        IpEndPoint(const char* ip, unsigned short port);
        IpEndPoint(sockaddr* addr);
        IpVersion getIpVersion();
        std::string getHostName();
        std::string getIpString();
        std::vector<uint8_t> getBytesVector();
        unsigned short getPort();
        sockaddr_in getSockAddIpV4();
        void print();

    private:
        IpVersion m_ipversion = IpVersion::Unknow;
        std::string m_hostname;
        std::string ip_string;
        std::vector<uint8_t> ip_bytes;
        unsigned short port = 0;



    };



}
