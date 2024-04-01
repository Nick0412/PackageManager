#include "Misc/FileMetadata.hpp"
#include "Misc/ReadByteBuffer.hpp"
#include "Misc/WriteByteBuffer.hpp"

FileMetadata::FileMetadata(const std::string& fileName, const std::vector<std::byte>& fileContents)
    : fileName{fileName}, fileContents{fileContents}
{
}

std::string FileMetadata::getFileName() const { return fileName; }

std::vector<std::byte> FileMetadata::getFileContents() const { return fileContents; }

std::vector<std::byte> FileMetadata::Serialize(const FileMetadata& metadata)
{
    WriteByteBuffer writeBuf;
    writeBuf.write(metadata.fileName).write(metadata.fileContents);
    return writeBuf.getBytes();
}

FileMetadata FileMetadata::Deserialize(const std::span<std::byte>& bytes)
{
    ReadByteBuffer readBuf{bytes};
    std::string fileName = readBuf.read<std::string>();
    std::vector<std::byte> fileContents = readBuf.read<std::vector<std::byte>>();
    return FileMetadata{fileName, fileContents};
}
