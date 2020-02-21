#include <iostream>

#include "matrix.h"

int main()
{
    Matrix<int, 0> matrix;

    const size_t SIZE = 10;

    for (size_t i = 0; i < SIZE; ++i)
    {
        matrix[SIZE - 1 - i][i] = i;
        matrix[i][i] = i;
    }



/*    Matrix<int, -99> matrix;

	matrix(0, 2) = 22;
    std::cout << matrix(0, 2).get() << std::endl;
    std::cout << matrix.size() << std::endl;
	matrix(0, 2) = -99;
    std::cout << matrix(0, 2).get() << std::endl;
	std::cout << matrix.size() << std::endl;*/
    return 0;
}