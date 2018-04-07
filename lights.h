#ifndef _LIHGTS_H_
#define _LIHGTS_H_

#include "vmath.h"
#include "shapes.h"

class Light
{
    public:        
        Color color;
        float intensity;

        Light(const Color& _color, float _intensity)
            : color{_color} , intensity{_intensity} {}

        virtual Vec3  get_direction(const Vec3& point) const = 0;
        virtual float get_distance (const Vec3& point) const = 0;
};

class Light_Direction : public Light
{
    public:

        Vec3 direction;

        Light_Direction( const Vec3& _direction = Vec3(0.0f, 0.0f, 1.0f),
                         const Color _color     = Color(0.7f, 0.7f, 0.7f),
                         float _intensity        = 1.0f )
            : direction{_direction} , Light(_color, _intensity) { direction.normalize(); }

        Vec3  get_direction(const Vec3& point) const override;
        float get_distance (const Vec3& point) const override;
};

#endif // _LIGHTS_H_