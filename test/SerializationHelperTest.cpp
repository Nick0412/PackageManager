#include "SerializationHelper.hpp"

#include <cstddef>
#include <iostream>

std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}

void Test32BitUnsignedIntSerialization()
{
    std::uint32_t number = 0xABCDEF00;
    std::vector<std::byte> number_bytes = SerializationHelper::Serialize32BitUnsignedInt(number);
    
    assert(std::to_integer<std::uint32_t>(number_bytes[0]) == 0x00);
    assert(std::to_integer<std::uint32_t>(number_bytes[1]) == 0xEF);
    assert(std::to_integer<std::uint32_t>(number_bytes[2]) == 0xCD);
    assert(std::to_integer<std::uint32_t>(number_bytes[3]) == 0xAB);
}

int main()
{
    Test32BitUnsignedIntSerialization();

    return 0;
}
