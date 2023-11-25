#include "ipEndPoint.h"
#include "ipVersion.h"
#include "NetWorkCLS.h"
#include <cassert>
#include <iostream>
#include <string.h>

namespace PNet {
    PNet::IpEndPoint::IpEndPoint(const char* ip, unsigned short port)
    {
        this->port = port;
        in_addr addr;
        int result = inet_pton(AF_INET, ip, &addr);
        if(result == 1)
        {
            if(addr.s_addr != INADDR_NONE)
            {
                ip_string = ip;
                m_hostname = ip;
                ip_bytes.resize(sizeof(uint32_t));
                memcpy(&ip_bytes[0], &addr.s_addr, sizeof(uint32_t));
                m_ipversion = IpVersion::IP_v4;
                return;
            }
        }
        addrinfo hint = {};
        hint.ai_family = AF_INET; // Only ipv4
        addrinfo* hostInfo = nullptr;
        result = getaddrinfo(ip, nullptr, &hint, &hostInfo);
        if(result == 0)
        {
            sockaddr_in* host_addr = (sockaddr_in*)hostInfo->ai_addr;
            ip_string.resize(16);
            inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], 16);
            m_hostname = ip;
            uint32_t ip_long = host_addr->sin_addr.s_addr;
            ip_bytes.resize(sizeof(uint32_t));
            // FIX 1ST DESTINATION
            memcpy(&ip_bytes[0],&ip_long, sizeof(uint32_t));
            m_ipversion = IpVersion::IP_v4;
            freeaddrinfo(hostInfo);
            return;
        }
        else // personal addition by Mark
        {
            std::cerr << "Result return 0... ipEndPoint.cpp" << std::endl;
            PNet::NetWork::shoutDown();
        }
    }

    IpEndPoint::IpEndPoint(sockaddr* addr)
    {
        assert(addr->sa_family == AF_INET);
        sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
        m_ipversion = IpVersion::IP_v4;
        port = ntohs(addrv4->sin_port);
        ip_bytes.resize(sizeof(uint32_t));
        memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(uint32_t));

        ip_string.resize(16);
        inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
        m_hostname = ip_string;
    }
    IpVersion PNet::IpEndPoint::getIpVersion() { return m_ipversion; }
    std::string PNet::IpEndPoint::getHostName(){ return m_hostname;}
    std::string PNet::IpEndPoint::getIpString(){ return ip_string;}
    std::vector<uint8_t> PNet::IpEndPoint::getBytesVector(){ return ip_bytes;}

    unsigned short PNet::IpEndPoint::getPort(){ return port;}
    sockaddr_in IpEndPoint::getSockAddIpV4()
    {
        assert(m_ipversion == IpVersion::IP_v4);
        sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(uint32_t));
        addr.sin_port = htons(port);
        return addr;
    }
    void IpEndPoint::print()
    {
        if(m_ipversion == IpVersion::IP_v4)

            switch (m_ipversion)
            {
            case IpVersion::IP_v4:
                std::cout << "IP Version: V4" << std::endl;
                break;
            case IpVersion::IP_v6:
                std::cout << "IP Version: V6" << std::endl;
                break;
            default:
                std::cout << "Uknow Version of ip stat is so strange because we have only two... Nice tech changed" << std::endl;
                break;
            }
        std::cout << "HostName: " << m_hostname << std::endl;
        std::cout << "IP address: " << ip_string << std::endl;
        std::cout << "Port: " << port << std::endl;
        std::cout << "ip bytes: ";
        for(const auto &link: ip_bytes)
        {
            std::cout << (int)link;
        }
        std::cout << "" << std::endl;
    }
}
