#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "Utility/Logger.hpp"
#include "Packet.hpp"

#include <vector>

namespace NetworkSimulation
{
    // Forward declaration of a NetworkDevice.
    class NetworkDevice;

    /**
     * @brief A router is responsible for routing packets between various network devices. It should
     * work as follows:
     *   - A network device attached to the router will send a packet to the router.
     *   - The router will receive the packet and determine its destination.
     *     - The destination can be found using the packet's destination endpoint field.
     *   - The router will then consult its list of attached network devices and check if any of
     *     them have an endpoint which matches the packet's destination.
     *   - If a network device does have the correct endpoint, the router will send the packet it
     *     to it via some function call, most likely with a consume function on the network device.
     * 
     * +----------------+         +--------+         +----------------+
     * |                |<--------+        |<--------+                |
     * | NetworkDevice1 |         | Router |         | NetworkDevice2 |
     * |                +-------->|        +-------->|                |
     * +----------------+         +-----+--+         +----------------+
     *                              ^   |                              
     *                              |   |                              
     *                              |   v                              
     *                        +-----+----------+                       
     *                        |                |                       
     *                        | NetworkDevice3 |                       
     *                        |                |                       
     *                        +----------------+                       
     * 
     */
    class Router
    {
    private:
        Utility::Logger logger_;
        std::vector<NetworkDevice*> network_devices_;

    public:
        Router(const Utility::Logger& logger);
        void routePacket(const Packet& packet);
        void attachNetworkDevice(NetworkDevice* network_device);
    };
}

#endif
