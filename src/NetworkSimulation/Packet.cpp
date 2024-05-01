#include "NetworkSimulation/Packet.hpp"

#include <format>

namespace NetworkSimulation
{
    Packet::Packet(
        const Endpoint& source_endpoint,
        const Port& source_port, 
        const Endpoint& destination_endpoint, 
        const Port destination_port, 
        const ByteList& data)
    : source_endpoint{source_endpoint},
      source_port{source_port},
      destination_endpoint{destination_endpoint}, 
      destination_port{destination_port},
      data{data}
    {

    }

    std::ostream& operator<<(std::ostream& stream, const Packet& packet)
    {
        auto formatted_str = std::format(
            "Packet: {{\n"
            "\tsource_endpoint: \"{}\"\n"
            "\tsource_port: {}\n"
            "\tdestination_endpoint: \"{}\"\n"
            "\tdestination_port: {}\n"
            "}}\n",
            packet.source_endpoint, packet.source_port, packet.destination_endpoint, packet.destination_port);

        stream << formatted_str;
        return stream;
    }
}
