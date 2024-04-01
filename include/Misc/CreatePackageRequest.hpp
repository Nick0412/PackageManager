#ifndef CREATE_PACKAGE_REQUEST_HPP
#define CREATE_PACKAGE_REQUEST_HPP

#include "FileMetadata.hpp"

#include <cstdint>

class CreatePackageRequest
{
  private:
    std::string package_name;
    std::uint32_t package_version;
    std::vector<FileMetadata> header_files;
    std::vector<FileMetadata> static_lib_files;
    std::vector<FileMetadata> shared_lib_files;

  public:
    class CreatePackageRequestBuilder
    {
      private:
        std::string package_name_builder;
        std::uint32_t package_version_builder;
        std::vector<FileMetadata> header_files_builder;
        std::vector<FileMetadata> static_lib_files_builder;
        std::vector<FileMetadata> shared_lib_files_builder;

      public:
        CreatePackageRequestBuilder& withPackageName(const std::string& package_name);
        CreatePackageRequestBuilder& withPackageVersion(std::uint32_t package_version);
        CreatePackageRequestBuilder& withHeaderFiles(const std::vector<FileMetadata>& header_files);
        CreatePackageRequestBuilder& withStaticLibFiles(const std::vector<FileMetadata>& static_lib_files);
        CreatePackageRequestBuilder& withSharedLibFiles(const std::vector<FileMetadata>& shared_lib_files);

        CreatePackageRequest build();
    };

  public:
    CreatePackageRequest() = delete;
    CreatePackageRequest(const std::string& package_name, std::uint32_t package_version,
                         const std::vector<FileMetadata>& header_files,
                         const std::vector<FileMetadata>& static_lib_files,
                         const std::vector<FileMetadata>& shared_lib_files);

    static CreatePackageRequestBuilder Builder();

    std::string getPackageName() const;
    std::uint32_t getPackageVersion() const;
    std::vector<FileMetadata> getHeaderFiles() const;
    std::vector<FileMetadata> getStaticLibFiles() const;
    std::vector<FileMetadata> getSharedLibFiles() const;

    static std::vector<std::byte> Serialize(const CreatePackageRequest& request);
    static CreatePackageRequest Deserialize(const std::span<std::byte>& bytes);
};

#endif
