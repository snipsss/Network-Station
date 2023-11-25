#pragma once

#include <stdint.h>

namespace PNet
{
    enum PacketType : uint16_t
    {
        PT_invalid,
        PT_ChatMessage,
        PT_integerArray
    };
}
