#ifndef DIRECTORY_HELPER_H
#define DIRECTORY_HELPER_H

#include <filesystem>
#include <string_view>

namespace DirectoryHelper
{
    const std::filesystem::path ROOT_PACKAGE_DIRECTORY("/opt/CppPackages");
    const std::filesystem::path INCLUDE_DIRECTORY("Include");
    const std::filesystem::path STATIC_LIB_DIRECTORY("StaticLibs"); 
    const std::filesystem::path SHARED_LIB_DIRECTORY("SharedLibs"); 

    void InitializeDirectories();
};

#endif
