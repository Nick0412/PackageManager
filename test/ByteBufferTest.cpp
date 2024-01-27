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

  assert(buffer.readByteAtIndex(0) == std::byte{0x12});
  assert(buffer.readByteAtIndex(1) == std::byte{0x34});
  assert(buffer.readByteAtIndex(4) == std::byte{0xAC});
  assert(buffer.readByteAtIndex(8) == std::byte{0x44});
  assert(buffer.read32BitUnsignedIntegerAtIndex(4) ==
         std::uint32_t{0x332211AC});
}

void TestEndToEndByteBuffer() {
  ByteBuffer buffer{32};
  buffer.putByteAtIndex(std::byte{69}, 0);
  buffer.putByteAtIndex(std::byte{0x69}, 1);
  buffer.put32BitUnsignedIntegerAtIndex(std::uint32_t{0x90ABCDEF}, 2);
  buffer.putByteListAtIndex({std::byte{0x12}, std::byte{0x34}}, 6);

  assert(buffer.readByteAtIndex(0) == std::byte{69});
  assert(buffer.readByteAtIndex(1) == std::byte{0x69});
  assert(buffer.read32BitUnsignedIntegerAtIndex(2) ==
         std::uint32_t{0x90ABCDEF});
  assert(buffer.readByteAtIndex(7) == std::byte{0x34});
}

void TestByteBufferCursor() {
  ByteBuffer buffer{12};
  buffer.writeByte(std::byte{26})
      .write32BitUnsignedInteger(0x12345678)
      .writeByteList({std::byte{0x11}, std::byte{0x22}})
      .writeString("test");

  assert(buffer.readByteAtIndex(0) == std::byte{26});
  assert(buffer.read32BitUnsignedIntegerAtIndex(1) ==
         std::uint32_t{0x12345678});
  assert(buffer.readByteAtIndex(5) == std::byte{0x11});
  assert(buffer.readByteAtIndex(6) == std::byte{0x22});
  assert(buffer.readByteAtIndex(7) == static_cast<std::byte>('t'));
  assert(buffer.readByteAtIndex(8) == static_cast<std::byte>('e'));
  assert(buffer.readByteAtIndex(9) == static_cast<std::byte>('s'));
  assert(buffer.readByteAtIndex(10) == static_cast<std::byte>('t'));
}

int main() {
  TestByteBufferVectorConstructor();
  TestEndToEndByteBuffer();
  TestByteBufferCursor();
  return 0;
}
