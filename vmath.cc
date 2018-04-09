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
    return (rad / PI ) * 180.0f;
}
float degree_to_radian(float deg)
{
    return (deg / 180.0f) * PI;
}


//  --  Class Vec2  --  //

//       2x1
//      [ x ]
//      [ y ]
//        v

// Constructors
Vec2::Vec2(const Vec2& _vec)
{
    this->operator=(_vec);
}

// Assignment operators
Vec2& Vec2::operator  = (const Vec2& rhs)
{
    x = rhs.x;
    y = rhs.y;

    return *this;
}
Vec2& Vec2::operator += (const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    
    return *this;
}
Vec2& Vec2::operator -= (const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}
Vec2& Vec2::operator *= (float rhs)
{
    x *= rhs;
    y *= rhs;

    return *this;
}

// Arithmetic operators
Vec2 Vec2::operator + (const Vec2& rhs)      const { return Vec2(*this) += rhs; }
Vec2 Vec2::operator - (const Vec2& rhs)      const { return Vec2(*this) -= rhs; }
Vec2 operator * (const Vec2& lhs, float rhs)       { return Vec2(lhs)   *= rhs; }
Vec2 operator * (float lhs, const Vec2& rhs)       { return rhs * lhs; }

Vec2 Vec2::operator - () const { return Vec2(*this) *= -1.0f;}

// Dot product
float Vec2::operator * (const Vec2& rhs) const
{
    return (x * rhs.x) + (y * rhs.y);
}

// Member functions
Vec2& Vec2::normalize()
{
    float l = length();
    x /= l;
    y /= l;

    return *this;
}
float Vec2::length() const
{
    return std::sqrt( x*x + y*y );
}
bool Vec2::parallel  (const Vec2& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    if ( equal_floats(dot, mag) )
        return true;

    return false;
}
bool Vec2::orthogonal(const Vec2& rhs) const
{
    float dot = this->operator*(rhs);

    if ( equal_floats(dot, 0.0f) )
        return true;

    return false;
}
float Vec2::angle_to (const Vec2& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    return std::acos(dot / mag);
}
Vec2 Vec2::projection(const Vec2& rhs) const
{
    float  dot = this->operator*(rhs);
    return rhs * ( dot / (rhs * rhs) );
}


//  --  Class Vec3  --  //

//       3x1
//      [ x ]
//      [ y ]
//      [ z ]
//        v

// Constructors
Vec3::Vec3(const Vec3& _vec)
{
    this->operator=(_vec);
}

// Assignment operators
Vec3& Vec3::operator  = (const Vec3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;

    return *this;
}
Vec3& Vec3::operator += (const Vec3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    
    return *this;
}
Vec3& Vec3::operator -= (const Vec3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}
Vec3& Vec3::operator *= (float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
}

// Arithmetic operators
Vec3 Vec3::operator + (const Vec3& rhs)      const { return Vec3(*this) += rhs; }
Vec3 Vec3::operator - (const Vec3& rhs)      const { return Vec3(*this) -= rhs; }
Vec3 operator * (const Vec3& lhs, float rhs)       { return Vec3(lhs)   *= rhs; }
Vec3 operator * (float lhs, const Vec3& rhs)       { return rhs * lhs; }

Vec3 Vec3::operator - () const { return Vec3(*this) *= -1.0f; }

// Dot product
float Vec3::operator * (const Vec3& rhs) const
{
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}
Vec3& Vec3::normalize()
{
    float l = length();
    x /= l;
    y /= l;
    z /= l;

    return *this;
}
float Vec3::length() const
{
    return std::sqrt( x*x + y*y + z*z);
}
bool Vec3::parallel  (const Vec3& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    if ( equal_floats(dot, mag) )
        return true;

    return false;
}
bool Vec3::orthogonal(const Vec3& rhs) const
{
    float dot = this->operator*(rhs);

    if ( equal_floats(dot, 0.0f) )
        return true;

    return false;
}
float Vec3::angle_to (const Vec3& rhs) const
{
    float dot = this->operator*(rhs);
    float mag = length() * rhs.length();

    return std::acos(dot / mag);
}
Vec3 Vec3::projection(const Vec3& rhs) const
{
    float  dot = this->operator*(rhs);
    return rhs * ( dot / (rhs * rhs) );
}
Vec3  Vec3::cross_product(const Vec3& rhs) const
{
    return Vec3( (y * rhs.z) - (z * rhs.y),
                 (z * rhs.x) - (x * rhs.z),
                 (x * rhs.y) - (y * rhs.x) );
}


