#include "WriteByteBuffer.hpp"
#include "SerializationHelper.hpp"

#include <iomanip>
#include <vector>
#include <algorithm>

const std::vector<std::byte>& WriteByteBuffer::getBytes() { return dataBuffer; }

WriteByteBuffer& WriteByteBuffer::write(std::byte data)
{
    dataBuffer.push_back(data);
    return *this;
}

WriteByteBuffer& WriteByteBuffer::write(std::uint32_t data)
{
    std::vector<std::byte> serializedData = SerializationHelper::Serialize32BitUnsignedInt(data);
    dataBuffer.insert(dataBuffer.end(), serializedData.begin(), serializedData.end());
    return *this;
}

WriteByteBuffer& WriteByteBuffer::write(const std::vector<std::byte>& data)
{
    // Write the size of the byte list
    write(data.size());

    // Write the byte list
    dataBuffer.insert(dataBuffer.end(), data.begin(), data.end());
    return *this;
}

WriteByteBuffer& WriteByteBuffer::write(const std::string& data)
{
    // Write the size of the string
    write(data.size());

    // Write the string
    std::transform(data.begin(), data.end(), std::back_inserter(dataBuffer),
                   [](char c) { return static_cast<std::byte>(c); });
    return *this;
}

std::ostream& operator<<(std::ostream& os, const WriteByteBuffer& buf)
{
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
