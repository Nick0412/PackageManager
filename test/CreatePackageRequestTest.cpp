#include "CreatePackageRequest.hpp"

#include <cassert>

void TestSerializeAndDeserialize()
{
    std::string package_name = "CheeseWheel";
    std::uint32_t package_version = 5;
    std::string file_name = "Mouse.hpp";
    std::vector<std::byte> file_contents = { std::byte{0xAB}, std::byte{0x91}, std::byte{0xF5} };
    FileMetadata file_metadata{file_name.size(), file_name, file_contents.size(), file_contents};

    CreatePackageRequest request = CreatePackageRequest::Builder()
        .withPackageNameLength(package_name.size())
        .withPackageName(package_name)
        .withPackageVersion(5)
        .withHeaderFileCount(1)
        .withStaticLibFileCount(0)
        .withSharedLibFileCount(0)
        .withHeaderFiles({file_metadata})
        .build();

    auto serialized_data = CreatePackageRequest::Serialize(request);
    auto deserialized = CreatePackageRequest::Deserialize(serialized_data);

    assert(deserialized.getPackageName() == package_name);
    assert(deserialized.getHeaderFiles()[0].getFileName() == file_name);
    assert(deserialized.getHeaderFiles()[0].getFileContents() == file_contents);
}


int main()
{
    TestSerializeAndDeserialize();
    return 0;
}
