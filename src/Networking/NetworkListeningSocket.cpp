#include "Networking/NetworkListeningSocket.hpp"
#include "Networking/NetworkDataSocket.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

NetworkListeningSocket::NetworkListeningSocket(const IPv4Address& address, const Port& port, const SocketOptions& socket_options)
: address{address}, port{port}, socket_options{socket_options}
{
    // TODO: Eventually move options into SocketOptions object.
    raw_socket = socket(AF_INET, SOCK_STREAM, 0);
    int reuse_addr = 1;
    setsockopt(raw_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));

    // TODO: Wrap POSIX sockaddr in structs in high level type.
    struct sockaddr_in socket_inet_address = { .sin_family = AF_INET, .sin_port = htons(port) };
    // TODO: Make binding address to sockaddr in a network utility function.
    inet_pton(AF_INET, address.getIpAddressString().c_str(), &(socket_inet_address.sin_addr));
    // TODO: Abstract these bind calls
    socklen_t socket_address_size = sizeof(sockaddr_in);
    bind(raw_socket, (sockaddr*)(&socket_inet_address), socket_address_size);
    // TODO: Abstract listen call and make number of connections configurable.
    listen(raw_socket, 64);
}

std::unique_ptr<DataSocketInterface> NetworkListeningSocket::acceptClient()
{
    struct sockaddr_in client_connected_socket_address;
    socklen_t client_connected_socket_address_size;

    // TODO: Abstract accept call
    int client_connected_socket = accept(raw_socket, (struct sockaddr*)&client_connected_socket_address, &client_connected_socket_address_size);
    int reuse_addr = 1;
    setsockopt(client_connected_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));

    // TODO: general clean up
    auto raw_ip_string = inet_ntoa(client_connected_socket_address.sin_addr);
    auto raw_port = ntohs(client_connected_socket_address.sin_port);

    Port port{raw_port};
    IPv4Address ip_address{raw_ip_string};

    return std::make_unique<NetworkDataSocket>(client_connected_socket, ip_address, port, true);
}

void NetworkListeningSocket::close() 
{
    ::close(raw_socket);
}
