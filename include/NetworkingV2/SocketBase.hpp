#ifndef SOCKET_BASE_HPP
#define SOCKET_BASE_HPP

#include <concepts>

template <typename T>
concept HasSocketClose = requires(T t)
{
    { t.close_implementation() } -> std::same_as<void>;
};

template <typename T>
class Socket
{
    template <HasSocketClose C = T>
    void close()
    {
        static_cast<C*>(this)->close_implementation();
    }
};

#endif
