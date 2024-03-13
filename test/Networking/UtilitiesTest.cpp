#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Networking/Utilities.hpp"

TEST(NetworkingUtilities, ConvertIPv4StringToArraySuccess)
{
    const std::string ipv4_address = "192.168.0.1";
    auto result = Networking::Utilities::ConvertIPv4StringToArray(ipv4_address);

    EXPECT_EQ(result[0], 192);
    EXPECT_EQ(result[1], 168);
    EXPECT_EQ(result[2], 0);
    EXPECT_EQ(result[3], 1);
}

TEST(NetworkingUtilities, ConvertIPv4StringToArrayIncorrectFormat)
{
    const std::string ipv4_address = "192.168.0.500";

    // Expect that a `runtime_error` exception is thrown with the correct message.
    EXPECT_THAT(
        [&]() { Networking::Utilities::ConvertIPv4StringToArray(ipv4_address); },
        ::testing::ThrowsMessage<std::runtime_error>(::testing::HasSubstr("IPv4 address has incorrect format")));
}
