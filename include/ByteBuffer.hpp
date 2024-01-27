#ifndef BYTE_BUFFER_HPP
#define BYTE_BUFFER_HPP

#include <vector>

/**
 * @class ByteBuffer ByteBuffer.h
 * 
 * @brief This class is meant to represent a raw list of bytes. It can be used to 
 */
class ByteBuffer
{
private:
    std::vector<std::byte> raw_byte_buffer;

public:
    ByteBuffer() = delete;
    ByteBuffer(std::size_t byte_buffer_size);
    ByteBuffer(const std::vector<std::byte>& byte_list_to_wrap);

    void insertByteAtIndex(std::byte byte, std::size_t index);
    void insert32BitUnsignedIntegerAtIndex(std::uint32_t value, std::size_t index);
    void insertByteListAtIndex(const std::vector<std::byte> byte_list, std::size_t index);

    std::byte readByteAtIndex(std::size_t index);
    std::uint32_t read32BitUnsignedIntegerAtIndex(std::size_t index);
};

#endif
