#ifndef _Shape_H_
#define _Shape_H_

#include "vmath.h"

struct Color
{
    public:
        
        float red   = 0.0f;
        float green = 0.0f;
        float blue  = 0.0f;

        Color() = default;
        Color(const Color& _color) = default;
        Color(float r, float g, float b)
            : red{r} , green{g} , blue{b} {}
        Color(uint32_t hex)
        {
            uint8_t* p_hex = (uint8_t*) &hex;

            red   = p_hex[3] / 255.0f;
            green = p_hex[2] / 255.0f;
            blue  = p_hex[1] / 255.0f;
        }

        Color& operator =  (const Color& rhs)
        {
            red   = rhs.red;
            green = rhs.green;
            blue  = rhs.blue;
        }

        Color& operator *= (float rhs)
        {
            red   *= rhs;
            green *= rhs;
            blue  *= rhs;

            return *this;
        }

        Color& operator *= (const Color& rhs)
        {
            red   *= rhs.red;
            green *= rhs.green;
            blue  *= rhs.blue;

            return *this;
        }

        Color& operator += (const Color& rhs)
        {
            red   += rhs.red;
            green += rhs.green;
            blue  += rhs.blue;

            return *this;
        }

        Color& operator -= (const Color& rhs)
        {
            red   -= rhs.red;
            green -= rhs.green;
            blue  -= rhs.blue;

            return *this;
        }

        Color operator * (const Color& rhs) { return Color(*this) *= rhs; }
        Color operator + (const Color& rhs) { return Color(*this) += rhs; }
        Color operator - (const Color& rhs) { return Color(*this) -= rhs; }

 friend Color operator * (const Color& lhs, float rhs) { return Color(lhs) *= rhs; }
 friend Color operator * (float lhs, const Color& rhs) { return Color(rhs) *= lhs; }

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

        // Constructors
        Shape(const Shape& _shape) = default;
        Shape(const Color& _color = Color(Color::LIGHT_GRAY));
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
        float intersect (const Ray& ray)   const override;
        Vec3  get_normal(const Vec3& point) const override;
};

#endif // _Shape_H_