#include "CreatePackageRequest.hpp"
#include "ByteBuffer.hpp"
#include "MessageTypes.hpp"

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

// TODO: Determine how to separate the header and message body for correct deserialization.
CreatePackageRequest CreatePackageRequest::Deserialize(const std::vector<std::byte>& byte_data)
{
    ByteBuffer byte_buffer{byte_data};

    std::uint32_t message_size = byte_buffer.read32BitUnsignedInteger();
    MessageType message_type = static_cast<MessageType>(byte_buffer.read32BitUnsignedInteger());
    std::uint32_t message_protocol_version = byte_buffer.read32BitUnsignedInteger();

    std::uint32_t package_name_length = byte_buffer.read32BitUnsignedInteger();
    std::string package_name = byte_buffer.readString(package_name_length);
    std::uint32_t package_version = byte_buffer.read32BitUnsignedInteger();
    std::uint32_t header_file_count = byte_buffer.read32BitUnsignedInteger();
    std::uint32_t static_lib_file_count = byte_buffer.read32BitUnsignedInteger();
    std::uint32_t shared_lib_file_count = byte_buffer.read32BitUnsignedInteger();
    
    std::vector<FileMetadata> header_files;
    for (auto i{0}; i < header_file_count; i++)
    {
        header_files.push_back(FileMetadata::Deserialize(byte_buffer));
    }

    std::vector<FileMetadata> static_lib_files;
    for (auto i{0}; i < static_lib_file_count; i++)
    {
        static_lib_files.push_back(FileMetadata::Deserialize(byte_buffer));
    }

    std::vector<FileMetadata> shared_lib_files;
    for (auto i{0}; i < shared_lib_file_count; i++)
    {
        shared_lib_files.push_back(FileMetadata::Deserialize(byte_buffer));
    }

    CreatePackageRequestBuilder builder = CreatePackageRequest::Builder();

    return builder.withPackageNameLength(package_name_length)
        .withPackageName(package_name)
        .withPackageVersion(package_version)
        .withHeaderFileCount(header_file_count)
        .withStaticLibFileCount(static_lib_file_count)
        .withSharedLibFileCount(shared_lib_file_count)
        .withHeaderFiles(header_files)
        .withStaticLibFiles(static_lib_files)
        .withSharedLibFiles(shared_lib_files)
        .build();
}

std::vector<std::byte> CreatePackageRequest::Serialize(const CreatePackageRequest& request)
{
    // TODO: Determine if message size should include header field as well. For now we will assume it does.
    ByteBuffer byte_buffer{request.size()};
    
    byte_buffer.write32BitUnsignedInteger(request.size())
        .write32BitUnsignedInteger(static_cast<std::uint32_t>(MessageType::CREATE_PACKAGE_REQUEST))
        .write32BitUnsignedInteger(1)
        .write32BitUnsignedInteger(request.package_name_length)
        .writeString(request.package_name)
        .write32BitUnsignedInteger(request.package_version)
        .write32BitUnsignedInteger(request.header_file_count)
        .write32BitUnsignedInteger(request.static_lib_file_count)
        .write32BitUnsignedInteger(request.shared_lib_file_count);

    for (auto header_file : request.header_files)
    {
        byte_buffer.writeByteBuffer(FileMetadata::Serialize(header_file));
    }

    for (auto static_lib_file : request.static_lib_files)
    {
        byte_buffer.writeByteBuffer(FileMetadata::Serialize(static_lib_file));
    }

    for (auto shared_lib_file : request.shared_lib_files)
    {
        byte_buffer.writeByteBuffer(FileMetadata::Serialize(shared_lib_file));
    }

    return byte_buffer.getRawByteBuffer();
}

std::uint32_t CreatePackageRequest::size() const
{
    std::uint32_t size{0};
    // TODO make constants not look magic
    size += 12; // Header size
    size += 4;  // Package Name length
    size += package_name_length; // Package Name
    size += 4; // Package version
    size += 4; // Number of header files
    size += 4; // Number of static files
    size += 4; // Number of shared files

    // TODO: Look for accumulate function or something nicer.
    for (auto header_file : header_files)
    {
        size += header_file.size();
    }

    for (auto static_lib_file : static_lib_files)
    {
        size += static_lib_file.size();
    }

    for (auto shared_lib_file : shared_lib_files)
    {
        size += shared_lib_file.size();
    }

    return size;
}

std::string CreatePackageRequest::getPackageName() const
{
    return package_name;
}

std::vector<FileMetadata> CreatePackageRequest::getHeaderFiles()
{
    return header_files;
}
