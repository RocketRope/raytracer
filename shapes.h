#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "vmath.h"

class ray
{
    public:

        vec3 dir = vec3(1.0f, 0.0f, 0.0f);
        vec3 ori = vec3(0.0f, 0.0f, 0.0f);

        // Constructors
        ray(const vec3& _dir = vec3(1.0f, 0.0f, 0.0f), 
            const vec3& _ori = vec3{0.0f, 0.0f, 0.0f});

};

class shape
{
    public:

        virtual ~shape() {}

        virtual bool intersect(const ray& ray, float& depth) const = 0; 
};

class sphere : public shape
{
    public:

        vec3  center = vec3(0.0f, 0.0f, 0.0f);
        float radius = 1.0f;

        // Constructors
        sphere(const vec3& _center = vec3(0.0f, 0.0f, 0.0f),
                     float _radius = 1.0f );

        // Override functions
        bool intersect(const ray& ray, float& point) const override;

};

#endif // _SHAPE_H_