//
// Created by lan on 2022/7/2.
//

#include <gtest/gtest.h>

TEST(demo, demo) {
  EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}