#include "TestDataSocket.hpp"

#include <iostream>

TestDataSocket::TestDataSocket(
    Endpoint source_endpoint,
    Port source_port, 
    Endpoint destination_endpoint, 
    Port destination_port,
    Router& router,
    const Utility::Logger& logger)
: source_endpoint_{source_endpoint}, 
  destination_endpoint_{destination_endpoint}, 
  source_port_{source_port}, 
  destination_port_{destination_port}, 
  router_{router},
  logger_{logger}
{
}

Port TestDataSocket::getPort() const
{
    return source_port_;
}

Endpoint TestDataSocket::getEndpoint() const
{
    return source_endpoint_;
}

void TestDataSocket::consumePacket(const Packet& packet)
{
    input_byte_queue_.insert(input_byte_queue_.end(), packet.data_.begin(), packet.data_.end());
}

void TestDataSocket::sendData(const std::vector<std::uint8_t>& data)
{
    std::cout << "Bla\n";
    logger_.info("Here");
    std::cout << "Bla2\n";
    Packet packet{source_endpoint_, source_port_, destination_endpoint_, destination_port_, data};
    logger_.info("[SOCKET] Sending packet: id{{{}}}", packet.id_);
    router_.routePacket(packet);
}

std::vector<std::uint8_t> TestDataSocket::receiveData(std::size_t number_of_bytes)
{
    if (number_of_bytes > input_byte_queue_.size())
    {
        auto return_data = input_byte_queue_;
        input_byte_queue_.clear();
        return return_data;
    }
    else
    {
        ByteList return_data{input_byte_queue_.begin(), input_byte_queue_.begin() + number_of_bytes};
        input_byte_queue_.erase(input_byte_queue_.begin(), input_byte_queue_.begin() + number_of_bytes);
        return return_data;
    }
}

void TestDataSocket::connect()
{
}

void TestDataSocket::close()
{
}
