cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

# enable_testing()
# find_package(GTest REQUIRED)

# message(GTest_FOUND="${GTest_FOUND}")
# message(GTEST_INCLUDE_DIRS="${GTEST_INCLUDE_DIRS}")

# add_library(DirectoryHelperLib STATIC "src/DirectoryHelper.cpp")
# target_include_directories(DirectoryHelperLib PUBLIC "include")
# set_target_properties(DirectoryHelperLib PROPERTIES CXX_STANDARD 20)

# add_executable(MessageGenerator "src/GenerateMessageFile.cpp" "src/MessageCreator.cpp")
# target_include_directories(MessageGenerator PUBLIC "include")
# set_target_properties(MessageGenerator PROPERTIES CXX_STANDARD 20)

add_library(SuperLib STATIC "src/SerializationHelper.cpp" "src/WriteByteBuffer.cpp" "src/ReadByteBuffer.cpp" "src/FileMetadata.cpp")
target_include_directories(SuperLib PUBLIC "include")
set_target_properties(SuperLib PROPERTIES CXX_STANDARD 20)

################################################
# Testing section
################################################

add_executable(ByteBufferTestExe "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExe PUBLIC "include")
target_link_libraries(ByteBufferTestExe SuperLib)
set_target_properties(ByteBufferTestExe PROPERTIES CXX_STANDARD 20)
