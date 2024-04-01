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

####################################################################################################
# FUNCTION INVOCATIONS
####################################################################################################
enable_testing()

####################################################################################################
# INCLUDES AND PACKAGES
####################################################################################################
find_package(GTest REQUIRED)
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

    "src/Strings/Utilities.cpp"
    
    "src/Networking/Utilities.cpp"
    "src/Networking/IPv4Address.cpp"
    "src/Networking/NetworkDataSocket.cpp"
    "src/Networking/NetworkListeningSocket.cpp"
    "src/Networking/SocketOptions.cpp")
target_include_directories(SuperLib PUBLIC "include")

####################################################################################################
# EXECUTABLES
####################################################################################################
add_executable(ClientSocketTest "test/TodoReworkFolder/ClientSocketTest.cpp")
target_include_directories(ClientSocketTest PUBLIC "include")
target_link_libraries(ClientSocketTest SuperLib)

add_executable(ServerSocketTest "test/TodoReworkFolder/ServerSocketTest.cpp")
target_include_directories(ServerSocketTest PUBLIC "include")
target_link_libraries(ServerSocketTest SuperLib)

# TODO: Remove
add_executable(NetworkingV2 "src/NetworkingV2/SocketBase.cpp")

####################################################################################################
# TESTING SECTION       
####################################################################################################
create_test(TEST_NAME "Serialization"       SOURCES "test/Serialization/SerializationHelperTest.cpp" LIBRARIES SuperLib)
create_test(TEST_NAME "WriteByteBuffer"     SOURCES "test/Serialization/WriteByteBufferTest.cpp" LIBRARIES SuperLib)

create_test(TEST_NAME "StringUtilites"      SOURCES "test/Strings/UtilitiesTest.cpp" LIBRARIES SuperLib) 

create_test(TEST_NAME "NetworkingUtilites"  SOURCES "test/Networking/UtilitiesTest.cpp" LIBRARIES SuperLib)
create_test(TEST_NAME "Ipv4Address"         SOURCES "test/Networking/IPv4AddressTest.cpp" LIBRARIES SuperLib) 

create_test(TEST_NAME "BaseSocketInterface" SOURCES "test/NetworkingV2/BaseSocketInterfaceTest.cpp" LIBRARIES SuperLib)

####################################################################################################
# Miscellanious section
####################################################################################################
add_executable(ByteBufferTestExe "test/ByteBufferTest.cpp")
target_include_directories(ByteBufferTestExe PUBLIC "include")
target_link_libraries(ByteBufferTestExe SuperLib)
set_target_properties(ByteBufferTestExe PROPERTIES CXX_STANDARD 20)
