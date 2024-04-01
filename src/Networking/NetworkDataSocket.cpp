#include "Networking/NetworkDataSocket.hpp"
#include "Networking/Utilities.hpp"

#include <unistd.h>

NetworkDataSocket::NetworkDataSocket(int raw_data_socket, const IPv4Address ip_address, Port port, bool connected)
: raw_data_socket{raw_data_socket}, ip_address{ip_address}, port{port}, connected{connected}
{
    if (!connected)
    {
        connected = true;
        auto ip_string = ip_address.getIpAddressString();
        struct sockaddr_in socket_address = { .sin_family = AF_INET, .sin_port = htons(port) };
        inet_aton(ip_string.c_str(), &socket_address.sin_addr);
        ::connect(raw_data_socket, (const sockaddr *)&socket_address, sizeof(socket_address));
    }
}

NetworkDataSocket::NetworkDataSocket(const IPv4Address ip_address, Port port)
: ip_address{ip_address}, port{port}
{
    raw_data_socket = socket(AF_INET, SOCK_STREAM, 0);
    int reuse_addr = 1;
    setsockopt(raw_data_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
    auto ip_string = ip_address.getIpAddressString();
    struct sockaddr_in socket_address = { .sin_family = AF_INET, .sin_port = htons(port) };
    inet_aton(ip_string.c_str(), &socket_address.sin_addr);
    ::connect(raw_data_socket, (const sockaddr *)&socket_address, sizeof(socket_address));
}


void NetworkDataSocket::sendData(const std::vector<std::byte>& data)
{
    Networking::Utilities::SendDataOverNetworkSocket(raw_data_socket, data);
}

std::vector<std::byte> NetworkDataSocket::receiveData(const std::size_t number_of_bytes)
{
    return Networking::Utilities::ReceiveDataOverNetworkSocket(raw_data_socket, number_of_bytes);
}

void NetworkDataSocket::close()
{
    ::close(raw_data_socket);
}
