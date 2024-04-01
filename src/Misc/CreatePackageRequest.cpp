#include "Misc/CreatePackageRequest.hpp"
#include "Misc/ReadByteBuffer.hpp"
#include "Misc/WriteByteBuffer.hpp"

CreatePackageRequest::CreatePackageRequest(const std::string& package_name, std::uint32_t package_version,
                                           const std::vector<FileMetadata>& header_files,
                                           const std::vector<FileMetadata>& static_lib_files,
                                           const std::vector<FileMetadata>& shared_lib_files)
    : package_name{package_name}, package_version{package_version}, header_files{header_files},
      static_lib_files{static_lib_files}, shared_lib_files{shared_lib_files}
{
}

CreatePackageRequest::CreatePackageRequestBuilder&
CreatePackageRequest::CreatePackageRequestBuilder::withPackageName(const std::string& package_name)
{
    package_name_builder = package_name;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder&
CreatePackageRequest::CreatePackageRequestBuilder::withPackageVersion(std::uint32_t package_version)
{
    package_version_builder = package_version;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder&
CreatePackageRequest::CreatePackageRequestBuilder::withHeaderFiles(const std::vector<FileMetadata>& header_files)
{
    header_files_builder = header_files;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder&
CreatePackageRequest::CreatePackageRequestBuilder::withStaticLibFiles(const std::vector<FileMetadata>& static_lib_files)
{
    static_lib_files_builder = static_lib_files;
    return *this;
}

CreatePackageRequest::CreatePackageRequestBuilder&
CreatePackageRequest::CreatePackageRequestBuilder::withSharedLibFiles(const std::vector<FileMetadata>& shared_lib_files)
{
    shared_lib_files_builder = shared_lib_files;
    return *this;
}

CreatePackageRequest CreatePackageRequest::CreatePackageRequestBuilder::build()
{
    return CreatePackageRequest(package_name_builder, package_version_builder, header_files_builder,
                                static_lib_files_builder, shared_lib_files_builder);
}

CreatePackageRequest::CreatePackageRequestBuilder CreatePackageRequest::Builder()
{
    return CreatePackageRequest::CreatePackageRequestBuilder();
}

std::string CreatePackageRequest::getPackageName() const { return package_name; }

std::uint32_t CreatePackageRequest::getPackageVersion() const { return package_version; }

std::vector<FileMetadata> CreatePackageRequest::getHeaderFiles() const { return header_files; }

std::vector<FileMetadata> CreatePackageRequest::getStaticLibFiles() const { return static_lib_files; }

std::vector<FileMetadata> CreatePackageRequest::getSharedLibFiles() const { return shared_lib_files; }

std::vector<std::byte> CreatePackageRequest::Serialize(const CreatePackageRequest& request)
{
    WriteByteBuffer write_buf;
    write_buf.write(request.package_name)
        .write(request.package_version)
        .write(request.header_files)
        .write(request.static_lib_files)
        .write(request.shared_lib_files);
    return write_buf.getBytes();
}

CreatePackageRequest CreatePackageRequest::Deserialize(const std::span<std::byte>& bytes)
{
    ReadByteBuffer read_buf{bytes};
    CreatePackageRequestBuilder builder = CreatePackageRequest::Builder();

    return builder.withPackageName(read_buf.read<std::string>())
        .withPackageVersion(read_buf.read<std::uint32_t>())
        .withHeaderFiles(read_buf.read<std::vector<FileMetadata>>())
        .withStaticLibFiles(read_buf.read<std::vector<FileMetadata>>())
        .withSharedLibFiles(read_buf.read<std::vector<FileMetadata>>())
        .build();
}
