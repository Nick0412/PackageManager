#include "gtest/gtest.h"
#include "Misc/WriteByteBuffer.hpp"

class TestClassWithSerializeFunction
{
private:
    std::byte test_byte;
    std::uint32_t test_uint32;
public:
    TestClassWithSerializeFunction(std::byte test_byte, std::uint32_t test_uint32)
    : test_byte{test_byte}, test_uint32{test_uint32}
    {

    }

    static std::vector<std::byte> Serialize(TestClassWithSerializeFunction obj)
    {
        WriteByteBuffer writeBuf;
        writeBuf.write(obj.test_byte).write(obj.test_uint32);
        return writeBuf.getBytes();
    }
};

TEST(WriteByteBuffer, TestByteWritten)
{
    std::byte expectedByte = std::byte{0xAB};
    WriteByteBuffer writeBuf;

    writeBuf.write(expectedByte);

    std::vector<std::byte> rawBytes = writeBuf.getBytes();
    EXPECT_EQ(rawBytes[0], expectedByte);
    EXPECT_EQ(rawBytes.size(), 1);
}

TEST(WriteByteBuffer, TestUnsignedInt32Written)
{
    std::uint32_t expectedInt = 987654321;
    WriteByteBuffer writeBuf;

    writeBuf.write(expectedInt);

    std::vector<std::byte> rawBytes = writeBuf.getBytes();
    EXPECT_EQ(rawBytes.size(), 4);
    EXPECT_EQ(rawBytes[0], std::byte{0xB1});
    EXPECT_EQ(rawBytes[1], std::byte{0x68});
    EXPECT_EQ(rawBytes[2], std::byte{0xDE});
    EXPECT_EQ(rawBytes[3], std::byte{0x3A});
}

TEST(WriteByteBuffer, TestByteListWritten)
{
    std::vector<std::byte> expectedByteList = {
        std::byte{0x22}, std::byte{0x44},
        std::byte{0x66}, std::byte{0x88}};
    WriteByteBuffer writeBuf;

    writeBuf.write(expectedByteList);

    std::vector<std::byte> rawBytes = writeBuf.getBytes();
    std::vector<std::byte> expectedBytes = {
        std::byte{0x04}, std::byte{0x00}, std::byte{0x00},
        std::byte{0x00}, std::byte{0x22}, std::byte{0x44},
        std::byte{0x66}, std::byte{0x88}};
    EXPECT_EQ(rawBytes.size(), 8);
    EXPECT_EQ(rawBytes, expectedBytes);
}

TEST(WriteByteBuffer, TestStringWritten)
{
    std::string expectedString = "test";
    WriteByteBuffer writeBuf;

    writeBuf.write(expectedString);

    std::vector<std::byte> rawBytes = writeBuf.getBytes();
    std::vector<std::byte> expectedBytes = {
        std::byte{0x04}, std::byte{0x00}, std::byte{0x00},
        std::byte{0x00}, std::byte{'t'},  std::byte{'e'},
        std::byte{'s'},  std::byte{'t'}};
    EXPECT_EQ(rawBytes.size(), 8);
    EXPECT_EQ(rawBytes, expectedBytes);
}

TEST(WriteByteBuffer, TestComplexObjectWritten)
{
    TestClassWithSerializeFunction obj{std::byte{0xAB}, std::uint32_t{987654321}};
    WriteByteBuffer buf;

    buf.write(obj);

    auto rawBytes = buf.getBytes();
    std::vector<std::byte> expectedBytes = {
        // 4 Bytes for the size of the object, which in this case is size 5.
        std::byte{0x05}, std::byte{0},    std::byte{0},    std::byte{0},
        std::byte{0xAB}, std::byte{0xB1}, std::byte{0x68}, std::byte{0xDE},
        std::byte{0x3A}};
    EXPECT_EQ(rawBytes.size(), 9);
    EXPECT_EQ(rawBytes, expectedBytes);
}

TEST(WriteByteBuffer, TestMultipleTypesWritten)
{
    // Setup
    TestClassWithSerializeFunction obj{std::byte{0xAB}, std::uint32_t{987654321}};
    std::byte expectedByte = std::byte{0xAB};
    std::uint32_t expectedInt = 987654321;
    std::vector<std::byte> expectedByteList = {
        std::byte{0x22}, std::byte{0x44}, std::byte{0x66}, std::byte{0x88}};
    std::string expectedString = "test";

    // Act
    WriteByteBuffer writeBuf;
    writeBuf.write(expectedByte)
        .write(expectedInt)
        .write(expectedByteList)
        .write(expectedString)
        .write(obj);
    
    // Verify
    std::vector<std::byte> rawBytes = writeBuf.getBytes();
    std::vector<std::byte> expectedBytes = {
        std::byte{0xAB}, 
        std::byte{0xB1}, std::byte{0x68}, std::byte{0xDE}, std::byte{0x3A},
        std::byte{0x04}, std::byte{0},    std::byte{0},    std::byte{0}, 
        std::byte{0x22}, std::byte{0x44}, std::byte{0x66}, std::byte{0x88},
        std::byte{0x04}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00},
        std::byte{'t'},  std::byte{'e'},  std::byte{'s'},  std::byte{'t'},
        std::byte{0x05}, std::byte{0},    std::byte{0},    std::byte{0},
        std::byte{0xAB}, std::byte{0xB1}, std::byte{0x68}, std::byte{0xDE},
        std::byte{0x3A}};
    EXPECT_EQ(rawBytes, expectedBytes);
}
