#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock.h>
#else
#include <arpa/inet.h> // for htons // for ntohs..
#endif
#include <iostream>
#include <vector>
#include "PackageExtenntionCLS.h"
#include "PackageType.h"

namespace PNet
{
   struct Packet
   {
   public:

       Packet(PacketType packetType = PacketType::PT_invalid);
       std::vector<char> m_buffer;
       uint32_t absOffSet = 0;

       void AssignPacketType(PacketType packetType);
       PacketType getType();

       void clearPacket();
       void append(const void* data, uint32_t size);
       Packet& operator <<(uint32_t data);
       Packet& operator >>(uint32_t& data);
       Packet& operator <<(const std::string& data);
       Packet& operator >>(std::string & data);




   };


}
