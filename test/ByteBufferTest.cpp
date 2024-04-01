#include "Misc/CreatePackageRequest.hpp"
#include "Misc/FileMetadata.hpp"
#include "Misc/ReadByteBuffer.hpp"
#include "Misc/RequestHeader.hpp"
#include "Misc/WriteByteBuffer.hpp"

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
    std::vector<std::byte> rawBytes = writeBuf.getBytes();

    // simulate sending bytes over network

    ReadByteBuffer readBuf{rawBytes};

    std::byte actualByte = readBuf.read<std::byte>();
    std::uint32_t actualInt = readBuf.read<std::uint32_t>();
    std::vector<std::byte> actualByteList = readBuf.read<std::vector<std::byte>>();
    std::string actualString = readBuf.read<std::string>();
    FileMetadata actualFileMetadata = readBuf.read<FileMetadata>();

    assert(expectedByte == actualByte);
    assert(expectedInt == actualInt);
    assert(expectedByteList == actualByteList);
    assert(expectedString == actualString);
    assert(expectedFileMetadata.getFileName() == actualFileMetadata.getFileName());
    assert(expectedFileMetadata.getFileContents() == actualFileMetadata.getFileContents());
}

void ByteBuffer_Success_FileMetadataList()
{
    FileMetadata expectedFileMetadata1{"foo.cpp", {std::byte{0xAA}}};
    FileMetadata expectedFileMetadata2{"bar.cpp", {std::byte{0xBB}, std::byte{0xCC}, std::byte{0xDD}}};
    std::vector<FileMetadata> expectedFileMetadataList{expectedFileMetadata1, expectedFileMetadata2};
    std::string expectedString = "test"; // Write and read extra data to verify position pointer is incremented properly

    WriteByteBuffer writeBuf;
    writeBuf.write(expectedFileMetadataList).write(expectedString);
    std::vector<std::byte> rawBytes = writeBuf.getBytes();

    // simulate sending bytes over network

    ReadByteBuffer readBuf{rawBytes};

    std::vector<FileMetadata> actualFileMetadataList = readBuf.read<std::vector<FileMetadata>>();
    std::string actualString = readBuf.read<std::string>();

    assert(expectedFileMetadata1.getFileName() == actualFileMetadataList[0].getFileName());
    assert(expectedFileMetadata1.getFileContents() == actualFileMetadataList[0].getFileContents());
    assert(expectedFileMetadata2.getFileName() == actualFileMetadataList[1].getFileName());
    assert(expectedFileMetadata2.getFileContents() == actualFileMetadataList[1].getFileContents());
    assert(expectedString == actualString);
}

void ByteBuffer_Success_CreatePackageRequest()
{
    RequestHeader expectedHeader = RequestHeader{MessageType::CREATE_PACKAGE_REQUEST, "v1"};
    CreatePackageRequest expectedRequest =
        CreatePackageRequest::Builder()
            .withPackageName("myPackage")
            .withPackageVersion(1)
            .withHeaderFiles({{"foo.h", {std::byte{0xA0}}}, {"bar.h", {std::byte{0xA1}}}})
            .withStaticLibFiles({{"mystatic.a", {std::byte{0xA2}, std::byte{0xA3}}}})
            .withSharedLibFiles({{"myshared.so", {std::byte{0xA4}}}})
            .build();

    WriteByteBuffer writeBuf;
    writeBuf.write(expectedHeader).write(expectedRequest);
    std::vector<std::byte> rawBytes = writeBuf.getBytes();

    // simulate sending bytes over network

    ReadByteBuffer readBuf{rawBytes};

    // std::cout << readBuf << std::endl;

    RequestHeader actualHeader = readBuf.read<RequestHeader>();
    CreatePackageRequest actualRequest = readBuf.read<CreatePackageRequest>();

    assert(expectedHeader.getMessageType() == actualHeader.getMessageType());
    assert(expectedHeader.getProtocolVersion() == actualHeader.getProtocolVersion());
    assert(expectedRequest.getPackageName() == expectedRequest.getPackageName());
    assert(expectedRequest.getPackageVersion() == expectedRequest.getPackageVersion());
}

int main()
{
    ByteBuffer_Success();
    ByteBuffer_Success_FileMetadataList();
    ByteBuffer_Success_CreatePackageRequest();
    return 0;
}
