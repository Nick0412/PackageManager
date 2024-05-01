#include "FakeNetwork.hpp"

#include <algorithm>
#include <stdexcept>

namespace NetworkSimulation
{
    FakeNetwork::FakeNetwork(const Utility::Logger& logger)
    : logger_{logger}, router_{logger}
    {

    }

    NetworkDevice& FakeNetwork::provisionNetworkDevice(const Endpoint& endpoint)
    {
        if (doesNetworkDeviceAlreadyExist(endpoint))
        {
            throw std::runtime_error("Network device already exists.");
        }

        // Create the network device.
        NetworkDevice& device_reference = network_devices_.emplace_back(router_, endpoint, logger_);

        // Link the network device and the router together via their pointers.
        device_reference.setRouter(&router_);
        router_.attachNetworkDevice(&device_reference);

        return device_reference;
    }

    TestDataSocket& FakeNetwork::provisionDataSocketOnNetworkDevice(
            NetworkDevice& device, 
            const Endpoint& destination_endpoint,
            const Port& destination_port)
    {
        auto optional_port = device.getAvailablePort();
        if (!optional_port.has_value())
        {
            throw std::runtime_error("No ports available");
        }

        TestDataSocket& socket = device.constructSocket(
            device.getEndpoint(),
            optional_port.value(),
            destination_endpoint,
            destination_port);

        return socket;
    }

    bool FakeNetwork::doesNetworkDeviceAlreadyExist(const Endpoint& endpoint)
    {
        auto begin_iter = network_devices_.begin();
        auto end_iter = network_devices_.end();
        auto result = std::find_if(begin_iter, end_iter, [&](const NetworkDevice& nd) { return nd.getEndpoint() == endpoint; });

        // If the network device endpoint does not exist, then this statement will be false.
        return result != end_iter;
    }
}
