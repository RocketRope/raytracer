#include "shapes.h"

#include <cmath>

#include "vmath.h"

//  --  class ray  --  //

// Constructors
Ray::Ray(const Vec3& _dir, const Vec3& _ori)
    : dir{_dir} , ori{_ori} {}


//  --  class Sphere  --  //

// Constructors
Sphere::Sphere(const Vec3& _center, float _radius)
    : center{_center} , radius{_radius} {}

// Override functions
bool Sphere::intersect(const Ray& ray, float& depth) const
{
    Vec3  v = ray.ori - center;
    float ray_dot_v = ray.dir * v;
    
    float x = (ray_dot_v * ray_dot_v) - (v * v) + (radius * radius);

    if ( x < 0.0f )
        return false;

    float sqrt_x = std::sqrt(x);

    float d1 = (-ray_dot_v) + sqrt_x;
    float d2 = (-ray_dot_v) - sqrt_x;

    depth = (d1 < d2) ?  d1 : d2;

    if ( depth <= 0.0f)
        return false;

    return true;
}



