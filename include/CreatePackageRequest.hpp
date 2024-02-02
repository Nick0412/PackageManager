#ifndef CREATE_PACKAGE_REQUEST_HPP
#define CREATE_PACKAGE_REQUEST_HPP

#include "FileMetadata.hpp"

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

class CreatePackageRequest
{
private:
    std::uint32_t package_name_length;
    std::string package_name;
    std::uint32_t package_version;
    std::uint32_t header_file_count;
    std::uint32_t static_lib_file_count;
    std::uint32_t shared_lib_file_count;
    std::vector<FileMetadata> header_files;
    std::vector<FileMetadata> static_lib_files;
    std::vector<FileMetadata> shared_lib_files;

public:
    class CreatePackageRequestBuilder
    {
    private:
        std::uint32_t package_name_length_builder;
        std::string package_name_builder;
        std::uint32_t package_version_builder;
        std::uint32_t header_file_count_builder;
        std::uint32_t static_lib_file_count_builder;
        std::uint32_t shared_lib_file_count_builder;
        std::vector<FileMetadata> header_files_builder;
        std::vector<FileMetadata> static_lib_files_builder;
        std::vector<FileMetadata> shared_lib_files_builder;

    public:
        CreatePackageRequestBuilder& withPackageNameLength(std::uint32_t package_name_length);
        CreatePackageRequestBuilder& withPackageName(const std::string& package_name);
        CreatePackageRequestBuilder& withPackageVersion(std::uint32_t package_version);
        CreatePackageRequestBuilder& withHeaderFileCount(std::uint32_t header_file_count);
        CreatePackageRequestBuilder& withStaticLibFileCount(std::uint32_t static_lib_file_count);
        CreatePackageRequestBuilder& withSharedLibFileCount(std::uint32_t shared_lib_file_count);
        CreatePackageRequestBuilder& withHeaderFiles(const std::vector<FileMetadata>& header_files);
        CreatePackageRequestBuilder& withStaticLibFiles(const std::vector<FileMetadata>& static_lib_files);
        CreatePackageRequestBuilder& withSharedLibFiles(const std::vector<FileMetadata>& shared_lib_files);

        CreatePackageRequest build();
    };

public:
    static CreatePackageRequestBuilder Builder();
    static CreatePackageRequest Deserialize(const std::vector<std::byte>& byte_data);
    static std::vector<std::byte> Serialize(const CreatePackageRequest& request);

    CreatePackageRequest() = delete;
    CreatePackageRequest(
        std::uint32_t package_name_length,
        std::string package_name,
        std::uint32_t package_version,
        std::uint32_t header_file_count,
        std::uint32_t static_lib_file_count,
        std::uint32_t shared_lib_file_count,
        std::vector<FileMetadata> header_files,
        std::vector<FileMetadata> static_lib_files,
        std::vector<FileMetadata> shared_lib_files);

    std::string getPackageName() const;
    std::vector<FileMetadata> getHeaderFiles();

    std::uint32_t size() const;
};

#endif
