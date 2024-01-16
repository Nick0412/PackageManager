#include "DirectoryHelper.hpp"

#include <filesystem>

void DirectoryHelper::InitializeDirectories()
{
    std::filesystem::create_directory(ROOT_PACKAGE_DIRECTORY);
    std::filesystem::create_directory(ROOT_PACKAGE_DIRECTORY / INCLUDE_DIRECTORY);
    std::filesystem::create_directory(ROOT_PACKAGE_DIRECTORY / STATIC_LIB_DIRECTORY);
    std::filesystem::create_directory(ROOT_PACKAGE_DIRECTORY / SHARED_LIB_DIRECTORY);
}
