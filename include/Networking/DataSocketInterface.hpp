#ifndef DATA_SOCKET_INTERFACE_HPP
#define DATA_SOCKET_INTERFACE_HPP

#include <vector>

class DataSocketInterface
{
public:
    virtual ~DataSocketInterface() {};
    
    virtual void sendData(const std::vector<std::byte>& data) = 0;
    virtual std::vector<std::byte> receiveData(const std::size_t number_of_bytes) = 0;
    virtual void close() = 0;
};

#endif
