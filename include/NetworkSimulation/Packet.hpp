#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <ostream>

namespace NetworkSimulation
{
    using Port = std::uint16_t;
    using ByteList = std::vector<std::uint8_t>;
    using Endpoint = std::string;

    class Packet
    {
    public:
        Endpoint source_endpoint;
        Endpoint destination_endpoint;
        Port source_port;
        Port destination_port;
        ByteList data;

        Packet(
            const Endpoint& source_endpoint,
            const Port& source_port, 
            const Endpoint& destination_endpoint, 
            const Port destination_port, 
            const ByteList& data);
    };

    std::ostream& operator<<(std::ostream& stream, const Packet& packet);
};

#endif
