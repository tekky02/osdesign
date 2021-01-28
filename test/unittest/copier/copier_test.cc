// file copier_test.cc.
// created by tekky on 2021.1.28.
// © tekky all rights reserved.

#include "copier/copier.h"
#include "gtest/gtest.h"

TEST(CopierTest, args_validation_no_operand) {
  const char *argv[] = {"copier"};
  std::size_t size = sizeof(argv) / sizeof(argv[0]);
  EXPECT_EQ(false, args_validation(argv, size));
}

TEST(CopierTest, args_validation_one_operand) {
  const char *argv[] = {"copier", "source.txt"};
  std::size_t size = sizeof(argv) / sizeof(argv[0]);
  EXPECT_EQ(false, args_validation(argv, size));
}

TEST(CopierTest, args_validation_valid) {
  const char *argv[] = {"copier", "source.txt", "dest.txt"};
  std::size_t size = sizeof(argv) / sizeof(argv[0]);
  EXPECT_EQ(true, args_validation(argv, size));
}
