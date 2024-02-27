# This function creates a test and links it against google test (gtest) and other specified libraries.
# It can be invoked by calling the following.
# `create_test(TEST_NAME <some_test_name> SOURCES <source_files_for_the_test> LIBRARIES <libs_to_link_against>)`
#
# After creating the test, the tests can be executed by running the "ctest" command.
# `cmake ..`
# `cmake --build .`
# `ctest --verbose`
function (create_test)
    set(options)
    set(oneValueArgs TEST_NAME)
    set(multiValueArgs SOURCES LIBRARIES)
    # This command parses the arguments passed to the "create_test" function and prepends "CREATE_TEST"
    # to each variable. In this case it means we have two variables "CREATE_TEST_TEST_NAME" and
    # "CREATE_TEST_SOURCES".
    cmake_parse_arguments(CREATE_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT DEFINED CREATE_TEST_TEST_NAME)
        message(SEND_ERROR "TEST_NAME can not be empty for create_test")
    endif()

    add_executable(${CREATE_TEST_TEST_NAME} ${CREATE_TEST_SOURCES})
    target_link_libraries(${CREATE_TEST_TEST_NAME} GTest::gtest GTest::gtest_main ${CREATE_TEST_LIBRARIES})
    target_include_directories(${CREATE_TEST_TEST_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
    add_test(NAME "${CREATE_TEST_TEST_NAME}Test" COMMAND ${CREATE_TEST_TEST_NAME} "--verbose")
endfunction()
