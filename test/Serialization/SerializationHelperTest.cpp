#include "gtest/gtest.h"
#include "Serialization/SerializationHelper.hpp"

TEST(SerializationHelper, SerializeTest)
{
    std::uint32_t number = 0x89ABCDEF;
    auto bytes = Serialization::Serialize32BitUnsignedInt(number);
    auto deserialized_number = Serialization::Deserialize32BitUnsignedInt(bytes);

    EXPECT_EQ(number, deserialized_number);
}
