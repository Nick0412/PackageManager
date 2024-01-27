#ifndef SERIALIZATION_HELPER_HPP
#define SERIALIZATION_HELPER_HPP

#include <cstdint>
#include <vector>

namespace SerializationHelper
{
    std::vector<std::byte> Serialize32BitUnsignedInt(std::uint32_t number);
    std::uint32_t Deserialize32BitUnsignedInt(const std::vector<std::byte>& bytes);
};

#endif
