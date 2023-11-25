#pragma once

#include <iostream>

namespace PNet
{
    class PacketException
    {
    private:
        std::string m_exception;
    public:
        PacketException(const std::string& exception)
            :m_exception(exception)
        {
        }
        const char* what() { return m_exception.c_str(); }
        std::string GetException() const { return m_exception; }

    };
}
