#include "ReadByteBuffer.hpp"
#include "Serialization/SerializationHelper.hpp"

#include <iomanip>

ReadByteBuffer::ReadByteBuffer(const std::span<std::byte>& data) : dataBuffer{data}, position{0} {}

template <>
std::byte ReadByteBuffer::read<std::byte>()
{
    return dataBuffer[position++];
}

template <>
std::uint32_t ReadByteBuffer::read<std::uint32_t>()
{
    auto it = dataBuffer.begin() + position;
    std::vector<std::byte> data{it, it + 4};
    position += 4;

    return Serialization::Deserialize32BitUnsignedInt(data);
}

template <>
std::vector<std::byte> ReadByteBuffer::read<std::vector<std::byte>>()
{
    // Read the size of the byte list
    std::uint32_t dataSize = read<std::uint32_t>();

    // Read the byte list
    auto it = dataBuffer.begin() + position;
    std::vector<std::byte> data{it, it + dataSize};
    position += dataSize;

    return data;
}

template <>
std::string ReadByteBuffer::read<std::string>()
{
    // Read the size of the string
    std::uint32_t dataSize = read<std::uint32_t>();

    // Read the string
    auto it = dataBuffer.begin() + position;
    std::string data;
    data.resize(dataSize);
    std::transform(it, it + dataSize, data.begin(), [](std::byte byte) { return static_cast<char>(byte); });
    position += dataSize;

    return data;
}

std::ostream& operator<<(std::ostream& os, const ReadByteBuffer& buf)
{
    os << "Position: " << buf.position << std::endl;

    std::uint8_t count = 0;
    for (std::byte byte : buf.dataBuffer)
    {
        std::uint32_t value = static_cast<std::uint32_t>(byte);
        char charValue = static_cast<char>(byte);
        if (value < 32 || value > 126) // Check if char is printable
            charValue = ' ';

        os << std::hex << std::setw(2) << std::setfill('0') << value << std::dec;
        os << " (" << charValue << ") ";

        if (++count % 16 == 0) // Print 16 bytes per line
            os << std::endl;
    }

    return os;
}
