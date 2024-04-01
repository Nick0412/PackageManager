#ifndef LISTENING_SOCKET_INTERFACE_HPP
#define LISTENING_SOCKET_INTERFACE_HPP

#include "DataSocketInterface.hpp"

#include <memory>

class ListeningSocketInterface
{
public:
    virtual ~ListeningSocketInterface() {};
    
    virtual std::unique_ptr<DataSocketInterface> acceptClient() = 0;
    virtual void close() = 0;
};

#endif
