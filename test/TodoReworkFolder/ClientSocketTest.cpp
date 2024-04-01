#include "Networking/NetworkDataSocket.hpp"
#include "Networking/SocketOptions.hpp"

#include <iostream>

// std::ostream& operator<<(std::ostream& os, std::byte data)
// {
//     os << std::to_integer<uint8_t>(data) << " " << data << "\n";
//     return os;
// }

int main()
{
    IPv4Address address("127.0.0.1");
    Port port{35000};
    SocketOptions options;
    NetworkDataSocket data_socket{address, port};

    auto result = data_socket.receiveData(4);

    for (std::size_t i{0}; i < result.size(); i++)
    {
        std::cout << std::to_integer<std::uint8_t>(result[i]) << "\n";
    }

    // std::cout << "Result size: " << result.size();
    // std::cout << result[0] << result[1] << result[2] << result[3];

    return 0;
}
