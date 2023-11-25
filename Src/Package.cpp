#include "Package.h"
#include "ConstantCLS.h"

namespace PNet {
    Packet::Packet(PacketType packetType)
    {
        clearPacket();
        AssignPacketType(packetType);

    }
    void Packet::AssignPacketType(PacketType packetType)
    {
        PacketType* ptrPacketType = reinterpret_cast<PacketType*>(&m_buffer[0]);
        *ptrPacketType = static_cast<PacketType>(htons(packetType));
    }
    PacketType Packet::getType()
    {
        PacketType* ptrPacketType = reinterpret_cast<PacketType*>(&m_buffer[0]);
        return static_cast<PacketType>(ntohs(*ptrPacketType));
    }
    void Packet::clearPacket()
    {
        m_buffer.resize(sizeof(PacketType));
        AssignPacketType(PacketType::PT_invalid);
        absOffSet = sizeof(PacketType);

    }

    void Packet::append(const void* data, uint32_t size)
    {

        if ((m_buffer.size() + size) > PNet::maxBufferSize)
            throw PacketException("{Packet::append(const void* data, uint_t size} - Package size exceeded max packet size.");

        m_buffer.insert(m_buffer.end(), (char*)data,(char*)data + size );

    }

    Packet& Packet::operator<<(uint32_t data)
    {
        data = htonl(data);
        append(&data, sizeof(uint32_t));
        return *this;
    }

    Packet& Packet::operator>>(uint32_t& data)
    {

        if ((absOffSet + sizeof(uint32_t)) > m_buffer.size()) {
            throw PacketException("Packet& Packet::operator>>(uint32_t& data) - Extraction absOffSet exceeded buffer size ");
        }

        data = *reinterpret_cast<uint32_t*>(&m_buffer[absOffSet]);
        data = ntohl(data);
        absOffSet += sizeof(uint32_t);

        return *this;
    }

    Packet& Packet::operator<<(const std::string& data)
    {
        *this << (uint32_t)data.size();
        append(data.data(), data.size());
        return *this;
    }


    Packet& Packet::operator>>(std::string& data)
    {
        data.clear();
        uint32_t strSize = 0;
        *this >> strSize;

        if ((absOffSet + strSize) > m_buffer.size()) { throw PacketException("Packet& Packet::operator>>(std::string& data) - extraction absOffSet ewxceeed buffer size"); }

        data.resize(strSize);
        data.assign(&m_buffer[absOffSet],strSize);
        absOffSet += strSize;
        return *this;
    }
}
