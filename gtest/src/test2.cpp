#include "gtest/gtest.h"
#include <iostream>

TEST(module_name2, test_name2) {
    std::cout << "module_name2 test_name2" << std::endl;
    // Google Test will also provide macros for assertions.
    ASSERT_EQ(1+1, 2);
}

