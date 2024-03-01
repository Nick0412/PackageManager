#ifndef READ_BYTE_BUFFER_HPP
#define READ_BYTE_BUFFER_HPP

#include <span>

template <typename T>
concept Deserializable = (requires(std::span<std::byte> a) {
                              {
                                  T::Deserialize(a)
                              } -> std::same_as<T>;
                          }) || std::same_as<T, std::byte> || std::same_as<T, std::uint32_t> ||
                         std::same_as<T, std::vector<std::byte>> || std::same_as<T, std::string>;

class ReadByteBuffer
{
  private:
    std::span<std::byte> dataBuffer;
    std::size_t position;

  public:
    ReadByteBuffer() = delete;
    ReadByteBuffer(const std::span<std::byte>& data);

    template <Deserializable T>
    T read()
    {
        // Read the size of the object
        std::uint32_t objectSize = read<std::uint32_t>();

        // Read the object
        auto it = dataBuffer.begin() + position;
        std::span<std::byte> data{it, it + objectSize};
        return T::Deserialize(data);
    }

    friend std::ostream& operator<<(std::ostream& os, const ReadByteBuffer& buffer);
};

template <>
std::byte ReadByteBuffer::read<std::byte>();

template <>
std::uint32_t ReadByteBuffer::read<std::uint32_t>();

template <>
std::vector<std::byte> ReadByteBuffer::read<std::vector<std::byte>>();

template <>
std::string ReadByteBuffer::read<std::string>();

#endif
