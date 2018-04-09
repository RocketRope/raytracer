#ifndef _Shape_H_
#define _Shape_H_

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
        Sphere(const Sphere& _sphere) = default;
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
        Plane( const Vec3& _position = Vec3(0.0f, 0.0f, 0.0f),
               const Vec3& _normal   = Vec3(0.0f, 1.0f, 0.0f) );

        // Override functions
        float intersect (const Ray& ray) const override;
        Vec3  get_normal(const Vec3& /*point*/)    const override;
};

#endif // _Shape_H_