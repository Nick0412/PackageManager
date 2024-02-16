#ifndef SERIALIZATION_HELPER_HPP
#define SERIALIZATION_HELPER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <span>

namespace SerializationHelper
{
    std::vector<std::byte> Serialize32BitUnsignedInt(std::uint32_t number);
    std::uint32_t Deserialize32BitUnsignedInt(const std::vector<std::byte>& bytes);
    std::uint32_t Deserialize32BitUnsignedInt(const std::span<std::byte>& bytes, std::size_t position);

    std::vector<std::byte> SerializeString(const std::string& value);
    std::string DeserializeString(const std::span<std::byte>& bytes);

};

#endif
