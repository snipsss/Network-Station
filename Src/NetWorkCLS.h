#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#endif

namespace PNet
{
    class NetWork
    {
    public:
        static bool initiaise();
        static void shoutDown();
    };
}