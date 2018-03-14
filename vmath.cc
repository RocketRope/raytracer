#include "vmath.h"

#include <cmath>
#include <limits>

// -- Helper functions -- //

bool equal_floats(float lhs, float rhs)
{
    float diff = std::abs(lhs - rhs);

    if ( diff <= std::numeric_limits<float>::epsilon() )
        return true;

    return false;
}
float radian_to_degree(float rad)
{
    return (rad / PI ) * 360;
}
float degree_to_radian(float deg)
{
    return (deg / 360) * PI;
}

// -- Class Vec2 -- //

    // Constructors
    vec2::vec2(float _x, float _y)
        : x{_x} , y{_y} {}
    vec2::vec2(const vec2& _vec)
        : x{_vec.x} , y{_vec.y} {}

    // Assignment operators
    vec2& vec2::operator  = (const vec2& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    vec2& vec2::operator += (const vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    vec2& vec2::operator -= (const vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    vec2& vec2::operator *= (float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    // Arithmetic operators
    vec2 vec2::operator + (const vec2& rhs) const
    {
        return vec2(x + rhs.x , y + rhs.y);
    }
    vec2 vec2::operator - (const vec2& rhs) const
    {
        return vec2(x - rhs.x , y - rhs.y);
    }
    vec2 vec2::operator * (float rhs)       const
    {
        return vec2(x * rhs , y * rhs);
    }
    vec2 operator * (float lhs, const vec2& rhs)
    {
            return rhs * lhs;
    }
    

    // Dot product
    float vec2::operator * (const vec2& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y);
    }

    // Member functions
    void  vec2::normalize()
    {
        float l = length();
        x /= l;
        y /= l;
    }
    float vec2::length() const
    {
        return std::sqrt( x*x + y*y );
    }

    bool vec2::parallel  (const vec2& rhs) const
    {
        float dot = this->operator*(rhs);
        float mag = length() * rhs.length();

        if ( equal_floats(dot, mag) )
            return true;

        return false;
    }
    bool vec2::orthogonal(const vec2& rhs) const
    {
        float dot = this->operator*(rhs);

        if ( equal_floats(dot, 0.0f) )
            return true;

        return false;
    }
    float vec2::angle_to (const vec2& rhs) const
    {
        float dot = this->operator*(rhs);
        float mag = length() * rhs.length();

        return std::acos(dot / mag);
    }
    vec2 vec2::projection(const vec2& rhs) const
    {
        float  dot = this->operator*(rhs);
        return rhs * ( dot / (rhs * rhs) );
    }

// -- Class mat2x2 -- //

    // Constructors
    mat2x2::mat2x2( float _a, 
                    float _b, 
                    float _c, 
                    float _d )
        : a{_a}, b{_b}, c{_c}, d{_d} {}
    mat2x2::mat2x2(const vec2& v, const vec2& u)
        :a{v.x}, b{u.x}, c{v.y}, d{u.y} {}
    mat2x2::mat2x2(const mat2x2& _mat)
    {
        *this = _mat;
    }

    // Assignment operators
    mat2x2& mat2x2::operator  = (const mat2x2& rhs)
    {
        a = rhs.a; b = rhs.b;
        c = rhs.c; d = rhs.d;

        return *this;
    }
    mat2x2& mat2x2::operator += (const mat2x2& rhs)
    {
        a += rhs.a; b += rhs.b;
        c += rhs.c; d += rhs.d;

        return *this;
    }
    mat2x2& mat2x2::operator -= (const mat2x2& rhs)
    {
        a -= rhs.a; b -= rhs.b;
        c -= rhs.c; d -= rhs.d;

        return *this;
    }

    mat2x2& mat2x2::operator *= (const mat2x2& rhs)
    {
        return *this = mat2x2( (a * rhs.a) + (b * rhs.c),
                               (a * rhs.b) + (b * rhs.d),
                               (c * rhs.a) + (d * rhs.c),
                               (c * rhs.b) + (d * rhs.d) );
    }
    mat2x2& mat2x2::operator *= (float rhs)
    {
        a *= rhs; b *= rhs;
        c *= rhs; d *= rhs;

        return *this;
    }

    // Arithmetic operators
    mat2x2 mat2x2::operator + (const mat2x2& rhs) const
    {
        return mat2x2(*this) += rhs;
    }
    mat2x2 mat2x2::operator - (const mat2x2& rhs) const
    {
        return mat2x2(*this) -= rhs;
    }
    mat2x2 mat2x2::operator * (const mat2x2& rhs) const
    {
        return mat2x2(*this) *= rhs;
    }
    mat2x2 mat2x2::operator * (float rhs) const
    {
        return mat2x2(*this) *= rhs;
    }

    // Access operators

    // Member functions
    float mat2x2::determinant() const
    {
        return (a*d) - (b*c); 
    }
    mat2x2 mat2x2::inverse() const
    {
        float det = determinant();
        return mat2x2(d, -b, -c, a) * ( 1 / det );
    }