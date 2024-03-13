#include "gtest/gtest.h"
#include "Strings/Utilities.hpp"

TEST(StringUtilities, SplitStringTestSuccess)
{
    const std::string test_str{"192.168.0.1"};
    std::vector<std::string> expected = { "192", "168", "0", "1" };

    auto result = Strings::Utilities::SplitString(test_str, '.');

    EXPECT_EQ(result, expected);
}
