#ifndef STRINGS_UTILITIES_HPP
#define STRINGS_UTILITIES_HPP

#include <string>
#include <vector>

namespace Strings::Utilities
{
    std::vector<std::string> SplitString(const std::string& str, char delimiter);
}

#endif
