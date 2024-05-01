#include "Router.hpp"
#include <iostream>

Router::Router(const Utility::Logger& logger)
: logger_{logger}
{
}

bool Router::doesSocketExist(const Endpoint& source_endpoint, const Port& source_port) const
{
    for (const auto& sock : sockets_)
    {
        if (sock.getEndpoint() == source_endpoint && sock.getPort() == source_port)
        {
            return true;
        }
    }
    return false;
}

TestDataSocket& Router::addSocket(Endpoint source_endpoint, Endpoint destination_endpoint, Port source_port, Port destination_port)
{
    if (doesSocketExist(source_endpoint, source_port))
    {
        throw std::runtime_error("Socket already exists");
    }

    logger_.info("[ROUTER] Constructing socket: source_endpoint{{{}}} source_port{{{}}}", source_endpoint, source_port);
    return sockets_.emplace_back(source_endpoint, source_port, destination_endpoint, destination_port, *this, logger_);
}

void Router::routePacket(const Packet& packet)
{
    logger_.info("[ROUTER] Routing packet: id{{{}}} destination_endpoint{{{}}}, destination_port{{{}}}",
        packet.id_, packet.destination_endpoint_, packet.destination_port_);
    for (auto& sock : sockets_)
    {
        if (sock.getEndpoint() == packet.destination_endpoint_ && sock.getPort() == packet.destination_port_)
        {
            logger_.info("[ROUTER] Found socket");
            sock.consumePacket(packet);
        }
    }
}

std::size_t Router::getSize()
{
    return sockets_.size();
}
