#ifndef IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <array>
#include <cstdint>
#include <string>

using Port = std::uint16_t;

class IPv4Address
{
private:
    std::array<std::uint8_t, 4> raw_ip_address;

public:
    IPv4Address() = delete;

    IPv4Address(const std::string& ipv4_address_string);
    IPv4Address(const std::array<std::uint8_t, 4>& ip_address_array);
    IPv4Address(std::uint8_t block_1, std::uint8_t block_2, std::uint8_t block_3, std::uint8_t block_4);
    IPv4Address(const IPv4Address& other);

    std::string getIpAddressString() const;
    std::uint8_t operator[](std::size_t index) const;
};

#endif
