#include "material.h"

//  --  class Color  --  //


// Constructors
Color::Color(uint8_t _r, uint8_t _g, uint8_t _b)
    : r{_r} , g{_g} , b{_b} {}
Color::Color(uint32_t hex)
{
    set(hex);
}
Color::Color(const Color& _color)
    : r{_color.r} , g{_color.g} , b{_color.b} {}

// Assignment operators
Color& Color::operator =  (const Color& rhs)
{
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;

    return *this;
}
Color& Color::operator += (const Color& rhs)
{
    if ( (r += rhs.r) < rhs.r )
        r = 0xFF;
    if ( (g += rhs.g) < rhs.g )
        g = 0xFF;
    if ( (b += rhs.b) < rhs.b )
        b = 0xFF;

    return *this;
}
Color& Color::operator -= (const Color& rhs)
{
    if ( (r += rhs.r) > rhs.r )
        r = 0x00;
    if ( (g += rhs.g) > rhs.g )
        g = 0x00;
    if ( (b += rhs.b) > rhs.b )
        b = 0x00;

    return *this;
}
Color& Color::operator *= (float rhs)
{
    set(r * rhs, g * rhs, b * rhs);

    return *this;
}

// Arithmetic operators
Color Color::operator + (const Color& rhs) const
{
    return Color(*this) += rhs;
}
Color Color::operator - (const Color& rhs) const
{
    return Color(*this) -= rhs;
}

Color operator * (const Color& lhs, float rhs)
{
    return Color(lhs) *= rhs;
}
Color operator * (float lhs, const Color& rhs)
{
    return Color(rhs) *= lhs;
}

// Member functions
void Color::set(uint8_t _r, uint8_t _g, uint8_t _b)
{
    r = _r;
    g = _g;
    b = _b;
}
void Color::set(uint32_t hex)
{
    uint8_t* p = (uint8_t*) &hex;

    r = p[2];
    g = p[1];
    b = p[0];
    a = p[3];
}