#include "gtest/gtest.h"

#include "NetworkingV2/BaseSocketInterface.hpp"

class TestBaseSocket : public BaseSocketInterface<TestBaseSocket>
{
public:
    void closeImplementation()
    {
        // Do nothing.
    }

    std::vector<std::byte> getSocketPropertyImplementation(const std::string& property)
    {
        return { std::byte{0x01}, std::byte{0x02}, std::byte{0x03} };
    }

    void setSocketPropertyImplementation(const std::string& property, const std::vector<std::byte>& value)
    {
        // Do nothing.
    }
};

template <typename T>
void callClose(BaseSocketInterface<T> socket)
{
    socket.close();
}

template <typename T>
std::vector<std::byte> callGetSocketProperty(BaseSocketInterface<T> socket)
{
    return socket.getSocketProperty("test");
}

template <typename T>
void callSetSocketProperty(BaseSocketInterface<T> socket)
{
    socket.setSocketProperty("test", { std::byte{0x01}, std::byte{0x02}, std::byte{0x03} });
}

// Begin tests here

TEST(BaseSocketInterfaceTest, closeTest)
{
    TestBaseSocket base_socket;
    // Make sure no compilation errors occur.
    callClose(base_socket); 
}

TEST(BaseSocketInterfaceTest, getSocketPropertyTest)
{
    TestBaseSocket base_socket;
    auto result = callGetSocketProperty(base_socket);
    auto expected = std::vector<std::byte>{ std::byte{0x01}, std::byte{0x02}, std::byte{0x03} };

    ASSERT_EQ(result, expected);
}

TEST(BaseSocketInterfaceTest, setSocketPropertyTest)
{
    TestBaseSocket base_socket;
    // Make sure no compilation errors occur.
    callSetSocketProperty(base_socket);
}
