#ifndef WRITE_BYTE_BUFFER_HPP
#define WRITE_BYTE_BUFFER_HPP

#include <string>

template <typename T>
concept Serializable = requires(T a) {
                           {
                               T::Serialize(a)
                           } -> std::same_as<std::vector<std::byte>>;
                       };

class WriteByteBuffer
{
  private:
    std::vector<std::byte> dataBuffer;

  public:
    WriteByteBuffer() = default;

    const std::vector<std::byte>& getBytes();

    WriteByteBuffer& write(std::byte data);
    WriteByteBuffer& write(std::uint32_t data);
    WriteByteBuffer& write(const std::vector<std::byte>& data);
    WriteByteBuffer& write(const std::string& data);

    template <Serializable T>
    WriteByteBuffer& write(const T& data)
    {
        write(T::Serialize(data));
        return *this;
    }

    template <Serializable T>
    WriteByteBuffer& write(const std::vector<T>& data)
    {
        // Write the size of the data list
        write(data.size());

        // Write the data list
        for (auto d : data)
            write(T::Serialize(d));
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const WriteByteBuffer& buffer);
};

#endif
