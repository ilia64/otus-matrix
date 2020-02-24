#define BOOST_TEST_MODULE project_test_module

#include <boost/test/unit_test.hpp>
#include "../src/matrix.h"

BOOST_AUTO_TEST_SUITE(project_test_suite)


	BOOST_AUTO_TEST_CASE(project_test_matrix_rect)
	{
		Matrix<int, -1> m;
		m[9][5] = 12;
		assert(m.size() == 1);
		m[9][5] = -1;
		assert(m.size() == 0);
	}

BOOST_AUTO_TEST_SUITE_END()
