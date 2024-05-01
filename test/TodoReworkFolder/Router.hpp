#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <vector>
#include "TestDataSocket.hpp"
#include "Utility/Logger.hpp"
#include "Packet.hpp"

class TestDataSocket;

class Router 
{
private:
    std::vector<TestDataSocket> sockets_;
    Utility::Logger logger_;

public:
    Router(const Utility::Logger& logger);

    void routePacket(const Packet& packet);
    bool doesSocketExist(const Endpoint& source_endpoint, const Port& source_port) const;
    TestDataSocket& addSocket(Endpoint source_endpoint, Endpoint destination_endpoint, Port source_port, Port destination_port);
    std::size_t getSize();
};

#endif
