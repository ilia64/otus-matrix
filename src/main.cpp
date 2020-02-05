#include <iostream>

#include "matrix.h"

int main()
{
    matrix<int, -99> m;

    m[0][2] = 22;
    std::cout << m[0][2] << std::endl;
    std::cout << m[0][1] << std::endl;
    std::cout << m.size() << std::endl;
    return 0;
}