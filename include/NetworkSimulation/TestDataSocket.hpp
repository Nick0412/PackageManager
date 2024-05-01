#ifndef TEST_DATA_SOCKET_HPP
#define TEST_DATA_SOCKET_HPP

#include "Networking/SocketInterfaces.hpp"
#include "Packet.hpp"
#include "NetworkDevice.hpp"

namespace NetworkSimulation
{
    class TestDataSocket : public Networking::IDataSocket
    {
    private:
        NetworkDevice* network_device_;
        ByteList input_byte_queue_;
        Endpoint source_endpoint_;
        Endpoint destination_endpoint_;
        Port source_port_;
        Port destination_port_;

    public:
        TestDataSocket(
            NetworkDevice* network_device,
            const Endpoint& source_endpoint,
            const Port& source_port, 
            const Endpoint& destination_endpoint, 
            const Port& destination_port);
        Port getPort() const;
    };
}

#endif
