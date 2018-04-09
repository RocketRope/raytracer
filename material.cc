#include "material.h"

//  -- Struct Color  --  //

Color::Color(unsigned int hex)
{
    unsigned char* p_hex = (unsigned char*) &hex;

    red   = p_hex[3] / 255.0f;
    green = p_hex[2] / 255.0f;
    blue  = p_hex[1] / 255.0f;
}

// Assignment operators
Color& Color::operator =  (const Color& rhs)
{
    red   = rhs.red;
    green = rhs.green;
    blue  = rhs.blue;

    return *this;
}
Color& Color::operator *= (float rhs)
{
    red   *= rhs;
    green *= rhs;
    blue  *= rhs;

    return *this;
}
Color& Color::operator *= (const Color& rhs)
{
    red   *= rhs.red;
    green *= rhs.green;
    blue  *= rhs.blue;

    return *this;
}
Color& Color::operator += (const Color& rhs)
{
    red   += rhs.red;
    green += rhs.green;
    blue  += rhs.blue;

    return *this;
}
Color& Color::operator -= (const Color& rhs)
{
    red   -= rhs.red;
    green -= rhs.green;
    blue  -= rhs.blue;

    return *this;
}

// Arithmetic operators
Color Color::operator * (const Color& rhs) { return Color(*this) *= rhs; }
Color Color::operator + (const Color& rhs) { return Color(*this) += rhs; }
Color Color::operator - (const Color& rhs) { return Color(*this) -= rhs; }

Color operator * (const Color& lhs, float rhs) { return Color(lhs) *= rhs; }
Color operator * (float lhs, const Color& rhs) { return Color(rhs) *= lhs; }