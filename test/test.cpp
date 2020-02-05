#define BOOST_TEST_MODULE project_test_module

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(project_test_suite)

BOOST_AUTO_TEST_CASE(project_test_case_1)
{
    BOOST_CHECK_MESSAGE(true, "must be true");
}

BOOST_AUTO_TEST_SUITE_END()
