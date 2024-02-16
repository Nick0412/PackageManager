#include "ByteBuffer.hpp"
#include "SerializationHelper.hpp"

ByteBuffer::ByteBuffer(std::size_t byte_buffer_size)
    : raw_byte_buffer{byte_buffer_size}, position{0}, read_position{0} {}

ByteBuffer::ByteBuffer(const std::vector<std::byte> &byte_list_to_wrap)
: raw_byte_buffer{byte_list_to_wrap}, position{0}, read_position{0}
{

}

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

std::byte ByteBuffer::getByteAtIndex(std::size_t index) {
  return raw_byte_buffer[index];
}

std::uint32_t ByteBuffer::get32BitUnsignedIntegerAtIndex(std::size_t index) {
  auto it = raw_byte_buffer.begin() + index;
  std::vector<std::byte> data(it, it + 4);
  return SerializationHelper::Deserialize32BitUnsignedInt(data);
}

std::vector<std::byte> ByteBuffer::getByteListAtIndex(std::size_t size,
                                                      std::size_t index) {
  auto it = raw_byte_buffer.begin() + index;
  std::vector<std::byte> data(it, it + size);
  return data;
}

std::string ByteBuffer::getStringAtIndex(std::size_t size, std::size_t index) {
  std::string data;
  for (std::size_t i = index; i < index + size; ++i) {
    data += static_cast<char>(getByteAtIndex(i));
  }
  return data;
}

// Write functions

ByteBuffer& ByteBuffer::write(std::byte value)
{
    putByteAtIndex(value, position);
    position += 1;
    return *this;
}

ByteBuffer& ByteBuffer::write(std::uint32_t value)
{
    put32BitUnsignedIntegerAtIndex(value, position);
    position += 4;
    return *this;
}

ByteBuffer& ByteBuffer::write(const std::vector<std::byte>& value)
{
    putByteListAtIndex(value, position);
    position += value.size();
    return *this;
}

ByteBuffer& ByteBuffer::write(const std::string& value)
{
    putStringAtIndex(value, position);
    position += value.size();
    return *this;
}

ByteBuffer& ByteBuffer::write(const ByteBuffer& value)
{
    putByteListAtIndex(value.raw_byte_buffer, position);
    position += value.raw_byte_buffer.size();
    return *this;
}

template <>
std::byte ByteBuffer::read<std::byte>()
{
    std::byte value = getByteAtIndex(read_position);
    read_position += 1;
    return value;
}

template <>
std::string ByteBuffer::read<std::string>()
{
    std::uint32_t value_length = get32BitUnsignedIntegerAtIndex(read_position);
    read_position += 4;

    std::string value = getStringAtIndex(value_length, read_position);
    read_position += value_length;

    return value;
}

template <>
std::uint32_t ByteBuffer::read<std::uint32_t>()
{
    std::uint32_t value = get32BitUnsignedIntegerAtIndex(read_position);
    read_position += 4;
    return value;
}

template <>
std::vector<std::byte> ByteBuffer::read<std::vector<std::byte>>()
{
    std::uint32_t value_length = get32BitUnsignedIntegerAtIndex(read_position);
    read_position += 4;

    std::vector<std::byte> value = getByteListAtIndex(value_length, read_position);
    read_position += value_length;
    
    return value;
}
