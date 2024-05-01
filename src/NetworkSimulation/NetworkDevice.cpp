#include "NetworkSimulation/NetworkDevice.hpp"

#include <algorithm>

namespace NetworkSimulation
{
    NetworkDevice::NetworkDevice(Router* router, const std::string& endpoint, const Utility::Logger& logger)
    : router_{router}, endpoint_{endpoint}, logger_{logger}
    {

    }

    void NetworkDevice::setRouter(Router* router)
    {
        router_ = router;
    }

    void NetworkDevice::consumePacket(const Packet& packet)
    {
        packet.destination_port;
    }

    // void NetworkDevice::sendDataFromSocket(TestDataSocket* socket, const ByteList& data);
    // Endpoint NetworkDevice::getEndpoint() const;

    bool NetworkDevice::isPortInUse(const Port& port) const
    {
        auto iter_begin = sockets_.begin();
        auto iter_end = sockets_.end();
        auto iter = std::find_if(iter_begin, iter_end, [&](TestDataSocket& sock) { return sock.getPort() == port; });

        return iter != iter_end;
    }

    TestDataSocket& NetworkDevice::getSocketWithPort(const Port& port)
    {
        auto iter_begin = sockets_.begin();
        auto iter_end = sockets_.end();
        auto iter = std::find_if(iter_begin, iter_end, [&](TestDataSocket& sock) { return sock.getPort() == port; });

        if (iter == iter_end)
        {
            throw std::runtime_error("No socket with port found");
        }

        return *iter;
    }

    // std::optional<Port> NetworkDevice::getAvailablePort() const;
    // TestDataSocket& NetworkDevice::constructSocket(const Endpoint& source_endpoint,
    //     const Port& source_port, 
    //     const Endpoint& destination_endpoint, 
    //     const Port& destination_port);
}
