#include "MessageCreator.hpp"

#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <cstdlib>

// TODO: This function is brittle and does no error checking or exception handling.

/**
 * This program is meant to take an INI like file and generate an appropriate header and source file
 * from it. 
 * 
 * Usage: "./MessageGenerator /some/directory/MyRequest.ini"
 * 
 * where "MyRequest.ini" has the following form
 * 
 * NAME=MyFakeRequest
 * FieldOne=TypeOne
 * AnotherFieldHere=std::uint32_t
 * SomeOtherField=std::vector<std::byte>
 * 
 * Note the following:
 * - NAME is required as this defines the message name.
 * - Field names are pascal case.
 * - Types are a subset of standard c++ types.
*/
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Incorrect number of arguments. Expected 1.\n";
        std::cerr << "./GenerateMessageFile.cpp <path to INI file>\n";
        std::exit(EXIT_FAILURE);
    } 

    std::string file_path{argv[1]};
    MessageCreator::CreateMessageFiles(file_path);

    return 0;
}
