#include "gtest/gtest.h"
#include <iostream>

TEST(module_name1, test_name1) {
    std::cout << "module_name1 test_name1" << std::endl;
    // Google Test will also provide macros for assertions.
    ASSERT_EQ(1+1, 2);
}

