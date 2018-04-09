#ifndef _VMATH_H_
#define _VMATH_H_

#include <ostream>
#include <iomanip>

const float PI = 3.1415927;

// -- Helper functions -- //
bool  equal_floats(float lhs, float rhs);
float radian_to_degree(float rad);
float degree_to_radian(float deg);

class Vec2
{
    //  2x1
    // [ x ]
    // [ y ]
    //   v

    public:

        float x = 0.0f;
        float y = 0.0f;

        // Constructors
        Vec2(const Vec2& _vec);
        explicit Vec2(float _x = 0.0f, float _y = 0.0f)
                     : x{_x} , y{_y} {}
        
        // Assignment operators
        Vec2& operator  = (const Vec2& rhs);
        Vec2& operator += (const Vec2& rhs);
        Vec2& operator -= (const Vec2& rhs);
        Vec2& operator *= (float rhs);

        // Arithmetic operators
        Vec2 operator + (const Vec2& rhs) const;
        Vec2 operator - (const Vec2& rhs) const;

 friend Vec2 operator * (const Vec2& lhs, float rhs);
 friend Vec2 operator * (float lhs, const Vec2& rhs);

        Vec2 operator - () const;

        // Dot product
        float operator * (const Vec2& rhs) const;

        // Member functions
        Vec2& normalize ();
        float length    () const;

        bool  parallel  (const Vec2& rhs) const;
        bool  orthogonal(const Vec2& rhs) const;
        float angle_to  (const Vec2& rhs) const;
        Vec2  projection(const Vec2& rhs) const;

};

class Vec3
{
    //  3x1
    // [ x ]
    // [ y ]
    // [ z ]
    //   v

    public:

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;


        // Constructors
        Vec3(const Vec3& _vec);
        explicit Vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
                     : x{_x} , y{_y} , z{_z} {}
        
        // Assignment operators
        Vec3& operator  = (const Vec3& rhs);
        Vec3& operator += (const Vec3& rhs);
        Vec3& operator -= (const Vec3& rhs);
        Vec3& operator *= (float rhs);

        // Arithmetic operators
        Vec3 operator + (const Vec3& rhs) const;
        Vec3 operator - (const Vec3& rhs) const;

 friend Vec3 operator * (const Vec3& lhs, float rhs);
 friend Vec3 operator * (float lhs, const Vec3& rhs);

        Vec3 operator - () const;

        // Dot product
        float operator * (const Vec3& rhs) const;

        // Member functions
        Vec3& normalize ();
        float length    () const;

        bool  parallel  (const Vec3& rhs) const;
        bool  orthogonal(const Vec3& rhs) const;
        float angle_to  (const Vec3& rhs) const;
        Vec3  projection(const Vec3& rhs) const;
        Vec3  cross_product(const Vec3& rhs) const;

};

class Mat2x2
{
    //   2x2
    // [ a b ]
    // [ c d ]
    //   u v

    public:

        float a = 1.0f, b = 0.0f;
        float c = 0.0f, d = 1.0f;

        // Constructors
        
        Mat2x2(const Mat2x2& _mat);
        explicit Mat2x2(const Vec2& u, const Vec2& v)
                       : a{u.x} , b{v.x}, 
                         c{u.y} , d{v.y}  {}
        explicit Mat2x2( float _a = 1.0f, float _b = 0.0f, 
                         float _c = 0.0f, float _d = 1.0f )
                       : a{_a} , b{_b}, 
                         c{_c} , d{_d}  {}

        // Assignment operators
        Mat2x2& operator  = (const Mat2x2& rhs);
        Mat2x2& operator += (const Mat2x2& rhs);
        Mat2x2& operator -= (const Mat2x2& rhs);

        Mat2x2& operator *= (const Mat2x2& rhs);
        Mat2x2& operator *= (float rhs);

        // Arithmetic operators
        Mat2x2 operator + (const Mat2x2& rhs) const;
        Mat2x2 operator - (const Mat2x2& rhs) const;
        Mat2x2 operator * (const Mat2x2& rhs) const;

        Vec2 operator * (const Vec2& rhs) const;

 friend Mat2x2 operator * (const Mat2x2& lhs, float rhs);
 friend Mat2x2 operator * (float lhs, const Mat2x2& rhs);

        // Member functions
        float  determinant() const;
        Mat2x2 inverse()     const;
        Mat2x2 transpose()   const;

};

class Mat3x3
{
    //    3x3
    // [ a b c ]
    // [ d e f ]
    // [ g h i ] 
    //   u v w
    
    public:

        float a = 1.0f, b = 0.0f, c = 0.0f;
        float d = 0.0f, e = 1.0f, f = 0.0f;
        float g = 0.0f, h = 0.0f, i = 1.0f;

        // Constructors
        Mat3x3(const Mat3x3& _mat);
        explicit Mat3x3(const Vec3& u, const Vec3& v, const Vec3& w)
                       : a{u.x} , b{v.x} , c{w.x},
                         d{u.y} , e{v.y} , f{w.y},
                         g{u.z} , h{v.z} , i{w.z}  {}
        explicit Mat3x3( float _a = 1.0f, float _b = 0.0f, float _c = 0.0f, 
                         float _d = 0.0f, float _e = 1.0f, float _f = 0.0f,
                         float _g = 0.0f, float _h = 0.0f, float _i = 1.0f )
                       : a{_a} , b{_b} , c{_c},
                         d{_d} , e{_e} , f{_f},
                         g{_g} , h{_h} , i{_i}  {}

        // Assignment operators
        Mat3x3& operator  = (const Mat3x3& rhs);
        Mat3x3& operator += (const Mat3x3& rhs);
        Mat3x3& operator -= (const Mat3x3& rhs);

        Mat3x3& operator *= (const Mat3x3& rhs);
        Mat3x3& operator *= (float rhs);

        // Arithmetic operators
        Mat3x3 operator + (const Mat3x3& rhs) const;
        Mat3x3 operator - (const Mat3x3& rhs) const;
        Mat3x3 operator * (const Mat3x3& rhs) const;

        Vec3 operator * (const Vec3& rhs) const;

 friend Mat3x3 operator * (const Mat3x3& lhs, float rhs);
 friend Mat3x3 operator * (float lhs, const Mat3x3& rhs);

        // Member functions
        float  determinant() const;
        Mat3x3 adjugate()    const;
        Mat3x3 inverse()     const;
        Mat3x3 transpose()   const;

};


//  -- STD ostream  --  //

std::ostream& operator << (std::ostream& os, const Vec2& rhs);
std::ostream& operator << (std::ostream& os, const Vec3& rhs);
std::ostream& operator << (std::ostream& os, const Mat2x2& rhs);
std::ostream& operator << (std::ostream& os, const Mat3x3& rhs);


#endif // _VMATH_H_