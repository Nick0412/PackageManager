#ifndef FILE_METADATA_HPP
#define FILE_METADATA_HPP

#include <cstddef>
#include <vector>
#include <string>

class FileMetadata
{
private:
    std::uint32_t file_name_length;
    std::string file_name;
    std::uint32_t file_size;
    std::vector<std::byte> file_contents;

public:
    FileMetadata(
        std::uint32_t file_name_length, 
        const std::string& file_name, 
        std::uint32_t file_size,
        std::vector<std::byte>& file_contents);
};

#endif
