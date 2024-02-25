#include "FileMetadata.hpp"
#include "ReadByteBuffer.hpp"
#include "WriteByteBuffer.hpp"

FileMetadata::FileMetadata(std::uint32_t file_name_length, const std::string& file_name, std::uint32_t file_size,
                           const std::vector<std::byte>& file_contents)
    : file_name_length{file_name_length}, file_name{file_name}, file_size{file_size}, file_contents{file_contents}
{
}

std::string FileMetadata::getFileName() { return file_name; }

std::vector<std::byte> FileMetadata::getFileContents() { return file_contents; }

std::vector<std::byte> FileMetadata::Serialize(const FileMetadata& metadata)
{
    WriteByteBuffer writeBuf;
    writeBuf.write(metadata.file_name_length)
        .write(metadata.file_name)
        .write(metadata.file_size)
        .write(metadata.file_contents);
    return writeBuf.getBytes();
}

FileMetadata FileMetadata::Deserialize(const std::span<std::byte>& bytes)
{
    ReadByteBuffer readBuf{bytes};
    std::uint32_t file_name_length = readBuf.read<std::uint32_t>(); // can remove
    std::string file_name = readBuf.read<std::string>();
    std::uint32_t file_size = readBuf.read<std::uint32_t>(); // can remove
    std::vector<std::byte> file_contents = readBuf.read<std::vector<std::byte>>();
    return FileMetadata{file_name_length, file_name, file_size, file_contents};
}
