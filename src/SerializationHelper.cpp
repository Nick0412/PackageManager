#include "SerializationHelper.hpp"

#include <algorithm>
#include <string>

std::vector<std::byte> SerializationHelper::Serialize32BitUnsignedInt(std::uint32_t data)
{
    std::uint32_t networkByteOrderData = htonl(data);
    std::vector<std::byte> bytes{4};
    bytes[3] = static_cast<std::byte>(networkByteOrderData & 0xFF);
    bytes[2] = static_cast<std::byte>((networkByteOrderData >> 8) & 0xFF);
    bytes[1] = static_cast<std::byte>((networkByteOrderData >> 16) & 0xFF);
    bytes[0] = static_cast<std::byte>((networkByteOrderData >> 24) & 0xFF);

    return bytes;
}

std::uint32_t SerializationHelper::Deserialize32BitUnsignedInt(const std::vector<std::byte>& bytes)
{
    std::uint32_t networkByteOrderData{0};
    networkByteOrderData |= std::to_integer<std::uint32_t>(bytes[0]) << 24;
    networkByteOrderData |= std::to_integer<std::uint32_t>(bytes[1]) << 16;
    networkByteOrderData |= std::to_integer<std::uint32_t>(bytes[2]) << 8;
    networkByteOrderData |= std::to_integer<std::uint32_t>(bytes[3]);

    return ntohl(networkByteOrderData);
}

std::vector<std::byte> SerializationHelper::SerializeString(const std::string& data)
{
    std::vector<std::byte> bytes;
    std::transform(data.begin(), data.end(), std::back_inserter(bytes),
                   [](char c) { return static_cast<std::byte>(c); });

    return bytes;
}

std::string SerializationHelper::DeserializeString(const std::span<std::byte>& bytes)
{
    std::string data;
    std::transform(bytes.begin(), bytes.end(), std::back_inserter(data),
                   [](std::byte b) { return static_cast<char>(b); });

    return data;
}
