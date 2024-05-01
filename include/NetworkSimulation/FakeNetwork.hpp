#ifndef FAKE_NETWORK_HPP
#define FAKE_NETWORK_HPP

#include "Router.hpp"
#include "NetworkDevice.hpp"
#include "Utility/Logger.hpp"

#include <vector>

namespace NetworkSimulation
{
    class FakeNetwork
    {
    private:
        Utility::Logger logger_;
        Router router_;
        std::vector<NetworkDevice> network_devices_;

        bool doesNetworkDeviceAlreadyExist(const Endpoint& endpoint);

    public:
        FakeNetwork(const Utility::Logger& logger);
        NetworkDevice& provisionNetworkDevice(const Endpoint& endpoint);
        TestDataSocket& provisionDataSocketOnNetworkDevice(
            NetworkDevice& device, 
            const Endpoint& destination_endpoint,
            const Port& destination_port);
    };

}

#endif
