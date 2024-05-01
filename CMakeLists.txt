cmake_minimum_required(VERSION 3.24)

project(PackageManager VERSION 1)

####################################################################################################
# GLOBAL VARIABLES
####################################################################################################
# Informs CMake to look in the "cmake" folder when trying to include other files or find packages.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_OSX_ARCHITECTURES "x86_64") # Set for M1 ARM mac

####################################################################################################
# FUNCTION INVOCATIONS
####################################################################################################
enable_testing()

####################################################################################################
# INCLUDES AND PACKAGES
####################################################################################################
# find_package(GTest REQUIRED)
include(CommonUtils)

####################################################################################################
# STATIC LIBRARIES
####################################################################################################
add_library(
    SuperLib STATIC 
    "src/Serialization/SerializationHelper.cpp" 
    "src/Misc/WriteByteBuffer.cpp" 
    "src/Misc/ReadByteBuffer.cpp" 
    "src/Misc/FileMetadata.cpp" 
    "src/Misc/RequestHeader.cpp" 
    "src/Misc/CreatePackageRequest.cpp"

    "src/Utility/Logger.cpp"

    "src/Strings/Utilities.cpp")
target_include_directories(SuperLib PUBLIC "include")

####################################################################################################
# EXECUTABLES
####################################################################################################


####################################################################################################
# TESTING SECTION       
####################################################################################################
# create_test(TEST_NAME "Serialization"       SOURCES "test/Serialization/SerializationHelperTest.cpp" LIBRARIES SuperLib)
# create_test(TEST_NAME "WriteByteBuffer"     SOURCES "test/Serialization/WriteByteBufferTest.cpp" LIBRARIES SuperLib)

# create_test(TEST_NAME "StringUtilites"      SOURCES "test/Strings/UtilitiesTest.cpp" LIBRARIES SuperLib) 

####################################################################################################
# Miscellanious section
####################################################################################################
add_executable(ByteBufferTestExe "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExe PUBLIC "include")
target_link_libraries(ByteBufferTestExe SuperLib)
set_target_properties(ByteBufferTestExe PROPERTIES CXX_STANDARD 20)

add_executable(
    MainTest 
    "test/TodoReworkFolder/MainTest.cpp"
    "test/TodoReworkFolder/Packet.cpp"
    "test/TodoReworkFolder/Router.cpp"
    "test/TodoReworkFolder/TestDataSocket.cpp")
target_include_directories(MainTest PUBLIC "include" "test/TodoReworkFolder")
target_link_libraries(MainTest SuperLib)
set_target_properties(MainTest PROPERTIES CXX_STANDARD 20)
