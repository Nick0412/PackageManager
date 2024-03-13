#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Networking/IPv4Address.hpp"

#include <string>

// gtest fixture class for repetitive testing.
class IPv4AddressTest : public ::testing::Test
{
protected:
    inline static const std::string ip_str{"255.144.1.95"};
    inline static const std::array<std::uint8_t, 4> ip_arr{ 1, 12, 123, 255};
    inline static const std::uint8_t ip_block_1 = 222;
    inline static const std::uint8_t ip_block_2 = 33;
    inline static const std::uint8_t ip_block_3 = 1;
    inline static const std::uint8_t ip_block_4 = 198;

    IPv4Address ip_string;
    IPv4Address ip_array;
    IPv4Address ip_blocks;

    IPv4AddressTest()
    : ip_string{ip_str}, ip_array{ip_arr}, ip_blocks{ip_block_1, ip_block_2, ip_block_3, ip_block_4}
    {

    }

    void SetUp() override
    {
        // Nothing to do in override
    }
};

TEST_F(IPv4AddressTest, TestGetIpAddressString)
{
    EXPECT_EQ(ip_string.getIpAddressString(), "255.144.1.95");
    EXPECT_EQ(ip_array.getIpAddressString(), "1.12.123.255");
    EXPECT_EQ(ip_blocks.getIpAddressString(), "222.33.1.198");
}

TEST_F(IPv4AddressTest, TestGetIpAddressIndex)
{
    EXPECT_EQ(ip_string[0], 255);
    EXPECT_EQ(ip_string[3], 95);

    EXPECT_EQ(ip_array[1], 12);
    EXPECT_EQ(ip_array[2], 123);

    EXPECT_EQ(ip_blocks[1], 33);
    EXPECT_EQ(ip_blocks[3], 198);
}
