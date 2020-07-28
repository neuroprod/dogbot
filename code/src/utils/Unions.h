#pragma once
#include <iostream>
#include <cstdint>

union UnionU16
{
    std::uint16_t r;     // occupies 4 bytes
    std::uint8_t b[2]; // occupies 4 bytes
};
union Union16
{
    std::int16_t r;     // occupies 4 bytes
    std::uint8_t b[2]; // occupies 4 bytes
};

union Union32
{
    std::int32_t r;     // occupies 4 bytes
    std::uint8_t b[4]; // occupies 4 bytes
};