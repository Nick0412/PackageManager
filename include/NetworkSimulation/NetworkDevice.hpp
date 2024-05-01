#ifndef NETWORK_DEVICE_HPP
#define NETWORK_DEVICE_HPP

#include "Utility/Logger.hpp"
#include "Packet.hpp"
#include "TestDataSocket.hpp"

#include <vector>
#include <optional>

namespace NetworkSimulation
{
    // Forward declaration of the Router class and Socket class.
    class Router;
    class TestDataSocket;

    /**
     * @brief The `NetworkDevice` class is meant to represent an actual network device such as a
     * network card attached to a machine. It has an associated endpoint that it registers with a
     * router device.
     * 
     * In addition is will have multiple data sockets attached to it. Incoming packets to the
     * NetworkDevice will be router to the correct socket so they may receive it. Data sockets will
     * send packets that first go through the NetworkDevice before going to the router.
     * 
     *                                +----------+                                
     *                                |          |                                
     *                                |  Router  |                                
     *                                |          |                                
     *                                +------+---+                                
     *                                    ^  |                                   
     *                                    |  v                                   
     *                           +--------+-------------+                        
     *   +-----------------+     |                      |     +-----------------+
     *   |                 +---->|    NetworkDevice     |<----+                 |
     *   | TestDataSocket1 |     |                      |     | TestDataSocket2 |
     *   |                 |<----+(Endpoint: "0.0.0.0") +---->|                 |
     *   +-----------------+     |                      |     +-----------------+
     *                           +----------------------+                        
     * 
     */
    class NetworkDevice
    {
    private:
        std::vector<TestDataSocket> sockets_;
        std::string endpoint_;
        Utility::Logger logger_;
        Router* router_;

    public:
        NetworkDevice(const NetworkDevice& other) = delete;
        NetworkDevice& operator=(const NetworkDevice& other) = delete;
        NetworkDevice(Router* router, const std::string& endpoint, const Utility::Logger& logger);

        void setRouter(Router* router);
        void consumePacket(const Packet& packet);
        void sendDataFromSocket(TestDataSocket* socket, const ByteList& data);
        Endpoint getEndpoint() const;
        bool isPortInUse(const Port& port) const;
        std::optional<Port> getAvailablePort() const;
        TestDataSocket& getSocketWithPort(const Port& port);
        TestDataSocket& constructSocket(
            const Endpoint& source_endpoint,
            const Port& source_port, 
            const Endpoint& destination_endpoint, 
            const Port& destination_port);
    };
}

#endif
