#include <iostream>

/*int main() {
    std::cout << "Google Test" << std::endl;
}*/

#include "gtest/gtest.h"
#include "simplemath.h"

TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, cubic(10));	
}

int main(int argc, char **argv) {
  std::cout << "Google Test" << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}