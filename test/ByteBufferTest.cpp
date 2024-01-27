#include "ByteBuffer.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>

void TestByteBufferVectorConstructor() {
  std::vector<std::byte> data = {
      std::byte{0x12}, std::byte{0x34}, std::byte{0xDC}, std::byte{0xFA},
      std::byte{0xAC}, std::byte{0x11}, std::byte{0x22}, std::byte{0x33},
      std::byte{0x44}, std::byte{0x55}};
  ByteBuffer buffer{data};

  assert(buffer.getByteAtIndex(0) == std::byte{0x12});
  assert(buffer.getByteAtIndex(1) == std::byte{0x34});
  assert(buffer.getByteAtIndex(4) == std::byte{0xAC});
  assert(buffer.getByteAtIndex(8) == std::byte{0x44});
  assert(buffer.get32BitUnsignedIntegerAtIndex(4) == std::uint32_t{0x332211AC});
}

void TestEndToEndByteBuffer() {
  ByteBuffer buffer{32};
  buffer.putByteAtIndex(std::byte{69}, 0);
  buffer.putByteAtIndex(std::byte{0x69}, 1);
  buffer.put32BitUnsignedIntegerAtIndex(std::uint32_t{0x90ABCDEF}, 2);
  buffer.putByteListAtIndex({std::byte{0x12}, std::byte{0x34}}, 6);

  assert(buffer.getByteAtIndex(0) == std::byte{69});
  assert(buffer.getByteAtIndex(1) == std::byte{0x69});
  assert(buffer.get32BitUnsignedIntegerAtIndex(2) == std::uint32_t{0x90ABCDEF});
  assert(buffer.getByteAtIndex(7) == std::byte{0x34});
}

void TestByteBufferWrite() {
  ByteBuffer buffer{12};
  buffer.writeByte(std::byte{26})
      .write32BitUnsignedInteger(0x12345678)
      .writeByteList({std::byte{0x11}, std::byte{0x22}})
      .writeString("test");

  assert(buffer.getByteAtIndex(0) == std::byte{26});
  assert(buffer.get32BitUnsignedIntegerAtIndex(1) == std::uint32_t{0x12345678});
  assert(buffer.getByteAtIndex(5) == std::byte{0x11});
  assert(buffer.getByteAtIndex(6) == std::byte{0x22});
  assert(buffer.getByteAtIndex(7) == static_cast<std::byte>('t'));
  assert(buffer.getByteAtIndex(8) == static_cast<std::byte>('e'));
  assert(buffer.getByteAtIndex(9) == static_cast<std::byte>('s'));
  assert(buffer.getByteAtIndex(10) == static_cast<std::byte>('t'));
}

void TestByteBufferRead() {
  std::vector<std::byte> data = {
      std::byte{0x12}, std::byte{0x34}, std::byte{0xDC}, std::byte{0xFA},
      std::byte{0xAC}, std::byte{0x11}, std::byte{0x22}, std::byte{0x43},
      std::byte{0x41}, std::byte{0x54}};
  ByteBuffer buffer{data};

  std::byte test_byte;
  std::uint32_t test_int;
  std::vector<std::byte> test_byte_list;
  std::string test_string;

  test_byte = buffer.readByte();
  test_int = buffer.read32BitUnsignedInteger();
  test_byte_list = buffer.readByteList(2);
  test_string = buffer.readString(3);

  assert(test_byte == std::byte{0x12});
  assert(test_int == std::uint32_t{0xACFADC34});
  assert(test_byte_list[0] == std::byte{0x11});
  assert(test_byte_list[1] == std::byte{0x22});
  assert(test_string == "CAT");
}

int main() {
  TestByteBufferVectorConstructor();
  TestEndToEndByteBuffer();
  TestByteBufferWrite();
  TestByteBufferRead();
  return 0;
}
