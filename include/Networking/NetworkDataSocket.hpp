#ifndef NETWORK_DATA_SOCKET_HPP
#define NETWORK_DATA_SOCKET_HPP

#include "DataSocketInterface.hpp"
#include "IPv4Address.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

class NetworkDataSocket : public DataSocketInterface
{
private:
    int raw_data_socket;
    IPv4Address ip_address;
    Port port;
    bool connected;

public:
    NetworkDataSocket(int raw_data_socket, const IPv4Address ip_address, Port port, bool connected);
    NetworkDataSocket(const IPv4Address ip_address, Port port);
    
    void sendData(const std::vector<std::byte>& data) override;
    std::vector<std::byte> receiveData(const std::size_t number_of_bytes) override;
    void close() override;
};

#endif
