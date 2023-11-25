#include "SocketCLS.h"
#include "PResultCLS.h"
#include "SocketHandle.h"
#include <assert.h>
#include <cassert>
#include <iostream>
#include <unistd.h>

namespace PNet {
    Socket::Socket(IpVersion ipversion, SocketHandle handle)
        :ipVersion(ipversion), handle(handle)
    {
        assert(ipVersion == IpVersion::IP_v4);
    }

    Result Socket::Create()
    {
        assert(ipVersion == IpVersion::IP_v4);
        if (handle != INVALID_SOCKET)
        {
            return Result::P_GenericError;
        }
        handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (handle == INVALID_SOCKET)
        {
            int error = WSAGetLastError();
            return Result::P_GenericError;
        }
        if (SetSocketOption(SocketOption::TCP_NoDelay, 1) != Result::P_sucksess)
        {
            return Result::P_GenericError;
        }
        return Result::P_sucksess;
    }

    Result Socket::CloseSocket()
    {
        if (handle == INVALID_SOCKET)
        {
            return Result::P_GenericError;
        }
        int result = closesocket(handle);
        if (result != 0)
        {
            int error = WSAGetLastError();
            return Result::P_GenericError;
        }
        handle = INVALID_SOCKET;
        return Result::P_sucksess;
    }

    SocketHandle Socket::GetHandle()
    {
        return handle;
    }

    Result Socket::Bind(IpEndPoint endpoint)
    {
        sockaddr_in addr = endpoint.getSockAddIpV4();
        int result = bind(handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
        if(result != 0)
        {
            int error = WSAGetLastError();
            return Result::P_GenericError;
        }
        return Result::P_sucksess;
    }

    IpVersion Socket::GetIpVersion(){ return ipVersion; }
    Result Socket::Listen(IpEndPoint endpoint, int backlog)
    {
       if(Bind(endpoint) != Result::P_sucksess)
       {
           return Result::P_GenericError;
       }

       int result = listen(handle, backlog);
       if(result != 0)
       {
           int error = WSAGetLastError();
           std::cerr << "Listen returned 0" << std::endl;
           return Result::P_GenericError;
       }
       return Result::P_sucksess;
    }

    Result Socket::Accpet(Socket& outSock)
    {
        sockaddr_in addrin = {};
        #ifdef _WIN32
            int storeSize = sizeof(addrin);
        #else
            socklen_t len = sizeof(addrin);
        #endif
        SocketHandle acceptedConnectionHabndle = accept(handle,(sockaddr*)(& addrin),&len);
        if(acceptedConnectionHabndle == INVALID_SOCKET)
        {
            return Result::P_GenericError;
        }
        IpEndPoint newConnectionEndPoint((sockaddr*)&addrin);
        newConnectionEndPoint.print();
        std::cout << "New Connection accepted!" << std::endl;
        outSock = Socket(IpVersion::IP_v4,acceptedConnectionHabndle);
        return Result::P_sucksess;
    }

    Result Socket::Connect(IpEndPoint endpoint)
    {
        sockaddr_in addr = endpoint.getSockAddIpV4();
        int result = connect(handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
        if(result != 0)
        {
            int error = WSAGetLastError();
           std::cerr << "connection failed in file MyClassSocket.cpp line" << __LINE__ << std::endl;
            return Result::P_GenericError;
        }
        return Result::P_sucksess;

    }
    Result Socket::SendPackage(const void* data, int numberofbytes, int& bytesSent)
    {
        bytesSent = send(handle,(const char*)data,numberofbytes,0);
        if(bytesSent == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            std::cerr << "Error in sending package!" << std::endl;
            return Result::P_GenericError;
        }
        return Result::P_sucksess;
    }
    Result Socket::SentAllPackage(const void* data, int numberOfBytes)
    {
        int totalBytesSent = 0;
        while(totalBytesSent < numberOfBytes)
        {
            int bytesRemainding = numberOfBytes - totalBytesSent;
            int bytesSent = 0;
            char* bufferOffSet = (char*)data + totalBytesSent;
            Result result = SendPackage(bufferOffSet, bytesRemainding, bytesSent);
            if(result != Result::P_sucksess)
            {
                return Result::P_GenericError;
            }
            totalBytesSent += bytesSent;
        }
        return Result::P_sucksess;
    }


    Result Socket::Recv(void* destination, int numberofBytes, int& bytesRecives)
    {
        bytesRecives = recv(handle, (char*)destination, numberofBytes, 0);
        if(bytesRecives == 0)
        {
            int error = WSAGetLastError();
            std::cerr << "error in recv!: " << error << std::endl;
            return Result::P_GenericError;
        }
        if(bytesRecives == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            std::cout << "socket error!" << std::endl;
            return Result::P_GenericError;
        }
        return Result::P_sucksess;
    }
    Result Socket::RecvAll(void* destination, int numberOfBytes)
    {
        int totalBytesRecv = 0;
        while (totalBytesRecv < numberOfBytes)
        {
            int bytesRemainding = numberOfBytes - totalBytesRecv;
            int bytesRecived = 0;
            char* bufferOffSet = (char*)destination + totalBytesRecv;
            Result result = Recv(bufferOffSet, bytesRemainding, bytesRecived);
            if (result != Result::P_sucksess)
            {
                return Result::P_GenericError;
            }
            totalBytesRecv += bytesRecived;
        }
        return Result::P_sucksess;
    }


    Result Socket::Recvive(Packet& packet)
    {
        packet.clearPacket();

        uint16_t  encodeSize = 0;
        Result res = RecvAll(&encodeSize, sizeof(uint16_t));
        if (res != Result::P_sucksess)
        {
            return Result::P_GenericError;
        }

        uint16_t buffSize = ntohs(encodeSize);

        if(buffSize > PNet::maxBufferSize)
        {
            std::cerr << "buffer size is more thanm MaxBufferSize" << std::endl;
            return Result::P_GenericError;
        }

        packet.m_buffer.resize(buffSize);
        res = RecvAll(&packet.m_buffer[0], buffSize);
        if (res != Result::P_sucksess)
        {
            return Result::P_GenericError;
        }

        return Result::P_sucksess;
    }



    Result Socket::SendIt(Packet& packet)
    {
        uint16_t  encodedPacketSize = htons(packet.m_buffer.size());
        Result result = SentAllPackage(&encodedPacketSize, sizeof(uint16_t));
        if (result != Result::P_sucksess)
        {
            int err = WSAGetLastError();
            std::cerr << "Problem with sending package" << err << std::endl;
            return Result::P_GenericError;
        }

        result = SentAllPackage(packet.m_buffer.data(), packet.m_buffer.size());
        if (result != Result::P_sucksess)
        {
            int err = WSAGetLastError();
            std::cerr << "Problem with sending package" << err << std::endl;
            return Result::P_GenericError;
        }
        return Result::P_sucksess;
    }


    Result Socket::SetSocketOption(SocketOption option, BOOL value)
    {
        int result = 0;
        switch (option)
        {
        case SocketOption::TCP_NoDelay:
            result = setsockopt(handle, IPPROTO_TCP, TCP_NoDelay, (const char*)&value, sizeof(value));
            break;
        default:
        {
            return Result::P_GenericError;
        }
        if (result != 0)
        {
            int error = WSAGetLastError();
            return Result::P_GenericError;
        }
        }
        return Result::P_sucksess;
    }
}
