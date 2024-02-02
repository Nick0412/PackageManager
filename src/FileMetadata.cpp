#include "FileMetadata.hpp"
#include "ByteBuffer.hpp"

FileMetadata::FileMetadata(std::uint32_t file_name_length,
                           const std::string &file_name,
                           std::uint32_t file_size,
                           std::vector<std::byte> &file_contents)
    : file_name_length{file_name_length}, file_name{file_name},
      file_size{file_size}, file_contents{file_contents} {}

std::size_t FileMetadata::size() const 
{
  // TODO: we can replace size functions with actual fields like file_name_length.
  std::size_t total_size = 0;
  total_size += 4; // file_name_length size
  total_size += file_name.size();
  total_size += 4; // file_size size
  total_size += file_contents.size();
  return total_size;
}

FileMetadata FileMetadata::Deserialize(ByteBuffer &byte_buffer) 
{
    std::uint32_t file_name_length = byte_buffer.read32BitUnsignedInteger();
    std::string file_name = byte_buffer.readString(file_name_length);
    std::uint32_t file_size = byte_buffer.read32BitUnsignedInteger();
    std::vector<std::byte> file_contents = byte_buffer.readByteList(file_size);
    return FileMetadata{file_name_length, file_name, file_size, file_contents};
}

ByteBuffer FileMetadata::Serialize(const FileMetadata &metadata) {
  ByteBuffer buffer{metadata.size()};
  buffer.write32BitUnsignedInteger(metadata.file_name_length)
      .writeString(metadata.file_name)
      .write32BitUnsignedInteger(metadata.file_size)
      .writeByteList(metadata.file_contents);
  return buffer;
}

std::string FileMetadata::getFileName()
{
  return file_name;
}

std::vector<std::byte> FileMetadata::getFileContents()
{
  return file_contents;
}
