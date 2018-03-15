#include <iostream>
#include <algorithm>
#include "vmath.h"

int main()
{
    vec3 v( 2.0f, -3.0f, -1.0f);
    vec3 u( 1.0f,  4.0f, -2.0f);
    v.normalize();
    u.normalize();
    vec3 x = v.cross_product(u);
   

    std::cout << v << std::endl;
    std::cout << u << std::endl;
    
    std::cout << std::endl;

    std::cout << x << " " << x.length()  << std::endl;
    std::cout << v << " " <<  v.length() << std::endl;
    std::cout << u.orthogonal(x) << std::endl;

    return 0;
}