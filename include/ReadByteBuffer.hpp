#ifndef READ_BYTE_BUFFER_HPP
#define READ_BYTE_BUFFER_HPP

#include <cstdint>
#include <vector>
#include <span>
#include <string>
#include <algorithm>

template <typename T>
struct is_vector : std::false_type {
};

template <typename T>
struct is_vector<std::vector<T>> : std::true_type {
};

template <typename T>
struct remove_vector {
    using type = T;
};

template <typename T>
struct remove_vector<std::vector<T>> {
    using type = T;
};

template <typename T>
using remove_vector_t = typename remove_vector<T>::type;

template <typename T>
concept PrimitiveDeserializable =
    std::same_as<T, std::byte> || std::same_as<T, std::uint32_t> || std::same_as<T, std::string>;

template <typename T>
concept ObjectDeserializable = requires(std::span<std::byte> x) {
                                   {
                                       T::Deserialize(x)
                                   } -> std::same_as<T>;
                               };

template <typename T>
concept Deserializable = ObjectDeserializable<remove_vector_t<T>> || PrimitiveDeserializable<remove_vector_t<T>>;

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
        if constexpr (is_vector<T>::value) // T is a vector
        {
            // Read the size of the vector
            std::uint32_t vectorSize = read<std::uint32_t>();

            // Read each element of the vector
            T result;
            result.reserve(vectorSize);
            std::generate_n(std::back_inserter(result), vectorSize, [this]() { return read<remove_vector_t<T>>(); });

            return result;
        } else // T is an object
        {
            // Read the size of the object
            std::uint32_t objectSize = read<std::uint32_t>();

            // Read the object
            auto it = dataBuffer.begin() + position;
            std::span<std::byte> data{it, it + objectSize};
            position += objectSize;

            return T::Deserialize(data);
        }
    };

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
