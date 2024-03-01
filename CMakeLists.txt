cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

# Informs CMake to look in the "cmake" folder when trying to include other files or find packages.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(CommonUtils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_VERBOSE_MAKEFILE ON)
enable_testing()

find_package(GTest REQUIRED)

add_library(SuperLib STATIC "src/SerializationHelper.cpp" "src/Serialization/SerializationHelper.cpp" "src/WriteByteBuffer.cpp" "src/ReadByteBuffer.cpp" "src/FileMetadata.cpp" "src/RequestHeader.cpp" "src/CreatePackageRequest.cpp")
target_include_directories(SuperLib PUBLIC "include")

create_test(TEST_NAME "Serialization" SOURCES "test/Serialization/SerializationHelperTest.cpp" LIBRARIES SuperLib)

# TODO: Uncomment the below section later after getting all tests with gtest working.
# add_executable(Bla "Test/Test.cpp")
# target_link_libraries(Bla GTest::gtest GTest::gtest_main)

# add_library(DirectoryHelperLib STATIC "src/DirectoryHelper.cpp")
# target_include_directories(DirectoryHelperLib PUBLIC "include")
# set_target_properties(DirectoryHelperLib PROPERTIES CXX_STANDARD 20)

# add_library(SuperLib STATIC "src/SerializationHelper.cpp" "src/ByteBuffer.cpp" "src/CreatePackageRequest.cpp" "src/FileMetadata.cpp")
# target_include_directories(SuperLib PUBLIC "include")
# set_target_properties(SuperLib PROPERTIES CXX_STANDARD 20)

# add_executable(CreatePackageRequestTest "test/CreatePackageRequestTest.cpp")
# target_include_directories(CreatePackageRequestTest PUBLIC "include")
# set_target_properties(CreatePackageRequestTest PROPERTIES CXX_STANDARD 20)
# target_link_libraries(CreatePackageRequestTest SuperLib)

# add_executable(MainServerTestExecutable "test/MainServerTest.cpp")
# target_include_directories(MainServerTestExecutable PUBLIC "include")
# target_link_libraries(MainServerTestExecutable DirectoryHelperLib)
# set_target_properties(MainServerTestExecutable PROPERTIES CXX_STANDARD 20)

# add_executable(SerializationTestExecutable "test/SerializationHelperTest.cpp")
# target_include_directories(SerializationTestExecutable PUBLIC "include")
# set_target_properties(SerializationTestExecutable PROPERTIES CXX_STANDARD 20)
# target_link_libraries(SerializationTestExecutable SuperLib)

# add_executable(ByteBufferTestExecutable "test/ByteBufferTest.cpp")
# target_include_directories(ByteBufferTestExecutable PUBLIC "include")
# set_target_properties(ByteBufferTestExecutable PROPERTIES CXX_STANDARD 20)
# target_link_libraries(ByteBufferTestExecutable SuperLib)

# add_library(SuperLib STATIC "src/SerializationHelper.cpp" "src/ByteBuffer.cpp")
# target_include_directories(SuperLib PUBLIC "include")
# set_target_properties(SuperLib PROPERTIES CXX_STANDARD 20)

# add_executable(MessageGenerator "src/GenerateMessageFile.cpp" "src/MessageCreator.cpp")
# target_include_directories(MessageGenerator PUBLIC "include")
# set_target_properties(MessageGenerator PROPERTIES CXX_STANDARD 20)

add_executable(ByteBufferTestExe "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExe PUBLIC "include")
target_link_libraries(ByteBufferTestExe SuperLib)
set_target_properties(ByteBufferTestExe PROPERTIES CXX_STANDARD 20)
