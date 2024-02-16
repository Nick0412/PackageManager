/**
 * This file contains platform specific code.
*/
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

std::uint32_t SerializationHelper::Deserialize32BitUnsignedInt(const std::vector<std::byte>& bytes)
{
    std::uint32_t network_byte_order_number{0};
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[0]) << 24;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[1]) << 16;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[2]) << 8;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[3]);

    return ntohl(network_byte_order_number);
}

std::vector<std::byte> SerializationHelper::SerializeString(const std::string& value)
{
    std::vector<std::byte> ret;

    for (auto& c : value)
    {
        ret.push_back(std::byte{c});
    }

    return ret;
}

std::string SerializationHelper::DeserializeString(const std::span<std::byte>& bytes)
{
    std::string ret;
    for (std::byte b : bytes)
    {
        ret.push_back(static_cast<char>(b));
    }

    return ret;
}

std::uint32_t SerializationHelper::Deserialize32BitUnsignedInt(const std::span<std::byte>& bytes, std::size_t position)
{
    std::uint32_t network_byte_order_number{0};
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[position + 0]) << 24;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[position + 1]) << 16;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[position + 2]) << 8;
    network_byte_order_number |= std::to_integer<std::uint32_t>(bytes[position + 3]);

    return ntohl(network_byte_order_number);
}
