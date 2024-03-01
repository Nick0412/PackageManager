#include "FileMetadata.hpp"
#include "ReadByteBuffer.hpp"
#include "SerializationHelper.hpp"
#include "WriteByteBuffer.hpp"

#include <cassert>
#include <iostream>

void ByteBuffer_Success()
{
    std::byte expectedByte = std::byte{0xAB};
    std::uint32_t expectedInt = 987654321;
    std::vector<std::byte> expectedByteList = {std::byte{0x22}, std::byte{0x44}, std::byte{0x66}, std::byte{0x88}};
    std::string expectedString = "test";
    FileMetadata expectedFileMetadata{"test.cpp", {std::byte{0x12}, std::byte{0x34}, std::byte{0x56}, std::byte{0x78}}};

    WriteByteBuffer writeBuf;

    writeBuf.write(expectedByte)
        .write(expectedInt)
        .write(expectedByteList)
        .write(expectedString)
        .write(expectedFileMetadata);

    std::cout << writeBuf << std::endl;

    std::vector<std::byte> rawBytes = writeBuf.getBytes();

    // simulate sending bytes over network

    ReadByteBuffer readBuf{rawBytes};

    std::cout << std::endl << readBuf << std::endl;

    std::byte actualByte = readBuf.read<std::byte>();
    std::uint32_t actualInt = readBuf.read<std::uint32_t>();
    std::vector<std::byte> actualByteList = readBuf.read<std::vector<std::byte>>();
    std::string actualString = readBuf.read<std::string>();

    std::cout << std::endl << readBuf << std::endl;

    FileMetadata actualFileMetadata = readBuf.read<FileMetadata>();

    std::cout << "File name (" << actualFileMetadata.getFileName().size() << "): " << actualFileMetadata.getFileName()
              << std::endl;
    for (auto b : actualFileMetadata.getFileContents())
        std::cout << static_cast<std::uint32_t>(b) << std::endl;

    assert(expectedByte == actualByte);
    assert(expectedInt == actualInt);
    assert(expectedByteList == actualByteList);
    assert(expectedString == actualString);
    assert(expectedFileMetadata.getFileName() == actualFileMetadata.getFileName());
    assert(expectedFileMetadata.getFileContents() == actualFileMetadata.getFileContents());
}

int main()
{
    ByteBuffer_Success();
    return 0;
}
