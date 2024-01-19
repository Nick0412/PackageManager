#include "SerializationHelper.hpp"

#include <arpa/inet.h>
#include <iostream>

std::vector<std::byte> SerializationHelper::Serialize32BitUnsignedInt(std::uint32_t number)
{
    std::uint32_t network_byte_order_number = htonl(number);
    std::vector<std::byte> number_bytes(4);
    number_bytes[3] = static_cast<std::byte>(network_byte_order_number & 0xFF);
    number_bytes[2] = static_cast<std::byte>((network_byte_order_number >> 8) & 0xFF);
    number_bytes[1] = static_cast<std::byte>((network_byte_order_number >> 16) & 0xFF);
    number_bytes[0] = static_cast<std::byte>((network_byte_order_number >> 24) & 0xFF);

    return number_bytes;
}
