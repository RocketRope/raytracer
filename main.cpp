#include <iostream>
#include <algorithm>
#include "vmath.h"

int main()
{
 
    mat3x3 D(1, 1, 0,
              2, 1, 0,
             2, 1,  1 );

    std::cout << D << std::endl;

    mat3x3 A = D.inverse();

    std::cout << A << std::endl;
    std::cout << A*D << std::endl;
    std::cout << D*A << std::endl;

    std::cout << D.transpose() << std::endl;
    

    return 0;
} 