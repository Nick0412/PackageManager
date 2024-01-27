#ifndef BYTE_BUFFER_HPP
#define BYTE_BUFFER_HPP

#include <vector>
#include <string>

/**
 * @class ByteBuffer ByteBuffer.h
 *
 * @brief This class is meant to represent a raw list of bytes. It can be used
 * to
 */
class ByteBuffer {
private:
  std::vector<std::byte> raw_byte_buffer;
  std::size_t position;

public:
  ByteBuffer() = delete;
  ByteBuffer(std::size_t byte_buffer_size);
  ByteBuffer(const std::vector<std::byte> &byte_list_to_wrap);

  void putByteAtIndex(std::byte value, std::size_t index);
  void put32BitUnsignedIntegerAtIndex(std::uint32_t value, std::size_t index);
  void putByteListAtIndex(const std::vector<std::byte> &value,
                          std::size_t index);
  void putStringAtIndex(const std::string &value, std::size_t index);

  std::byte readByteAtIndex(std::size_t index);
  std::uint32_t read32BitUnsignedIntegerAtIndex(std::size_t index);

  ByteBuffer &writeByte(std::byte value);
  ByteBuffer &write32BitUnsignedInteger(std::uint32_t value);
  ByteBuffer &writeByteList(const std::vector<std::byte> &value);
  ByteBuffer &writeString(const std::string &value);
};

#endif