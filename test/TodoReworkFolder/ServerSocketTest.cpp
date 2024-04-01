#include "Networking/NetworkListeningSocket.hpp"
#include "Networking/NetworkDataSocket.hpp"
#include "Networking/SocketOptions.hpp"

#include <iostream>

int main()
{
    IPv4Address address("127.0.0.1");
    Port port{35000};
    SocketOptions options;
    NetworkListeningSocket listen_socket{address, port, options};

    auto data_socket = listen_socket.acceptClient();
    std::cout << "Received connection\n";

    std::vector<std::byte> data = { std::byte{'T'}, std::byte{'e'}, std::byte{'s'}, std::byte{'t'} };
    data_socket->sendData(data);
    data_socket->close();
    listen_socket.close();

    return 0;
}
