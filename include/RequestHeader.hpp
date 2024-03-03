#ifndef REQUEST_HEADER_HPP
#define REQUEST_HEADER_HPP

#include "MessageTypes.hpp"

#include <span>
#include <string>
#include <vector>

class RequestHeader
{
  private:
    MessageType messageType;
    std::string protocolVersion;

  public:
    RequestHeader() = delete;
    RequestHeader(const MessageType& messageType, const std::string& protocolVersion);

    MessageType getMessageType() const;
    std::string getProtocolVersion() const;

    static std::vector<std::byte> Serialize(const RequestHeader& header);
    static RequestHeader Deserialize(const std::span<std::byte>& bytes);
};

#endif
