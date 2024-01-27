#include "SerializationHelper.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>

void Test32BitUnsignedIntSerialization()
{
    std::uint32_t number{0xABCDEF00};
    std::vector<std::byte> number_bytes = SerializationHelper::Serialize32BitUnsignedInt(number);
    
    assert(std::to_integer<std::uint32_t>(number_bytes[0]) == 0x00);
    assert(std::to_integer<std::uint32_t>(number_bytes[1]) == 0xEF);
    assert(std::to_integer<std::uint32_t>(number_bytes[2]) == 0xCD);
    assert(std::to_integer<std::uint32_t>(number_bytes[3]) == 0xAB);
}

void Test32BitUnsignedIntDeserialization()
{
    std::vector<std::byte> bytes = { std::byte{0xEF}, std::byte{0xCD}, std::byte{0xAB}, std::byte{0x89} };
    std::uint32_t number = SerializationHelper::Deserialize32BitUnsignedInt(bytes);

    assert(number == 0x89ABCDEF);
}

void TestEndToEndSerialization()
{
    std::uint32_t number{0xABCDEF01};
    auto byte_list = SerializationHelper::Serialize32BitUnsignedInt(number);
    auto return_number = SerializationHelper::Deserialize32BitUnsignedInt(byte_list);

    assert(number == return_number);
}

int main()
{
    Test32BitUnsignedIntSerialization();
    Test32BitUnsignedIntDeserialization();
    TestEndToEndSerialization();

    return 0;
}
