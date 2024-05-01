#ifndef PACKET_HPP
#define PACKET_HPP

#include <vector>
#include <cstdint>
#include <string>

using ByteList = std::vector<std::uint8_t>;
using Endpoint = std::string;
using Port = std::uint16_t;

class Packet 
{
private:
    static std::size_t id_counter_s;

public:
    Endpoint source_endpoint_;
    Endpoint destination_endpoint_;
    Port source_port_;
    Port destination_port_;
    ByteList data_;
    std::size_t id_;

    Packet(
        const Endpoint& source_endpoint,
        const Port& source_port, 
        const Endpoint& destination_endpoint, 
        const Port destination_port, 
        const ByteList& data);
};

#endif
