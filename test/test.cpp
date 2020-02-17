#define BOOST_TEST_MODULE project_test_module

#include <boost/test/unit_test.hpp>
#include "../src/matrix.h"

BOOST_AUTO_TEST_SUITE(project_test_suite)

	BOOST_AUTO_TEST_CASE(project_test_rows)
	{
		Rows<int, -1> rows;
		assert(rows.size() == 0);
		assert(rows.get(1) == -1);

		rows.set(10, 20);
		assert(rows.get(10) == 20);
		assert(rows.get(1) == -1);
		assert(rows.size() == 11);

		rows.set(10, -1);
		assert(rows.get(10) == -1);
		assert(rows.get(0) == -1);
		assert(rows.size() == 0);
	}

BOOST_AUTO_TEST_SUITE_END()
