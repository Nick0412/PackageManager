#include "RequestHeader.hpp"
#include "ReadByteBuffer.hpp"
#include "WriteByteBuffer.hpp"

RequestHeader::RequestHeader(const MessageType& messageType, const std::string& protocolVersion)
    : messageType{messageType}, protocolVersion{protocolVersion}
{
}

MessageType RequestHeader::getMessageType() const { return messageType; }

std::string RequestHeader::getProtocolVersion() const { return protocolVersion; }

std::vector<std::byte> RequestHeader::Serialize(const RequestHeader& metadata)
{
    WriteByteBuffer writeBuf;
    writeBuf.write(static_cast<std::underlying_type_t<MessageType>>(metadata.messageType))
        .write(metadata.protocolVersion);
    return writeBuf.getBytes();
}

RequestHeader RequestHeader::Deserialize(const std::span<std::byte>& bytes)
{
    ReadByteBuffer readBuf{bytes};
    MessageType messageType = static_cast<MessageType>(readBuf.read<std::underlying_type_t<MessageType>>());
    std::string protocolVersion = readBuf.read<std::string>();
    return RequestHeader{messageType, protocolVersion};
}
