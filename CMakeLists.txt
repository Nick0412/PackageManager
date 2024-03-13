cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

# Informs CMake to look in the "cmake" folder when trying to include other files or find packages.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(CommonUtils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
enable_testing()

find_package(GTest REQUIRED)

add_library(
    SuperLib STATIC 
    "src/Serialization/SerializationHelper.cpp" 
    "src/WriteByteBuffer.cpp" 
    "src/ReadByteBuffer.cpp" 
    "src/FileMetadata.cpp" 
    "src/RequestHeader.cpp" 
    "src/CreatePackageRequest.cpp"

    "src/Strings/Utilities.cpp"
    
    "src/Networking/Utilities.cpp"
    "src/Networking/IPv4Address.cpp")
target_include_directories(SuperLib PUBLIC "include")

add_executable(ByteBufferTestExe "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExe PUBLIC "include")
target_link_libraries(ByteBufferTestExe SuperLib)
set_target_properties(ByteBufferTestExe PROPERTIES CXX_STANDARD 20)


################################################################################
# TESTING SECTION       
################################################################################
create_test(TEST_NAME "Serialization" SOURCES "test/Serialization/SerializationHelperTest.cpp" LIBRARIES SuperLib)
create_test(TEST_NAME "WriteByteBuffer" SOURCES "test/Serialization/WriteByteBufferTest.cpp" LIBRARIES SuperLib)
create_test(TEST_NAME "StringUtilites" SOURCES "test/Strings/UtilitiesTest.cpp" LIBRARIES SuperLib) 
create_test(TEST_NAME "NetworkingUtilites" SOURCES "test/Networking/UtilitiesTest.cpp" LIBRARIES SuperLib)
create_test(TEST_NAME "Ipv4Address" SOURCES "test/Networking/IPv4AddressTest.cpp" LIBRARIES SuperLib) 
