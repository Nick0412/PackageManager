// TODO: Remove this file later. It is used as an example on how to use gtest.
#include "gtest/gtest.h"
#include "SerializationHelper.hpp"

TEST(suite_name, actual_test)
{
    EXPECT_EQ(1, 1);
}

TEST(suite_name, fake_test)
{
    SerializationHelper::Serialize32BitUnsignedInt(123);
    EXPECT_EQ(1, 2);
}
