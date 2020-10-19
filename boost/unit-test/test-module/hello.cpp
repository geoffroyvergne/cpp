#include <boost/test/unit_test.hpp>

int add(int i, int j) {
    return i + j;
}

BOOST_AUTO_TEST_SUITE( HELLO )

BOOST_AUTO_TEST_CASE(universeInOrder) {
    BOOST_CHECK(add(2, 2) == 4);
    BOOST_TEST(2 == 2);
}

BOOST_AUTO_TEST_SUITE_END()
