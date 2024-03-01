#ifndef MESSAGE_TYPES_HPP
#define MESSAGE_TYPES_HPP

#include <cstdint>

enum class MessageType : std::uint32_t
{
    CREATE_PACKAGE_REQUEST = 1,
    INSTALL_PACKAGE_REQUEST = 2,
    UNINSTALL_PACKAGE_REQUEST = 3,
    DESCRIBE_PACKAGE_REQUEST = 4,
    LIST_PACKAGES_REQUEST = 5
};

#endif
