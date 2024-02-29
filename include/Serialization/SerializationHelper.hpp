#ifndef SERIALIZATION_HELPER_HPP_2
#define SERIALIZATION_HELPER_HPP_2

#include <cstdint>
#include <vector>
#include <span>

namespace Serialization
{
    std::vector<std::byte> Serialize32BitUnsignedInt(std::uint32_t number);
    std::uint32_t Deserialize32BitUnsignedInt(const std::span<std::byte>& bytes);
}

#endif
