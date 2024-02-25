#ifndef FILE_METADATA_HPP
#define FILE_METADATA_HPP

#include <span>
#include <string>

class FileMetadata
{
  private:
    std::uint32_t file_name_length;
    std::string file_name;
    std::uint32_t file_size;
    std::vector<std::byte> file_contents;

  public:
    FileMetadata() = delete;
    FileMetadata(std::uint32_t file_name_length, const std::string& file_name, std::uint32_t file_size,
                 const std::vector<std::byte>& file_contents);

    std::string getFileName();
    std::vector<std::byte> getFileContents();

    static std::vector<std::byte> Serialize(const FileMetadata& metadata);
    static FileMetadata Deserialize(const std::span<std::byte>& bytes);
};

#endif
