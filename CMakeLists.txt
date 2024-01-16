cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

add_library(DirectoryHelperLib STATIC "src/DirectoryHelper.cpp")
target_include_directories(DirectoryHelperLib PUBLIC "include")
set_target_properties(DirectoryHelperLib PROPERTIES CXX_STANDARD 20)

add_executable(MainServerTestExecutable "test/MainServerTest.cpp")
target_include_directories(MainServerTestExecutable PUBLIC "include")
target_link_libraries(MainServerTestExecutable DirectoryHelperLib)
set_target_properties(MainServerTestExecutable PROPERTIES CXX_STANDARD 20)
