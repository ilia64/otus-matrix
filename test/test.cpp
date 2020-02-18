#define BOOST_TEST_MODULE project_test_module

#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>
#include "../src/matrix.h"

BOOST_AUTO_TEST_SUITE(project_test_suite)

	BOOST_AUTO_TEST_CASE(project_test_rows)
	{
		List<int, -1> list;
		assert(list.size() == 0);
		assert(list.get(1) == -1);

		list.set(10, 20);
		assert(list.get(10) == 20);
		assert(list.get(1) == -1);
		assert(list.size() == 11);

		list.set(10, -1);
		assert(list.get(10) == -1);
		assert(list.get(0) == -1);
		assert(list.size() == 0);
	}

	BOOST_AUTO_TEST_CASE(project_test_iterator_row)
	{
		std::vector<int> v{1, 2, 3, 4, 5};
		List<int, -1> list;

		for (size_t i = 0; i < v.size(); ++i)
		{
			list.set(i, v[i]);
		}

		{
			auto iter = list.begin();
			assert(*(++iter) = 2);
			assert(*(iter++) = 2);
		}

		{
			size_t i = 0;
			for(const auto& value : list)
			{
				assert(value == v[i++]);
			}
		}
	}

	BOOST_AUTO_TEST_CASE(project_test_iterator_list_out_end)
	{
		List<int, -1> list;
		list.set(0, 12);
		auto iter = list.begin();
		iter++;
		assert(iter == list.end());
		++iter;
		++iter;
		assert(*iter == -1);
	}

	BOOST_AUTO_TEST_CASE(project_test_iterator_list_empty_size_10)
	{
		std::vector<int> v;
		List<int, -1> list;
		auto iter = list.begin();
		auto end = list.end(10);
		while (iter++ != end)
		{
			assert(*iter == -1);
			v.emplace_back(*iter);
		}
		assert(v.size() == 10);
	}

BOOST_AUTO_TEST_SUITE_END()
