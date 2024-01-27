#include "ByteBuffer.hpp"
#include "SerializationHelper.hpp"

ByteBuffer::ByteBuffer(std::size_t byte_buffer_size)
    : raw_byte_buffer{byte_buffer_size} {}

ByteBuffer::ByteBuffer(const std::vector<std::byte> &byte_list_to_wrap)
    : raw_byte_buffer{byte_list_to_wrap} {}

void ByteBuffer::putByteAtIndex(std::byte byte, std::size_t index) {
  raw_byte_buffer[index] = byte;
}

void ByteBuffer::put32BitUnsignedIntegerAtIndex(std::uint32_t value,
                                                std::size_t index) {
  std::vector<std::byte> serialized_value =
      SerializationHelper::Serialize32BitUnsignedInt(value);
  putByteListAtIndex(serialized_value, index);
}

void ByteBuffer::putByteListAtIndex(const std::vector<std::byte> &byte_list,
                                    std::size_t index) {
  for (std::byte byte : byte_list) {
    putByteAtIndex(byte, index++);
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
