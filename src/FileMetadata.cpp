#include "FileMetadata.hpp"

FileMetadata::FileMetadata(
        std::uint32_t file_name_length, 
        const std::string& file_name, 
        std::uint32_t file_size,
        std::vector<std::byte>& file_contents) 
: file_name_length{file_name_length}, file_name{file_name}, file_size{file_size}, file_contents{file_contents}
{

}
