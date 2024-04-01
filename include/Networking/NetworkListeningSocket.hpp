#ifndef NETWORK_LISTENING_SOCKET_HPP
#define NETWORK_LISTENING_SOCKET_HPP

#include "IPv4Address.hpp"
#include "ListeningSocketInterface.hpp"
#include "SocketOptions.hpp"

#include <sys/socket.h>

class NetworkListeningSocket : public ListeningSocketInterface
{
private:
    IPv4Address address;
    Port port;
    SocketOptions socket_options;
    int raw_socket;

public:
    NetworkListeningSocket() = delete;
    NetworkListeningSocket(const IPv4Address& address, const Port& port, const SocketOptions& socket_options);

    std::unique_ptr<DataSocketInterface> acceptClient() override;
    void close() override;
};

#endif
