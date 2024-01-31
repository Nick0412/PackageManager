cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

add_library(DirectoryHelperLib STATIC "src/DirectoryHelper.cpp")
target_include_directories(DirectoryHelperLib PUBLIC "include")
set_target_properties(DirectoryHelperLib PROPERTIES CXX_STANDARD 20)

add_executable(MainServerTestExecutable "test/MainServerTest.cpp")
target_include_directories(MainServerTestExecutable PUBLIC "include")
target_link_libraries(MainServerTestExecutable DirectoryHelperLib)
set_target_properties(MainServerTestExecutable PROPERTIES CXX_STANDARD 20)

add_executable(SerializationTestExecutable "test/SerializationHelperTest.cpp")
target_include_directories(SerializationTestExecutable PUBLIC "include")
set_target_properties(SerializationTestExecutable PROPERTIES CXX_STANDARD 20)
target_link_libraries(SerializationTestExecutable SuperLib)

add_executable(ByteBufferTestExecutable "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExecutable PUBLIC "include")
set_target_properties(ByteBufferTestExecutable PROPERTIES CXX_STANDARD 20)
target_link_libraries(ByteBufferTestExecutable SuperLib)

add_library(SuperLib STATIC "src/SerializationHelper.cpp" "src/ByteBuffer.cpp")
target_include_directories(SuperLib PUBLIC "include")
set_target_properties(SuperLib PROPERTIES CXX_STANDARD 20)

add_executable(MessageGenerator "src/GenerateMessageFile.cpp" "src/MessageCreator.cpp")
target_include_directories(MessageGenerator PUBLIC "include")
set_target_properties(MessageGenerator PROPERTIES CXX_STANDARD 20)
