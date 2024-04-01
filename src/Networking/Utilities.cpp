#include "Networking/Utilities.hpp"
#include "Strings/Utilities.hpp"

#include <stdexcept>
#include <sys/socket.h>
#include <format>

std::array<std::uint8_t, 4> Networking::Utilities::ConvertIPv4StringToArray(const std::string& ipv4_address)
{
    auto ip_parts = Strings::Utilities::SplitString(ipv4_address, '.');
    ValidateIPv4StringBlocks(ip_parts);

    std::array<std::uint8_t, 4> result;
    for (std::size_t i{0}; i < IPV4_BLOCKS; i++)
    {
        result[i] = std::stoi(ip_parts[i]);
    }

    return result;
}

void Networking::Utilities::ValidateIPv4StringBlocks(const std::vector<std::string>& ipv4_strings)
{
    if (ipv4_strings.size() != IPV4_BLOCKS)
    {
        throw std::runtime_error(std::format("IPv4 address has an incorrect number of blocks."));
    }

    for (auto& ip_block : ipv4_strings)
    {
        auto ip_block_number = std::stoi(ip_block);
        if (ip_block_number < 0 || ip_block_number > 255)
        {
            throw std::runtime_error(std::format("IPv4 address has incorrect format."));
        }
    }
}

std::string Networking::Utilities::ConvertIPv4ArrayToString(const std::array<std::uint8_t, 4>& ipv4_array)
{
    std::string result;

    for (auto ip_block : ipv4_array)
    {
        result += std::to_string(ip_block);
        result += ".";
    }

    // Remove trailing '.' at the end.
    result.pop_back();

    return result;
}

void Networking::Utilities::SendDataOverNetworkSocket(int raw_socket, const std::vector<std::byte>& byte_data)
{
    std::size_t current_offset{0};
    std::size_t bytes_remaining{byte_data.size()};
    std::size_t attempts{5};

    while (bytes_remaining > 0 && attempts > 0)
    {
        std::size_t bytes_sent = send(raw_socket, byte_data.data() + current_offset, bytes_remaining, 0);
        if (bytes_sent == SOCKET_SEND_ERROR)
        {
            attempts--;
            continue;
        }

        current_offset += bytes_sent;
        bytes_remaining -= bytes_sent;
        attempts = 5;
    }
}

std::vector<std::byte> Networking::Utilities::ReceiveDataOverNetworkSocket(int raw_socket, const std::size_t number_of_bytes_to_receive)
{
    std::vector<std::byte> result{number_of_bytes_to_receive};
    std::size_t current_offset{0};
    std::size_t bytes_remaining{number_of_bytes_to_receive};
    std::size_t attempts{5};

    while (bytes_remaining > 0 && attempts > 0)
    {
        std::size_t bytes_received = recv(raw_socket, result.data() + current_offset, bytes_remaining, 0);
        if (bytes_received == SOCKET_RECV_ERROR)
        {
            attempts--;
            continue;
        }

        current_offset += bytes_received;
        bytes_remaining -= bytes_received;
        attempts = 5;
    }

    return result;
}
