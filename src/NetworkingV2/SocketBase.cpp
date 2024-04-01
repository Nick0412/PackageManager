#include <concepts>
#include <cstdint>
#include <variant>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <type_traits>

template <typename T>
concept IsBaseSocket = requires(T t, std::string str, std::vector<std::byte> value)
{
    { t.closeImplementation() } -> std::same_as<void>;
    { t.getSocketPropertyImplementation(str) } -> std::same_as<std::vector<std::byte>>;
    { t.setSocketPropertyImplementation(str, value) } -> std::same_as<void>;
};

template <typename T>
concept IsDataSocket = requires(T t, std::vector<std::byte> data, std::size_t number_of_bytes)
{
    { t.connectImplementation() } -> std::same_as<void>;
    { t.sendDataImplementation(data) } -> std::same_as<void>;
    { t.receiveDataImplementation(number_of_bytes) } -> std::same_as<std::vector<std::byte>>;
};

template <typename T>
class BaseSocket
{
public:
    template <IsBaseSocket C = T>
    void close()
    {
        static_cast<C*>(this)->closeImplementation();
    }

    template <IsBaseSocket C = T>
    std::vector<std::byte> getSocketProperty(const std::string& option)
    {
        return static_cast<C*>(this)->getSocketPropertyImplementation(option);
    }

    template <IsBaseSocket C = T>
    void setSocketProperty(const std::string& option, const std::vector<std::byte>& value)
    {
        static_cast<C*>(this)->setSocketPropertyImplementation(option, value);
    }
};

template <typename T>
class BaseDataSocket : public BaseSocket<T>
{
public:
    template <IsDataSocket C = T>
    void connect()
    {
        static_cast<C*>(this)->connectImplementation();
    }

    template <IsDataSocket C = T>
    void sendData(const std::vector<std::byte>& data)
    {
        static_cast<C*>(this)->sendDataImplementation(data);
    }

    template <IsDataSocket C = T>
    std::vector<std::byte> receiveData(std::size_t number_of_bytes)
    {
        return static_cast<C*>(this)->receiveDataImplementation(number_of_bytes);
    }
};

// CRTP
class NetworkDataSocket : public BaseDataSocket<NetworkDataSocket>
{
public:
    friend class BaseDataSocket<NetworkDataSocket>;
    friend class BaseSocket<NetworkDataSocket>;

private:
    void closeImplementation()
    {
        std::cout << "closeImplementation\n";
    }

    std::vector<std::byte> getSocketPropertyImplementation(const std::string& option)
    {
        std::cout << "getSocketPropertyImplementation\n";
        return {};
    }

    void setSocketPropertyImplementation(const std::string& option, const std::vector<std::byte>& value)
    {
        std::cout << "setSocketPropertyImplementation\n";
    }

    void connectImplementation()
    {
        std::cout << "Connect\n";
    }

    void sendDataImplementation(const std::vector<std::byte>& data)
    {
        std::cout << "SendData\n";
    }

    std::vector<std::byte> receiveDataImplementation(std::size_t number_of_bytes)
    {
        std::cout << "ReceiveData\n";
        return {};
    }
};

class FakeSocket : public BaseDataSocket<FakeSocket>
{
public:
    FakeSocket() = default;

public:
    friend class BaseDataSocket<FakeSocket>;
    friend class BaseSocket<FakeSocket>;

private:
    void closeImplementation()
    {
        std::cout << "fakeClose\n";
    }

    std::vector<std::byte> getSocketPropertyImplementation(const std::string& option)
    {
        return {};
    }

    void setSocketPropertyImplementation(const std::string& option, const std::vector<std::byte>& value)
    {
    }
};

template <typename ListenSocketType, typename DS>
concept IsListeningSocket = IsDataSocket<DS> and requires(ListenSocketType t)
{
    { t.acceptImplementation() } -> std::derived_from<BaseDataSocket<DS>>;
};


template <typename T>
class BaseListeningSocket : public BaseSocket<T>
{
public:
    template <typename DS, IsListeningSocket<DS> C = T>
    BaseDataSocket<DS> accept()
    {
        return static_cast<C*>(this)->acceptImplementation();
    }
};

// CRTP
class NetworkListeningSocket : public BaseListeningSocket<NetworkListeningSocket>
{
public:
    friend class BaseListeningSocket<NetworkListeningSocket>;
    friend class BaseSocket<NetworkListeningSocket>;

private:
    NetworkDataSocket acceptImplementation()
    {
        std::cout << "Accepting\n";
        return NetworkDataSocket();
    }
};


template <typename DERIVED>
class A
{
public:
    A()
    {
        std::cout << "Invoked\n";
        // static_assert(std::is_member_function_pointer_v<decltype(&A<DERIVED>::foo));
        // static_assert(std::is_convertible_v<std::remove_reference_t<decltype(this)>, DERIVED*>);
        // static_assert(std::is_convertible_v<DERIVED*, std::remove_reference_t<decltype(this)>>);
        // static_assert(std::is_same_v<decltype(static_cast<DERIVED&>(*this)), std::add_lvalue_reference_t<DERIVED>>);
        // static_assert(std::is_base_of_v<A<DERIVED>, DERIVED>);
    }
};

class X : public A<X>
{
    void foo()
    {

    }
};

class Y : public X
{

};


int main()
{
    X x;
    // A<int> a;
    Y y;
}
