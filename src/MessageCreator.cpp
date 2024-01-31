#include "MessageCreator.hpp"

#include <algorithm>
#include <numeric>
#include <string>
#include <format>
#include <filesystem>
#include <fstream>
#include <iostream>

MessageCreator::MessageData::MessageData(const std::string& name, const NamedTypesList& members)
: message_name{name}, member_name_and_types{members}
{

}

std::string MessageCreator::ConvertStringToUpperSnakeCase(const std::string& input)
{
    std::string result;
    for (auto it = input.cbegin(); it != input.cend(); it++)
    {
        if (std::isupper(*it) && it != input.cbegin())
        {
            result.push_back('_');
        }
        result.push_back(std::toupper(*it));
    }

    return result;
}

std::string MessageCreator::GenerateIncludeGuardBeginning(const MessageData& input)
{
    std::string upper_snake_case_name = ConvertStringToUpperSnakeCase(input.message_name);
    return std::format(INCLUDE_GUARD_TEMPLATE, upper_snake_case_name);
}

std::string MessageCreator::GeneratePrivateMemberDeclarations(const MessageData& input)
{
    std::string result;
    result.reserve(128);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(
            PRIVATE_MEMBERS_OUTER_TEMPLATE, 
            type, 
            ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    return result;
}

std::string MessageCreator::GenerateBuilderMemberDeclarations(const MessageData& input)
{
    std::string result;
    result.reserve(128);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(
            PRIVATE_MEMBERS_BUILDER_INNER_TEMPLATE,
            type,
            ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    return result;
}

std::string MessageCreator::ConvertPascalCaseStringToCamelCase(const std::string& input)
{
    std::string result{input};
    result[0] = std::tolower(result[0]);
    return result;
}

std::string MessageCreator::ConvertPascalCaseStringToLowerSnakeCase(const std::string& input)
{
    std::string result;
    for (auto it = input.cbegin(); it != input.cend(); it++)
    {
        if (std::isupper(*it) && it != input.cbegin())
        {
            result.push_back('_');
        }
        result.push_back(std::tolower(*it));
    }

    return result;
}

std::string MessageCreator::GenerateBuilderMethodDeclarations(const MessageData& input)
{
    std::string result;
    result.reserve(256);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(
            BUILDER_METHODS_DECLARATION_TEMPLATE,
            input.message_name,
            name,
            type,
            ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    return result;
}

std::string MessageCreator:: GenerateConstructorParams(const MessageData& input)
{
    std::string result;
    result.reserve(128);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(CONSTRUCTOR_PARAMS_TEMPLATE, type, ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    // Remove tailing characters ',' and '\n'.
    result.pop_back();
    result.pop_back();

    return result;
}

std::string MessageCreator::CreateHeaderFileString(const MessageData& input)
{
    std::string result;
    result.reserve(1024);

    result += GenerateIncludeGuardBeginning(input);
    result += "\n";
    result += COMMON_INCLUDES;
    result += "\n";
    result += std::format(CLASS_DECLARATION_OUTER_TEMPLATE, input.message_name);
    result += OPENING_OUTER_BRACKET;
    result += PRIVATE_BLOCK_DECLARATION;
    result += GeneratePrivateMemberDeclarations(input);
    result += "\n";
    result += std::format(BUILDER_DECLARATION_INNER_TEMPLATE, input.message_name);
    result += OPENING_INNER_BRACKET;
    result += PRIVATE_BLOCK_INNER_DECLARATION;
    result += GenerateBuilderMemberDeclarations(input);
    result += "\n";
    result += PUBLIC_BLOCK_INNER_DECLARATION;
    result += GenerateBuilderMethodDeclarations(input);
    result += std::format(BUILDER_BUILD_METHOD_TEMPLATE, input.message_name);
    result += CLOSING_INNER_BRACKET;
    result += "\n";
    result += PUBLIC_BLOCK_DECLARATION;
    result += std::format(BUILDER_STATIC_METHOD_DECLARATION_TEMPLATE, input.message_name);
    result += std::format(DESERIALIZE_STATIC_METHOD_DECLARATION_TEMPLATE, input.message_name);
    result += std::format(SERIALIZE_STATIC_METHOD_DECLARATION_TEMPLATE, input.message_name);
    result += "\n";
    result += std::format(DELETE_CONSTRUCTOR_TEMPLATE, input.message_name);
    result += std::format(CONSTRUCTOR_DECLARATION_TEMPLATE, input.message_name, GenerateConstructorParams(input));
    result += "\n";
    result += CLOSING_OUTER_BRACKET;
    result += "\n";
    result += INCLUDE_GUARD_END;

    return result;
}

std::string MessageCreator::GenerateBuilderFunctionDefinitions(const MessageData& input)
{
    std::string result;
    result.reserve(1024);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(BUILDER_METHOD_DEFINITION_TEMPLATE, input.message_name, name, type, ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    return result;
}

std::string MessageCreator::GenerateRealConstructorParams(const MessageData& input)
{
    std::string result;
    result.reserve(256);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(BUILD_CONSTRUCTOR_REAL_PARAMS_TEMPLATE, ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    // Remove the trailing characters ',' and '\n'
    result.pop_back();
    result.pop_back();

    return result;
}

std::string MessageCreator::GenerateConstructorDefinitionParams(const MessageData& input)
{
    std::string result;
    result.reserve(256);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(CONSTRUCTOR_DEFINITION_PARAMS_TEMPLATE, type, ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    // Remove the trailing characters ',' and '\n'
    result.pop_back();
    result.pop_back();

    return result;
}

std::string MessageCreator::GenerateConstructorMemberInitializer(const MessageData& input)
{
    std::string result;
    result.reserve(256);

    for (auto& [name, type] : input.member_name_and_types)
    {
        result += std::format(CONSTRUCTOR_DEFINITION_INITIALIZER_TEMPLATE, ConvertPascalCaseStringToLowerSnakeCase(name));
    }

    // Remove trailing ',' and '\n' but add '\n' back. This is a lazy way to remove the last comma.
    result.pop_back();
    result.pop_back();
    result.push_back('\n');

    return result;
}

std::string MessageCreator::CreateSourceFileString(const MessageData& input)
{
    std::string result;
    result.reserve(2048);

    result += std::format(INCLUDE_HEADER_TEMPLATE, input.message_name);
    result += "\n";
    result += GenerateBuilderFunctionDefinitions(input);
    result += std::format(BUILD_METHOD_DEFINITION_TEMPLATE, input.message_name, GenerateRealConstructorParams(input));
    result += std::format(CONSTRUCTOR_DEFINITION_TEMPLATE, input.message_name, GenerateConstructorDefinitionParams(input), GenerateConstructorMemberInitializer(input));
    result += std::format(STATIC_BUILDER_TEMPLATE, input.message_name);
    result += std::format(DESERIALIZE_DEFINITION_TEMPLATE, input.message_name);
    result += std::format(SERIALIZE_DEFINITION_TEMPLATE, input.message_name);

    return result;
}

void MessageCreator::CreateMessageFiles(const std::string& file_path_string)
{
    std::filesystem::path file_path{file_path_string};
    std::filesystem::path parent_directory{file_path.parent_path()};
    std::cout << parent_directory << "\n";
    std::ifstream file_stream{file_path};
    MessageData message_data;

    std::string line;
    while (std::getline(file_stream, line))
    {
        auto equals_position = line.find('=');
        std::string key{line.substr(0, equals_position)};
        std::string value{line.substr(equals_position +1 )};

        std::cout << "key: " << std::left << std::setw(20) << key <<  "value: " << value << "\n";

        if (key == "NAME")
        {
            message_data.message_name = value;
        }
        else
        {
            message_data.member_name_and_types.push_back({key, value});
        }
    }

    std::string header_file_name = std::format(HEADER_FILE_TEMPLATE, message_data.message_name);
    std::string source_file_name = std::format(SOURCE_FILE_TEMPLATE, message_data.message_name);

    std::filesystem::path header_file_path = parent_directory / header_file_name;
    std::filesystem::path source_file_path = parent_directory / source_file_name;

    std::cout << header_file_path << "\n";
    std::cout << source_file_path << "\n";

    std::ofstream header_stream{header_file_path};
    std::ofstream source_stream{source_file_path};

    header_stream << CreateHeaderFileString(message_data);
    source_stream << CreateSourceFileString(message_data);
}
