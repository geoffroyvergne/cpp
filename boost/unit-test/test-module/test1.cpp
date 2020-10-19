#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( TEST1 )

BOOST_AUTO_TEST_CASE(test1) {
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_SUITE_END()
