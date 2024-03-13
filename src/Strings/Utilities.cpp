#include "Strings/Utilities.hpp"

#include <iostream>

std::vector<std::string> Strings::Utilities::SplitString(const std::string& str, char delimiter)
{
    auto str_copy{str};
    std::vector<std::string> result;

    while (!str_copy.empty())
    {
        auto position = str_copy.find(delimiter);
        position = (position == str_copy.npos ? str_copy.size() : position);
        result.push_back(str_copy.substr(0, position));
        str_copy.erase(0, position + 1);
    }

    return result;
}
