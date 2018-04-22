#include "shapes.h"

#include <cmath>
#include <vector>
#include <fstream>
#include <limits>

#include "vmath.h"
#include "timer.h"

//  --  class Ray  --  //

// Constructors
Ray::Ray(const Vec3& _dir, const Vec3& _ori)
    : dir{_dir} , ori{_ori} {}


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
float Plane::intersect (const Ray& ray) const
{
    float y = ray.dir * normal;

    // Plane faces away from or is parallel to ray
    if ( y >= 0.0f )
       return -1.0f;

    float x = (position - ray.ori) * normal;

    return x / y;
}
Vec3  Plane::get_normal(const Vec3& /*point*/) const
{
    return normal;
}


//  --  class Triangle  --  //

// Constructors
Triangle::Triangle( const Vec3& _vertex_a,
                    const Vec3& _vertex_b,
                    const Vec3& _vertex_c )
    : vertex_a{_vertex_a} , vertex_b{_vertex_b} , vertex_c{_vertex_c}
{
    edge_ab = vertex_b - vertex_a;
    edge_ac = vertex_c - vertex_a;

    normal = edge_ac.cross_product(edge_ab);
    normal.normalize();
}

// Override functions
float Triangle::intersect (const Ray& ray) const
{
    Vec3  h = ray.dir.cross_product(edge_ac);
    float a = edge_ab * h;

    if ( equal_floats(a, 0.0f) )
        return -1.0f;

    Vec3  s = ray.ori - vertex_a;
    float u = ( s * h ) / a;

    if ( (u < 0.0f) || (u > 1.0f) )
        return -1.0f;

    Vec3  q = s.cross_product(edge_ab);
    float v = (ray.dir * q) / a;

    if ( (v < 0.0f) || ( (u+v) > 1.0f ) )
        return -1.0f;

    return (edge_ac * q) / a;
}
Vec3  Triangle::get_normal(const Vec3& /*point*/) const
{
    return normal;
}

//  --  class Mesh  --  //

// Constructors
Mesh::Mesh(const char* filename, const Vec3& position)
{
    std::ifstream ifs{filename};

    if ( !ifs.is_open() )
        std::cout << "Unable to open \"" << filename << "\"." << std::endl;

    Timer load_time( std::string("Load time - ") + filename);

    triangles.reserve(1000);

    char  chr;
    float x,y,z;
    int   a,b,c;

    std::vector<Vec3> vertices;
    vertices.reserve(1000);

    while ( ifs )
    {
        if ( ifs.peek() == 'v' )
        {
            ifs >> chr >> x >> y >> z;
            vertices.push_back(Vec3(x,y,z) + position);
        }

        if ( ifs.peek() == 'f' )
        {
            ifs >> chr >> a >> b >> c;
            triangles.push_back( Triangle( vertices[a - 1],
                                           vertices[c - 1],
                                           vertices[b - 1]) );
        }

        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    triangles.shrink_to_fit();
}


// Override functions
float Mesh::intersect (const Ray& ray)        const
{
    float closest_depth = std::numeric_limits<float>::max();

    for( auto& triangle : triangles )
    {
        float depth = triangle.intersect(ray);

        if ( ( depth > 0.0001f ) && ( depth < closest_depth) )
        {
            closest_depth = depth;
            tri = &triangle;
        }
    }

    if ( closest_depth < std::numeric_limits<float>::max() )
        return closest_depth;

    return -1.0f;
}

Vec3  Mesh::get_normal(const Vec3& point) const
{
    return tri->get_normal(point);
}


