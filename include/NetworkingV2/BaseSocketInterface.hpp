#ifndef SOCKET_BASE_HPP
#define SOCKET_BASE_HPP

#include <concepts>
#include <cstddef>
#include <string>
#include <vector>

// Constraint that requires certain "socket like" functions to exist for a given type T.
template <typename T>
concept HasBaseSocketProperties = requires(T t, std::string str, std::vector<std::byte> value)
{
    { t.closeImplementation() } -> std::same_as<void>;
    { t.getSocketPropertyImplementation(str) } -> std::same_as<std::vector<std::byte>>;
    { t.setSocketPropertyImplementation(str, value) } -> std::same_as<void>;
};

/**
 * A base socket interface to be used with the curiously recurring template pattern (CRTP). For
 * classes to inherit from this and use it their declarations must be something like the following
 * 
 * class Derived : public BaseSocketInterface<Derived>
 * ...
 * 
 * That way the "this" object pointer can be casted to "Derived" when we use "static_cast".
*/
template <typename T>
class BaseSocketInterface
{
public:
    template <typename C = T> requires HasBaseSocketProperties<C>
    void close()
    {
        static_cast<C*>(this)->closeImplementation();
    }

    template <typename C = T> requires HasBaseSocketProperties<C>
    std::vector<std::byte> getSocketProperty(const std::string& option)
    {
        return static_cast<C*>(this)->getSocketPropertyImplementation(option);
    }

    template <typename C = T> requires HasBaseSocketProperties<T>
    void setSocketProperty(const std::string& option, const std::vector<std::byte>& value)
    {
        static_cast<C*>(this)->setSocketPropertyImplementation(option, value);
    }
};

#endif
