#include "Messages/CreatePackageRequest.hpp"

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withPackageNameLength(std::uint32_t package_name_length)
{
    package_name_length_builder = package_name_length;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withPackageName(const std::string& package_name)
{
    package_name_builder = package_name;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withPackageVersion(std::uint32_t package_version)
{
    package_version_builder = package_version;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withHeaderFileCount(std::uint32_t header_file_count)
{
    header_file_count_builder = header_file_count;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withStaticLibFileCount(std::uint32_t static_lib_file_count)
{
    static_lib_file_count_builder = static_lib_file_count;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withSharedLibFileCount(std::uint32_t shared_lib_file_count)
{
    shared_lib_file_count_builder = shared_lib_file_count;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withHeaderFiles(const std::vector<FileMetadata>& header_files)
{
    header_files_builder = header_files;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withStaticLibFiles(const std::vector<FileMetadata>& static_lib_files)
{
    static_lib_files_builder = static_lib_files;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder& CreatePackageRequest::CreatePackageRequestBuilder::withSharedLibFiles(const std::vector<FileMetadata>& shared_lib_files)
{
    shared_lib_files_builder = shared_lib_files;
    return *this;
}

CreatePackageRequest CreatePackageRequest::CreatePackageRequestBuilder::build()
{
    return CreatePackageRequest(
        package_name_length_builder,
        package_name_builder,
        package_version_builder,
        header_file_count_builder,
        static_lib_file_count_builder,
        shared_lib_file_count_builder,
        header_files_builder,
        static_lib_files_builder,
        shared_lib_files_builder);
}

CreatePackageRequest::CreatePackageRequest(
        std::uint32_t package_name_length,
        std::string package_name,
        std::uint32_t package_version,
        std::uint32_t header_file_count,
        std::uint32_t static_lib_file_count,
        std::uint32_t shared_lib_file_count,
        std::vector<FileMetadata> header_files,
        std::vector<FileMetadata> static_lib_files,
        std::vector<FileMetadata> shared_lib_files)
:   package_name_length{package_name_length},
    package_name{package_name},
    package_version{package_version},
    header_file_count{header_file_count},
    static_lib_file_count{static_lib_file_count},
    shared_lib_file_count{shared_lib_file_count},
    header_files{header_files},
    static_lib_files{static_lib_files},
    shared_lib_files{shared_lib_files}
{

}

CreatePackageRequest::CreatePackageRequestBuilder CreatePackageRequest::Builder()
{
    return CreatePackageRequest::CreatePackageRequestBuilder();
}

CreatePackageRequest CreatePackageRequest::Deserialize(const std::vector<std::byte>& byte_data)
{

}

std::vector<std::byte> CreatePackageRequest::Serialize(const CreatePackageRequest& request)
{
    
}
