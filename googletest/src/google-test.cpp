/*#include <iostream>

int main() {
    std::cout << "Google Test" << std::endl;
}*/

#include "gtest/gtest.h"
#include "simplemath.h"

TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, cubic(10));	
}