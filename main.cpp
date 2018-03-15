#include <iostream>
#include <algorithm>
#include "vmath.h"

int main()
{
    mat2x2 A(1.1f,  2.2f,  3.3f, 4.4f);
    mat2x2 B = A.transpose();

    vec2 V(1.1f, 2.2f);

  

    std::cout << A   << " |A| = " << A.determinant() << std::endl;
    std::cout << B   << " |B| = " << B.determinant() << std::endl;

    std::cout << A*B << " "       << B*A             << std::endl;

    std::cout << A*V << std::endl;

    
    return 0;
}