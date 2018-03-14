#include <iostream>
#include <algorithm>
#include "vmath.h"

int main()
{
    mat2x2 A(1.1432f,  4.3240f,  2345.20f, 46.02f);
    mat2x2 B = A.inverse();

  

    std::cout << A   << " |A| = " << A.determinant() << std::endl;
    std::cout << B   << " |B| = " << B.determinant() << std::endl;

    std::cout << A*B << " "       << B*A             << std::endl;

    
    return 0;
}