#include "ByteBuffer.hpp"
#include "SerializationHelper.hpp"

ByteBuffer::ByteBuffer(std::size_t byte_buffer_size)
    : raw_byte_buffer{byte_buffer_size}, position{0} {}

ByteBuffer::ByteBuffer(const std::vector<std::byte> &byte_list_to_wrap)
    : raw_byte_buffer{byte_list_to_wrap}, position{0} {}

void ByteBuffer::putByteAtIndex(std::byte value, std::size_t index) {
  raw_byte_buffer[index] = value;
}

void ByteBuffer::put32BitUnsignedIntegerAtIndex(std::uint32_t value,
                                                std::size_t index) {
  std::vector<std::byte> serialized_value =
      SerializationHelper::Serialize32BitUnsignedInt(value);
  putByteListAtIndex(serialized_value, index);
}

void ByteBuffer::putByteListAtIndex(const std::vector<std::byte> &value,
                                    std::size_t index) {
  for (std::byte byte : value) {
    putByteAtIndex(byte, index++);
  }
}

void ByteBuffer::putStringAtIndex(const std::string &value, std::size_t index) {
  for (char c : value) {
    putByteAtIndex(static_cast<std::byte>(c), index++);
  }
}

std::byte ByteBuffer::readByteAtIndex(std::size_t index) {
  return raw_byte_buffer[index];
}

std::uint32_t ByteBuffer::read32BitUnsignedIntegerAtIndex(std::size_t index) {
  auto it = raw_byte_buffer.begin() + index;
  std::vector<std::byte> data(it, it + 4);
  return SerializationHelper::Deserialize32BitUnsignedInt(data);
}

ByteBuffer &ByteBuffer::writeByte(std::byte value) {
  putByteAtIndex(value, position);
  position += 1;
  return *this;
}

ByteBuffer &ByteBuffer::write32BitUnsignedInteger(std::uint32_t value) {
  put32BitUnsignedIntegerAtIndex(value, position);
  position += 4;
  return *this;
}

ByteBuffer &ByteBuffer::writeByteList(const std::vector<std::byte> &value) {
  putByteListAtIndex(value, position);
  position += value.size();
  return *this;
}

ByteBuffer &ByteBuffer::writeString(const std::string &value) {
  putStringAtIndex(value, position);
  position += value.size();
  return *this;
}
