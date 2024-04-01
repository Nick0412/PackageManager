#ifndef NETWORKING_UTILITIES_HPP
#define NETWORKING_UTILITIES_HPP

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace Networking::Utilities
{
    constexpr std::size_t MIN_IPV4_STRING_SIZE = 7;
    constexpr std::size_t MAX_IPV4_STRING_SIZE = 15;
    constexpr std::size_t IPV4_BLOCKS = 4;

    constexpr std::int32_t SOCKET_SEND_ERROR = -1;
    constexpr std::int32_t SOCKET_RECV_ERROR = -1;

    std::array<std::uint8_t, 4> ConvertIPv4StringToArray(const std::string& ipv4_string);
    std::string ConvertIPv4ArrayToString(const std::array<std::uint8_t, 4>& ipv4_array);
    void ValidateIPv4StringBlocks(const std::vector<std::string>& ipv4_strings);
    
    void SendDataOverNetworkSocket(int raw_socket, const std::vector<std::byte>& byte_data);
    std::vector<std::byte> ReceiveDataOverNetworkSocket(int raw_socket, const std::size_t number_of_bytes_to_receive);
}

#endif