//  --  Class Mat2x2  --  //

//        2x2 
//      [ a b ] 
//      [ c d ] 
//        u v

// Constructors
Mat2x2::Mat2x2(const Mat2x2& _mat)
{
    this->operator=(_mat);
}

// Assignment operators
Mat2x2& Mat2x2::operator  = (const Mat2x2& rhs)
{
    a = rhs.a; b = rhs.b;
    c = rhs.c; d = rhs.d;

    return *this;
}
Mat2x2& Mat2x2::operator += (const Mat2x2& rhs)
{
    a += rhs.a; b += rhs.b;
    c += rhs.c; d += rhs.d;

    return *this;
}
Mat2x2& Mat2x2::operator -= (const Mat2x2& rhs)
{
    a -= rhs.a; b -= rhs.b;
    c -= rhs.c; d -= rhs.d;

    return *this;
}

Mat2x2& Mat2x2::operator *= (const Mat2x2& rhs)
{
    return *this = Mat2x2( (a * rhs.a) + (b * rhs.c),
                           (a * rhs.b) + (b * rhs.d),
                           (c * rhs.a) + (d * rhs.c),
                           (c * rhs.b) + (d * rhs.d) );
}
Mat2x2& Mat2x2::operator *= (float rhs)
{
    a *= rhs; b *= rhs;
    c *= rhs; d *= rhs;

    return *this;
}

// Arithmetic operators
Mat2x2 Mat2x2::operator + (const Mat2x2& rhs)    const { return Mat2x2(*this) += rhs; }
Mat2x2 Mat2x2::operator - (const Mat2x2& rhs)    const { return Mat2x2(*this) -= rhs; }
Mat2x2 Mat2x2::operator * (const Mat2x2& rhs)    const { return Mat2x2(*this) *= rhs; }

Vec2   Mat2x2::operator * (const Vec2& rhs) const 
{
    return Vec2( a * rhs.x + b * rhs.y,
                 c * rhs.x + d * rhs.y );
}

Mat2x2 operator * (const Mat2x2& lhs, float rhs)       { return Mat2x2(lhs)   *= rhs; }
Mat2x2 operator * (float lhs, const Mat2x2& rhs)       { return rhs * lhs; }

// Member functions
float Mat2x2::determinant() const
{
    return (a*d) - (b*c); 
}
Mat2x2 Mat2x2::inverse() const
{
    float det = determinant();
    return Mat2x2(d, -b, -c, a) * ( 1 / det );
}
Mat2x2 Mat2x2::transpose() const
{
    return Mat2x2(d,b,c,a);
}


//  --  class Mat3x3  --  //

//     3x3
//  [ a b c ]
//  [ d e f ]
//  [ g h i ]
//    u v w

// Constructors
Mat3x3::Mat3x3(const Mat3x3& _mat)
{
    this->operator=(_mat);
}

// Assignment operators
Mat3x3& Mat3x3::operator  = (const Mat3x3& rhs)
{
    a = rhs.a; b = rhs.b; c = rhs.c;
    d = rhs.d; e = rhs.e; f = rhs.f;
    g = rhs.g; h = rhs.h; i = rhs.i;

    return *this;
}
Mat3x3& Mat3x3::operator += (const Mat3x3& rhs)
{
    a += rhs.a; b += rhs.b; c += rhs.c;
    d += rhs.d; e += rhs.e; f += rhs.f;
    g += rhs.g; h += rhs.h; i += rhs.i;

    return *this;
}
Mat3x3& Mat3x3::operator -= (const Mat3x3& rhs)
{
    a -= rhs.a; b -= rhs.b; c -= rhs.c;
    d -= rhs.d; e -= rhs.e; f -= rhs.f;
    g -= rhs.g; h -= rhs.h; i -= rhs.i;

    return *this;
}

