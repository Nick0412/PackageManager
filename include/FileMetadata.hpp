#ifndef FILE_METADATA_HPP
#define FILE_METADATA_HPP

#include "ByteBuffer.hpp"

#include <cstddef>
#include <string>
#include <vector>

class FileMetadata {
private:
  std::uint32_t file_name_length;
  std::string file_name;
  std::uint32_t file_size;
  std::vector<std::byte> file_contents;

public:
  FileMetadata(std::uint32_t file_name_length, const std::string &file_name,
               std::uint32_t file_size, std::vector<std::byte> &file_contents);

  std::size_t size() const;
  static FileMetadata Deserialize(const ByteBuffer &byte_buffer);
  static ByteBuffer Serialize(const FileMetadata &metadata);
};

#endif
