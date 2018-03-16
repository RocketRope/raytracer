#include "vmath.h"

#include <cmath>
#include <limits>

//  --  Helper functions  --  //

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


//  --  Class Vec2  --  //

//       2x1
//      [ x ]
//      [ y ]
//        v

// Constructors
vec2::vec2(float _x, float _y)
    : x{_x} , y{_y} {}
vec2::vec2(const vec2& _vec)
{
    this->operator=(_vec);
}

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
vec2 vec2::operator + (const vec2& rhs)      const { return vec2(*this) += rhs; }
vec2 vec2::operator - (const vec2& rhs)      const { return vec2(*this) -= rhs; }
vec2 operator * (const vec2& lhs, float rhs)       { return vec2(lhs)   *= rhs; }
vec2 operator * (float lhs, const vec2& rhs)       { return rhs * lhs; }

// Dot product
float vec2::operator * (const vec2& rhs) const
{
    return (x * rhs.x) + (y * rhs.y);
}

// Member functions
vec2& vec2::normalize()
{
    float l = length();
    x /= l;
    y /= l;

    return *this;
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


//  --  Class vec3  --  //

//       3x1
//      [ x ]
//      [ y ]
//      [ z ]
//        v

// Constructors
vec3::vec3(float _x, float _y, float _z)
    : x{_x} , y{_y} , z{_z} {}
vec3::vec3(const vec3& _vec)
{
    this->operator=(_vec);
}

// Assignment operators
vec3& vec3::operator  = (const vec3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;

    return *this;
}
vec3& vec3::operator += (const vec3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    
    return *this;
}
vec3& vec3::operator -= (const vec3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}
vec3& vec3::operator *= (float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
}

// Arithmetic operators
vec3 vec3::operator + (const vec3& rhs)      const { return vec3(*this) += rhs; }
vec3 vec3::operator - (const vec3& rhs)      const { return vec3(*this) -= rhs; }
vec3 operator * (const vec3& lhs, float rhs)       { return vec3(lhs)   *= rhs; }
vec3 operator * (float lhs, const vec3& rhs)       { return rhs * lhs; }

// Dot product
float vec3::operator * (const vec3& rhs) const
{
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}
vec3& vec3::normalize()
{
    float l = length();
    x /= l;
    y /= l;
    z /= l;

    return *this;
}
float vec3::length() const
{
    return std::sqrt( x*x + y*y + z*z);
}
bool vec3::parallel  (const vec3& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    if ( equal_floats(dot, mag) )
        return true;

    return false;
}
bool vec3::orthogonal(const vec3& rhs) const
{
    float dot = this->operator*(rhs);

    if ( equal_floats(dot, 0.0f) )
        return true;

    return false;
}
float vec3::angle_to (const vec3& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    return std::acos(dot / mag);
}
vec3 vec3::projection(const vec3& rhs) const
{
    float  dot = this->operator*(rhs);
    return rhs * ( dot / (rhs * rhs) );
}
vec3  vec3::cross_product(const vec3& rhs) const
{
    return vec3( (y * rhs.z) - (z * rhs.y),
                 (z * rhs.x) - (x * rhs.z),
                 (x * rhs.y) - (y * rhs.x) );
}


//  --  Class mat2x2  --  //

//        2x2 
//      [ a b ] 
//      [ c d ] 
//        u v

// Constructors
mat2x2::mat2x2( float _a, float _b, 
                float _c, float _d )
    : a{_a} , b{_b}, 
      c{_c} , d{_d} {}
mat2x2::mat2x2(const vec2& u, const vec2& v)
    : a{u.x} , b{v.x}, 
      c{u.y} , d{v.y} {}
mat2x2::mat2x2(const mat2x2& _mat)
{
    this->operator=(_mat);
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
mat2x2 mat2x2::operator + (const mat2x2& rhs)    const { return mat2x2(*this) += rhs; }
mat2x2 mat2x2::operator - (const mat2x2& rhs)    const { return mat2x2(*this) -= rhs; }
mat2x2 mat2x2::operator * (const mat2x2& rhs)    const { return mat2x2(*this) *= rhs; }

vec2   mat2x2::operator * (const vec2& rhs) const 
{
    return vec2( a * rhs.x + b * rhs.y,
                 c * rhs.x + d * rhs.y );
}

mat2x2 operator * (const mat2x2& lhs, float rhs)       { return mat2x2(lhs)   *= rhs; }
mat2x2 operator * (float lhs, const mat2x2& rhs)       { return rhs * lhs; }

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
mat2x2 mat2x2::transpose() const
{
    return mat2x2(d,b,c,a);
}


//  --  class mat3x3  --  //

//     3x3
//  [ a b c]
//  [ d e f]
//  [ g h i]
//    u v w

mat3x3::mat3x3( float _a, float _b, float _c, 
                float _d, float _e, float _f,
                float _g, float _h, float _i )
    : a{_a} , b{_b} , c{_c},
      d{_d} , e{_e} , f{_f},
      g{_g} , h{_h} , i{_i} {}
mat3x3::mat3x3(const vec3& u, const vec3& v, const vec3& w)
    : a{u.x} , b{v.x} , c{w.x},
      d{u.y} , e{v.y} , f{w.y},
      g{u.z} , h{v.z} , i{w.z} {}
mat3x3::mat3x3(const mat3x3& _mat)
{
    this->operator=(_mat);
}

// Assignment operators
mat3x3& mat3x3::operator  = (const mat3x3& rhs)
{
    a = rhs.a; b = rhs.b; c = rhs.c;
    d = rhs.d; e = rhs.e; f = rhs.f;
    g = rhs.g; h = rhs.h; i = rhs.i;

    return *this;
}
mat3x3& mat3x3::operator += (const mat3x3& rhs)
{
    a += rhs.a; b += rhs.b; c += rhs.c;
    d += rhs.d; e += rhs.e; f += rhs.f;
    g += rhs.g; h += rhs.h; i += rhs.i;

    return *this;
}
mat3x3& mat3x3::operator -= (const mat3x3& rhs)
{
    a -= rhs.a; b -= rhs.b; c -= rhs.c;
    d -= rhs.d; e -= rhs.e; f -= rhs.f;
    g -= rhs.g; h -= rhs.h; i -= rhs.i;

    return *this;
}

mat3x3& mat3x3::operator *= (const mat3x3& rhs)
{
    return *this = mat3x3( (a * rhs.a) + (b * rhs.d) + (c * rhs.g),
                           (a * rhs.b) + (b * rhs.e) + (c * rhs.h),
                           (a * rhs.c) + (b * rhs.f) + (c * rhs.i),
                           (d * rhs.a) + (e * rhs.d) + (f * rhs.g),
                           (d * rhs.b) + (e * rhs.e) + (f * rhs.h),
                           (d * rhs.c) + (e * rhs.f) + (f * rhs.i),
                           (g * rhs.a) + (h * rhs.d) + (i * rhs.g),
                           (g * rhs.b) + (h * rhs.e) + (i * rhs.h),
                           (g * rhs.c) + (h * rhs.f) + (i * rhs.i) );
}
mat3x3& mat3x3::operator *= (float rhs)
{
    a *= rhs; b *= rhs; c *= rhs;
    d *= rhs; e *= rhs; f *= rhs;
    g *= rhs; h *= rhs; i *= rhs;

    return *this;
}

// Arithmetic operators
mat3x3 mat3x3::operator + (const mat3x3& rhs) const { return mat3x3(*this) += rhs; }
mat3x3 mat3x3::operator - (const mat3x3& rhs) const { return mat3x3(*this) -= rhs; }
mat3x3 mat3x3::operator * (const mat3x3& rhs) const { return mat3x3(*this) *= rhs; }

vec3 mat3x3::operator * (const vec3& rhs) const
{
    return vec3( (a * rhs.x) + (b * rhs.y) + (c * rhs.z),
                 (d * rhs.x) + (e * rhs.y) + (f * rhs.z),
                 (g * rhs.x) + (h * rhs.y) + (i * rhs.z) );
}

mat3x3 operator * (const mat3x3& lhs, float rhs) { return mat3x3(lhs) *= rhs; }
mat3x3 operator * (float lhs, const mat3x3& rhs) { return mat3x3(rhs) *= lhs; }

// Member functions
float  mat3x3::determinant() const
{
    return (a*e*i) + (b*f*g) + (c*d*h) - (c*e*g) - (b*d*i) - (a*f*h); 
}
mat3x3 mat3x3::inverse()     const
{
    float det = determinant();
    return adjugate() * ( 1.0f / det );
}
mat3x3 mat3x3::adjugate()    const
{
   return mat3x3(  (e*i) - (f*h) ,
                 -((b*i) - (c*h)),
                   (b*f) - (c*e) ,
                 -((d*i) - (f*g)),
                   (a*i) - (c*g) ,
                 -((a*f) - (c*d)),
                   (d*h) - (e*g) ,
                 -((a*h) - (b*g)),
                   (a*e) - (b*d)  );
}
mat3x3 mat3x3::transpose()   const
{
    return mat3x3( a, d, g,
                   b, e, h,
                   c, f, i );
}

