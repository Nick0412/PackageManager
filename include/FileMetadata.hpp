#ifndef FILE_METADATA_HPP
#define FILE_METADATA_HPP

#include <span>
#include <string>
#include <vector>

class FileMetadata
{
  private:
    std::string fileName;
    std::vector<std::byte> fileContents;

  public:
    FileMetadata() = delete;
    FileMetadata(const std::string& fileName, const std::vector<std::byte>& fileContents);

    std::string getFileName() const;
    std::vector<std::byte> getFileContents() const;

    static std::vector<std::byte> Serialize(const FileMetadata& metadata);
    static FileMetadata Deserialize(const std::span<std::byte>& bytes);
};

#endif
