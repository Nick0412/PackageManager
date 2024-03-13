#include "Networking/IPv4Address.hpp"
#include "Networking/Utilities.hpp"

#include <stdexcept>

IPv4Address::IPv4Address(const std::string& ipv4_address_string)
: raw_ip_address{Networking::Utilities::ConvertIPv4StringToArray(ipv4_address_string)}
{

}

IPv4Address::IPv4Address(const std::array<std::uint8_t, 4>& ip_address_array)
: raw_ip_address{ip_address_array}
{
    
}

IPv4Address::IPv4Address(std::uint8_t block_1, std::uint8_t block_2, std::uint8_t block_3, std::uint8_t block_4)
: raw_ip_address{block_1, block_2, block_3, block_4}
{
    
}

IPv4Address::IPv4Address(const IPv4Address& other)
: raw_ip_address{other.raw_ip_address}
{

}


std::string IPv4Address::getIpAddressString()
{
    return Networking::Utilities::ConvertIPv4ArrayToString(raw_ip_address);
}

std::uint8_t IPv4Address::operator[](std::size_t index)
{
    if (index > Networking::Utilities::IPV4_BLOCKS)
    {
        throw std::runtime_error("IPv4Address index is out of bounds.");
    }

    return raw_ip_address[index];
}
