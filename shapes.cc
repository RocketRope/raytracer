#include "shapes.h"

#include <cmath>

#include "vmath.h"

//  --  class Ray  --  //

// Constructors
Ray::Ray(const Vec3& _dir, const Vec3& _ori)
    : dir{_dir} , ori{_ori} {}


//  --  class Shape  --  //

// Constructors
Shape::Shape(const Color& _color)
    : color{_color} {}

//  --  class Sphere  --  //

// Constructors
Sphere::Sphere(const Vec3& _center, float _radius)
    : center{_center} , radius{_radius} {}

// Override functions
float Sphere::intersect(const Ray& ray) const
{
    Vec3  v = ray.ori - center;
    float ray_dot_v = ray.dir * v;
    
    float x = (ray_dot_v * ray_dot_v) - (v * v) + (radius * radius);

    // Ray never intersect sphere
    if ( x < 0.0f )
        return -1.0f;

    float sqrt_x = std::sqrt(x);

    float d1 = (-ray_dot_v) + sqrt_x;
    float d2 = (-ray_dot_v) - sqrt_x;

    float depth = (d1 < d2) ?  d1 : d2;

    return depth;
}

Vec3 Sphere::get_normal(const Vec3& point) const
{
    Vec3 normal = point - center;
    normal.normalize();

    return normal;
}

//  --  class Plane  --  //

Plane::Plane( const Vec3& _position, const Vec3& _normal )
    : position{_position} 
{
    normal = _normal;
    normal.normalize();
}

#include <iostream>

// Override functions
float Plane::intersect (const Ray& ray)   const 
{
    float y = ray.dir * normal;

    // Plane and ray parallel
    if ( y >= 0.0f )
       return -1.0f;

    float x = (position - ray.ori) * normal;

    return x / y;
}
Vec3  Plane::get_normal(const Vec3& point) const
{
    return normal;
}



