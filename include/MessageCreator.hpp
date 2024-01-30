#ifndef MESSAGE_CREATOR_HPP
#define MESSAGE_CREATOR_HPP

#include <string>
#include <string_view>
#include <vector>

class MessageCreator
{
public:
    class MessageData
    {
    public:
        using NamedTypesList = std::vector<std::pair<std::string, std::string>>;
        std::string message_name;
        NamedTypesList member_name_and_types;

    public:
        MessageData(const std::string& name, const NamedTypesList& members);
    };

public:
    using ssv = std::string_view;

    /**
     * Header file strings section.
     */
    static constexpr ssv INCLUDE_GUARD_TEMPLATE = "#ifndef {0}_HPP\n#define {0}_HPP\n";
    static constexpr ssv CLASS_DECLARATION_OUTER_TEMPLATE = "class {0}\n";
    static constexpr ssv CLASS_BUILDER_DECLARATION_INNER_TEMPLATE = "\tclass {0}\n";
    static constexpr ssv PRIVATE_MEMBERS_OUTER_TEMPLATE = "\t{0} {1};\n";
    static constexpr ssv BUILDER_DECLARATION_INNER_TEMPLATE = "\tclass {0}Builder\n";
    static constexpr ssv PRIVATE_MEMBERS_BUILDER_INNER_TEMPLATE = "\t\t{0} {1}_builder;\n";
    static constexpr ssv BUILDER_METHODS_DECLARATION_TEMPLATE = "\t\t{0}Builder& with{1}({2} {3});\n";
    static constexpr ssv BUILDER_BUILD_METHOD_TEMPLATE = "\t\t{0} build();\n";
    static constexpr ssv BUILDER_STATIC_METHOD_DECLARATION_TEMPLATE = "\tstatic {0}Builder Builder();\n";
    static constexpr ssv DESERIALIZE_STATIC_METHOD_DECLARATION_TEMPLATE = "\tstatic {0} Deserialize(const std::vector<std::byte>& byte_data);\n";
    static constexpr ssv SERIALIZE_STATIC_METHOD_DECLARATION_TEMPLATE = "\tstatic std::vector<std::byte> Serialize(const {0}& request);\n";
    static constexpr ssv DELETE_CONSTRUCTOR_TEMPLATE = "\t{0}() = delete;\n";
    static constexpr ssv CONSTRUCTOR_DECLARATION_TEMPLATE = "\t{0}(\n{1});\n";
    static constexpr ssv CONSTRUCTOR_PARAMS_TEMPLATE = "\t\t{0} {1},\n";

    static constexpr ssv PUBLIC_BLOCK_DECLARATION = "public:\n";
    static constexpr ssv PRIVATE_BLOCK_DECLARATION = "private:\n";
    static constexpr ssv PUBLIC_BLOCK_INNER_DECLARATION = "\tpublic:\n";
    static constexpr ssv PRIVATE_BLOCK_INNER_DECLARATION = "\tprivate:\n";
    static constexpr ssv OPENING_OUTER_BRACKET = "{\n";
    static constexpr ssv CLOSING_OUTER_BRACKET = "};\n";
    static constexpr ssv OPENING_INNER_BRACKET = "\t{\n";
    static constexpr ssv CLOSING_INNER_BRACKET = "\t};\n";
    static constexpr ssv INCLUDE_GUARD_END = "#endif";
    static constexpr ssv COMMON_INCLUDES = "#include <vector>\n#include <string>\n#include <cstddef>\n#include <cstdint>\n";

    /**
     * Source file strings section.
    */
    static constexpr ssv INCLUDE_HEADER_TEMPLATE = "#include \"{0}.hpp\"\n";
    static constexpr ssv BUILDER_METHOD_DEFINITION_TEMPLATE = "{0}::{0}Builder& {0}::{0}Builder::with{1}({2} {3})\n{{\n\t{3}_builder = {3};\n\treturn *this;\n}}\n\n";
    static constexpr ssv BUILD_METHOD_DEFINITION_TEMPLATE = "{0} {0}::{0}Builder::build()\n{{\n\treturn {0}(\n{1});\n}}\n\n";
    static constexpr ssv BUILD_CONSTRUCTOR_REAL_PARAMS_TEMPLATE = "\t\t{0}_builder,\n";
    static constexpr ssv CONSTRUCTOR_DEFINITION_TEMPLATE = "{0}::{0}(\n{1})\n:{2}\n{{\n\n}}\n\n";
    static constexpr ssv CONSTRUCTOR_DEFINITION_PARAMS_TEMPLATE = "\t\t{0} {1},\n";
    static constexpr ssv CONSTRUCTOR_DEFINITION_INITIALIZER_TEMPLATE = "\t{0}{{{0}}},\n";
    static constexpr ssv STATIC_BUILDER_TEMPLATE = "{0}::{0}Builder {0}::Builder()\n{{\n\treturn {0}::{0}Builder();\n}}\n\n";
    static constexpr ssv DESERIALIZE_DEFINITION_TEMPLATE = "{0} {0}::Deserialize(const std::vector<std::byte>& byte_data)\n{{\n\t//TODO: Implementation here\n}}\n\n";
    static constexpr ssv SERIALIZE_DEFINITION_TEMPLATE = "std::vector<std::byte> {0}::Serialize(const {0}& request)\n{{\n\t//TODO: Implementation here\n}}\n\n";

    /**
     * @brief Converts a pascal case string into upper snake case.
     * 
     *  ex. MyCoolString -> MY_COOL_STRING
    */
    static std::string ConvertStringToUpperSnakeCase(const std::string& input);

    /**
     * @brief Converts a pascal case string into camel case.
     * 
     * ex. MyCoolString -> myCoolString
    */
    static std::string ConvertPascalCaseStringToCamelCase(const std::string& input);

    /**
     * @brief Converts a pascal case string into lower snake case
     * 
     * ex. MyCoolString -> my_cool_string
    */
    static std::string ConvertPascalCaseStringToLowerSnakeCase(const std::string& input);

    static std::string GenerateIncludeGuardBeginning(const MessageData& input);
    static std::string GeneratePrivateMemberDeclarations(const MessageData& input);
    static std::string GenerateBuilderMemberDeclarations(const MessageData& input);
    static std::string GenerateBuilderMethodDeclarations(const MessageData& input);
    static std::string GenerateConstructorParams(const MessageData& input);
    static std::string GenerateBuilderFunctionDefinitions(const MessageData& input);
    static std::string GenerateRealConstructorParams(const MessageData& input);
    static std::string GenerateConstructorDefinitionParams(const MessageData& input);
    static std::string GenerateConstructorMemberInitializer(const MessageData& input);

    static std::string CreateHeaderFileString(const MessageData& input);
    static std::string CreateSourceFileString(const MessageData& input);

public:
    MessageCreator() = delete;
};

#endif
