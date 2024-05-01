#ifndef SOCKET_INTERFACES_HPP
#define SOCKET_INTERFACES_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace Networking
{
    class IBaseSocket
    {
    public:
        virtual ~IBaseSocket() {}
        virtual void close() = 0;
    };

    class IDataSocket : public IBaseSocket
    {
    public:
        virtual ~IDataSocket() {}
        virtual void sendData(const std::vector<std::uint8_t>& data) = 0;
        virtual std::vector<std::uint8_t> receiveData(std::size_t number_of_bytes) = 0;
        virtual void connect() = 0;
    };

    class IListeningSocket : public IBaseSocket
    {
    public:
        virtual std::unique_ptr<IDataSocket> accept() = 0;
    };
}

#endif
