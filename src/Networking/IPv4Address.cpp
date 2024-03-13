#include "Networking/IPv4Address.hpp"

IPv4Address::IPv4Address(const std::string& ipv4_address_string)
{

}

IPv4Address::IPv4Address(const std::array<std::uint8_t, 4>& ip_address_array)
: raw_ip_address{ip_address_array}
{
    
}

IPv4Address::IPv4Address(std::uint8_t block_1, std::uint8_t block_2, std::uint8_t block_3, std::uint8_t block_4)
{
    
}

// IPv4Address::IPv4Address(const IPv4Address& other);
// IPv4Address::std::string getIpAddressString();
// IPv4Address::std::uint8_t operator[](std::size_t index);
