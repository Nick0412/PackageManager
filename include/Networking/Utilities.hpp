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

    std::array<std::uint8_t, 4> ConvertIPv4StringToArray(const std::string& ipv4_string);
    void ValidateIPv4StringBlocks(const std::vector<std::string>& ipv4_strings);
}

#endif