Mat3x3& Mat3x3::operator *= (const Mat3x3& rhs)
{
    return *this = Mat3x3( (a * rhs.a) + (b * rhs.d) + (c * rhs.g),
                           (a * rhs.b) + (b * rhs.e) + (c * rhs.h),
                           (a * rhs.c) + (b * rhs.f) + (c * rhs.i),
                           (d * rhs.a) + (e * rhs.d) + (f * rhs.g),
                           (d * rhs.b) + (e * rhs.e) + (f * rhs.h),
                           (d * rhs.c) + (e * rhs.f) + (f * rhs.i),
                           (g * rhs.a) + (h * rhs.d) + (i * rhs.g),
                           (g * rhs.b) + (h * rhs.e) + (i * rhs.h),
                           (g * rhs.c) + (h * rhs.f) + (i * rhs.i) );
}
Mat3x3& Mat3x3::operator *= (float rhs)
{
    a *= rhs; b *= rhs; c *= rhs;
    d *= rhs; e *= rhs; f *= rhs;
    g *= rhs; h *= rhs; i *= rhs;

    return *this;
}

// Arithmetic operators
Mat3x3 Mat3x3::operator + (const Mat3x3& rhs) const { return Mat3x3(*this) += rhs; }
Mat3x3 Mat3x3::operator - (const Mat3x3& rhs) const { return Mat3x3(*this) -= rhs; }
Mat3x3 Mat3x3::operator * (const Mat3x3& rhs) const { return Mat3x3(*this) *= rhs; }

Vec3 Mat3x3::operator * (const Vec3& rhs) const
{
    return Vec3( (a * rhs.x) + (b * rhs.y) + (c * rhs.z),
                 (d * rhs.x) + (e * rhs.y) + (f * rhs.z),
                 (g * rhs.x) + (h * rhs.y) + (i * rhs.z) );
}

Mat3x3 operator * (const Mat3x3& lhs, float rhs) { return Mat3x3(lhs) *= rhs; }
Mat3x3 operator * (float lhs, const Mat3x3& rhs) { return Mat3x3(rhs) *= lhs; }

// Member functions
float  Mat3x3::determinant() const
{
    return (a*e*i) + (b*f*g) + (c*d*h) - (c*e*g) - (b*d*i) - (a*f*h); 
}
Mat3x3 Mat3x3::inverse()     const
{
    float det = determinant();
    return adjugate() * ( 1.0f / det );
}
Mat3x3 Mat3x3::adjugate()    const
{
   return Mat3x3(  (e*i) - (f*h) ,
                 -((b*i) - (c*h)),
                   (b*f) - (c*e) ,
                 -((d*i) - (f*g)),
                   (a*i) - (c*g) ,
                 -((a*f) - (c*d)),
                   (d*h) - (e*g) ,
                 -((a*h) - (b*g)),
                   (a*e) - (b*d)  );
}
Mat3x3 Mat3x3::transpose()   const
{
    return Mat3x3( a, d, g,
                   b, e, h,
                   c, f, i );
}



//  -- STD ostream  --  //

std::ostream& operator << (std::ostream& os, const Vec2& rhs) 
{
    return os << "[" << rhs.x << " " << rhs.y << "]";
}
std::ostream& operator << (std::ostream& os, const Vec3& rhs) 
{
    return os << "[" << rhs.x << " " << rhs.y << " " << rhs.z << "]";
}

std::ostream& operator << (std::ostream& os, const Mat2x2 rhs)
{
    return os << "[ " << rhs.a << " " << rhs.b << " "
              << "| " << rhs.c << " " << rhs.d << " ]";
}
std::ostream& operator << (std::ostream& os, const Mat3x3 rhs)
{
    return os << "[ " << rhs.a << " " << rhs.b << " " << rhs.c << " "
              << "| " << rhs.d << " " << rhs.e << " " << rhs.f << " "
              << "| " << rhs.g << " " << rhs.h << " " << rhs.i << " ]";
}