#include <iostream>
#include "matrix.h"

int main()
{
    Matrix<int, 0> matrix;

    const size_t SIZE = 10;

    for (size_t i = 0; i < SIZE; ++i)
    {
		matrix[i][i] = matrix[SIZE - 1 - i][i] = i;
    }

	for (int x = 0; x < SIZE; x += 2)
	{
		for (int y = 0; y < SIZE; y += 2)
		{
			matrix[x][y] = matrix[x + 1][y + 1] = 0;
		}
	}

	for(int i = 1; i < 9; ++i)
	{
		bool space = false;
		for(int j = 1; j < 9; ++j)
		{
			if (space)
			{
				std::cout << ' ';
			}
			std::cout << matrix[i][j];
			space = true;
		}
		std::cout << '\n';
	}

	std::cout << matrix.size() << std::endl;

	for (const auto& [key, value] : matrix)
	{
		std::cout << '[';

		bool space = false;
		for (const auto& i : key)
		{
			if (space) std::cout << ", ";
			space = true;
			std::cout << i;
		}

		std::cout << "] = " << value << std::endl;
	}

    return 0;
}
