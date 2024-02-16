#ifndef BYTE_BUFFER_HPP
#define BYTE_BUFFER_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <span>

template <typename T>
concept ComplexMarshallable = requires(T a, std::span<std::byte> b) 
{
    { T::Serialize(a) } -> std::same_as<std::vector<std::byte>>;
    { T::Deserialize(b) } -> std::same_as<T>;
    { T::ComputeBinarySize(a) } -> std::same_as<std::size_t>;
};

template <typename T>
concept PrimitiveMarshallable = std::same_as<T, std::byte> ||
                                std::same_as<T, std::uint32_t> ||
                                std::same_as<T, std::string> ||
                                std::same_as<T, std::vector<std::byte>>;

template <typename T>
concept Marshallable = ComplexMarshallable<T> || PrimitiveMarshallable<T>;

/**
 * @class ByteBuffer ByteBuffer.h
 *
 * @brief This class is meant to represent a raw list of bytes. It can be used
 * to
 */
class ByteBuffer 
{
private:
    std::vector<std::byte> raw_byte_buffer;
    std::size_t position;
    std::size_t read_position;

    void putByteAtIndex(std::byte value, std::size_t index);
    void put32BitUnsignedIntegerAtIndex(std::uint32_t value, std::size_t index);
    void putByteListAtIndex(const std::vector<std::byte> &value, std::size_t index);
    void putStringAtIndex(const std::string &value, std::size_t index);

    std::byte getByteAtIndex(std::size_t index);
    std::uint32_t get32BitUnsignedIntegerAtIndex(std::size_t index);
    std::vector<std::byte> getByteListAtIndex(std::size_t size, std::size_t index);
    std::string getStringAtIndex(std::size_t size, std::size_t index);

public:
    ByteBuffer() = delete;
    ByteBuffer(std::size_t byte_buffer_size);
    ByteBuffer(const std::vector<std::byte> &byte_list_to_wrap);
    
    // std::vector<std::byte> readByteList(std::size_t size);
    // std::string readString(std::size_t size);
    // std::vector<std::byte>& getRawByteBuffer();
    // std::byte readByte();
    // std::uint32_t read32BitUnsignedInteger();

    ByteBuffer& write(std::byte value);
    ByteBuffer& write(std::uint32_t value);
    ByteBuffer& write(const std::vector<std::byte>& value);
    ByteBuffer& write(const std::string& value);
    ByteBuffer& write(const ByteBuffer& value);

    template <ComplexMarshallable T>
    ByteBuffer& write(const T& t)
    {
        auto byte_list = T::Serialize(t);
        write(byte_list);
        return *this;
    }

    template <Marshallable T>
    T read()
    {
        std::span<std::byte> remaining_byte_list(raw_byte_buffer.begin() + read_position, raw_byte_buffer.end());
        T deserialized_object = T::Deserialize(remaining_byte_list);
        read_position += T::ComputeBinarySize(deserialized_object);
        return deserialized_object;
    }
};

template <>
std::byte ByteBuffer::read<std::byte>();

template <>
std::uint32_t ByteBuffer::read<std::uint32_t>();

template <>
std::string ByteBuffer::read<std::string>();

template <>
std::vector<std::byte> ByteBuffer::read<std::vector<std::byte>>();

#endif
