#ifndef _Shape_H_
#define _Shape_H_

#include "vmath.h"

struct Color
{
    uint8_t red   = 0x00;
    uint8_t green = 0x00;
    uint8_t blue  = 0x00;
    uint8_t alpha = 0xFF;

    Color() = default;
    Color(uint32_t hex)
    {
        uint8_t* p_hex = (uint8_t*) &hex;

        red   = p_hex[3];
        green = p_hex[2];
        blue  = p_hex[1];
        alpha = p_hex[0];
    }

    static const uint32_t RED    = 0xEC4339FF;
    static const uint32_t YELLOW = 0xEFB920FF;
    static const uint32_t ORANGE = 0xF47B16FF;
    static const uint32_t GREEN  = 0x7CB82FFF;
    static const uint32_t TEAL   = 0x00AEB3FF;
    static const uint32_t BLUE   = 0x00A0DCFF;
    static const uint32_t PURPLE = 0x8C68CBFF;
    
    static const uint32_t WHITE      = 0xFFFFFFFF;
    static const uint32_t LIGHT_GRAY = 0xD0D3D6FF;
    static const uint32_t GRAY       = 0x86898CFF;
    static const uint32_t DARK_GRAY  = 0x595C5FFF;
    static const uint32_t BLACK      = 0x000000FF;

    static const uint32_t TRANSPARENT = 0x00000000;

};

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

        Color color;

        Shape(const Color& _color = Color(Color::ORANGE));
        Shape(const Shape& _shape)
            : color{_shape.color} {}
        virtual ~Shape() {}
 
        virtual float intersect (const Ray& ray)    const = 0;
        virtual Vec3  get_normal(const Vec3& point) const = 0;
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
        float intersect (const Ray& ray)    const override;
        Vec3  get_normal(const Vec3& point) const override;
};

#endif // _Shape_H_