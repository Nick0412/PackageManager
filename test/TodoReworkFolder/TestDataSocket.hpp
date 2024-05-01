#ifndef TEST_DATA_SOCKET_HPP
#define TEST_DATA_SOCKET_HPP

#include <vector>
#include "Networking/SocketInterfaces.hpp"
#include "Packet.hpp"
#include "Utility/Logger.hpp"
#include "Router.hpp"

class Router;

class TestDataSocket : public Networking::IDataSocket {
private:
    ByteList input_byte_queue_;
    Endpoint source_endpoint_;
    Endpoint destination_endpoint_;
    Port source_port_;
    Port destination_port_;
    Router& router_;
    Utility::Logger logger_;

public:
    TestDataSocket(
        Endpoint source_endpoint,
        Port source_port, 
        Endpoint destination_endpoint, 
        Port destination_port,
        Router& router,
        const Utility::Logger& logger);

    TestDataSocket(const TestDataSocket& other) = delete;
    TestDataSocket(TestDataSocket&& other) = default;

    Port getPort() const;
    Endpoint getEndpoint() const;

    void consumePacket(const Packet& packet);

    void sendData(const std::vector<std::uint8_t>& data) override;
    std::vector<std::uint8_t> receiveData(std::size_t number_of_bytes) override;
    void connect() override;
    void close() override;
};

#endif
