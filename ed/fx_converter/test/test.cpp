#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MyTest)
{
    float x = 9.5f;

    BOOST_CHECK(x != 0.0f);
    BOOST_CHECK_EQUAL((int)x, 9);
    BOOST_CHECK_CLOSE(x, 9.5f, 0.00001f);
}
