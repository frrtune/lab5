#include <gtest/gtest.h>
#include "../bit_sequence/bit_sequence.hpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  std::cout << sizeof(Bit) << std::endl;
}
//добавить size в arraySeq (добавление за О(1))