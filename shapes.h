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

        Color color = Color(0x9E9E9E);

        virtual Shape(Color _color = Color(0x9E9E9E));
        virtual ~Shape() {}

        virtual bool intersect(const Ray& ray, float& depth) const = 0; 
};

class Sphere : public Shape
{
    public:

        Vec3  center = Vec3(0.0f, 0.0f, 0.0f);
        float radius = 1.0f;

        // Constructors
        Sphere(const Vec3& _center = Vec3(0.0f, 0.0f, 0.0f),
                     float _radius = 1.0f );

        // Override functions
        bool intersect(const Ray& ray, float& point) const override;

};

#endif // _Shape_H_