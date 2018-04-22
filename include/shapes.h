#ifndef _Shape_H_
#define _Shape_H_

#include <vector>

#include "vmath.h"
#include "material.h"

class Ray
{
    public:

        Vec3 dir = Vec3(1.0f, 0.0f, 0.0f);
        Vec3 ori = Vec3(0.0f, 0.0f, 0.0f);

        // Constructors
        Ray(const Vec3& _dir = Vec3(1.0f, 0.0f, 0.0f), 
            const Vec3& _ori = Vec3{0.0f, 0.0f, 0.0f});
};

struct Vertex
{
    Vec3 position;
    Vec3 normal;

    Vertex(const Vec3& _position, const Vec3& _normal)
        : position{_position}, normal{_normal} {}
};

class Shape
{
    public:

        Material material;

        // Constructors
        Shape(const Shape& _shape) = default;
        Shape(const Material& _material = Material(Color(Color::LIGHT_GRAY)))
            : material{_material} {}
        // Destructor
        virtual ~Shape() {}
 
        // Pure Virutal functions
        virtual float intersect (const Ray& ray)    const = 0;
        virtual Vec3  get_normal(const Vec3& point) const = 0;
};

class Sphere : public Shape
{
    public:

        Vec3  center = Vec3(0.0f, 0.0f, 0.0f);
        float radius = 1.0f;

        // Constructors
        Sphere(const Sphere& _sphere ) = default;
        Sphere(const Vec3& _center = Vec3(0.0f, 0.0f, 0.0f),
                     float _radius = 1.0f );

        // Override functions
        float intersect (const Ray& ray)    const override;
        Vec3  get_normal(const Vec3& point) const override;
};

class Plane : public Shape
{
    public:

        Vec3 position = Vec3(0.0f, 0.0f ,0.0f); 
        Vec3 normal   = Vec3(0.0f ,1.0f, 0.0f);

        // Constructors
        Plane(const Plane& _plane) = default;
        Plane(const Vec3& _position = Vec3(0.0f, 0.0f, 0.0f),
              const Vec3& _normal   = Vec3(0.0f, 1.0f, 0.0f) );

        // Override functions
        float intersect (const Ray& ray)        const override;
        Vec3  get_normal(const Vec3& /*point*/) const override;
};

class Triangle : public Shape
{
    public:

        Vec3 vertex_a;
        Vec3 vertex_b;
        Vec3 vertex_c;

        Vec3 edge_ab;
        Vec3 edge_ac;

        Vec3 normal;

    public:

        // Constructors
        Triangle(const Triangle& _triangle) = default;
        Triangle(const Vec3& _point_a = Vec3(0.0f, 0.0f, 0.0f),
                 const Vec3& _point_b = Vec3(0.0f, 0.0f, 0.0f),
                 const Vec3& _point_c = Vec3(0.0f, 0.0f, 0.0f) );

        // Override functions
        float intersect (const Ray& ray)        const override;
        Vec3  get_normal(const Vec3& /*point*/) const override;
};

class Mesh : public Shape
{
    private:

        mutable Triangle* tri;
        mutable std::vector<Triangle> triangles;

    public:

        // Constructors
        Mesh(const Mesh& _mesh) = default;
        Mesh(const char* filename, const Vec3& position = Vec3(0.0f, 0.0f, 0.0f));

        // Override functions
        float intersect (const Ray& ray)        const override;
        Vec3  get_normal(const Vec3& /*point*/) const override;
};

#endif // _Shape_H_