#ifndef _VMATH_H_
#define _VMATH_H_

#include <ostream>
#include <iomanip>

const float PI = 3.1415927;

// -- Helper functions -- //
bool  equal_floats(float lhs, float rhs);
float radian_to_degree(float rad);
float degree_to_radian(float deg);

class vec2
{
    //  2x1
    // [ x ]
    // [ y ]
    //   v

    public:

        float x = 0.0f;
        float y = 0.0f;

        // Constructors
        vec2(float _x = 0.0f, float _y = 0.0f);
        vec2(const vec2& _vec);

        // Assignment operators
        vec2& operator  = (const vec2& rhs);
        vec2& operator += (const vec2& rhs);
        vec2& operator -= (const vec2& rhs);
        vec2& operator *= (float rhs);

        // Arithmetic operators
        vec2 operator + (const vec2& rhs) const;
        vec2 operator - (const vec2& rhs) const;

 friend vec2 operator * (const vec2& lhs, float rhs);
 friend vec2 operator * (float lhs, const vec2& rhs);

        // Dot product
        float operator * (const vec2& rhs) const;

        // Member functions
        vec2& normalize ();
        float length    () const;

        bool  parallel  (const vec2& rhs) const;
        bool  orthogonal(const vec2& rhs) const;
        float angle_to  (const vec2& rhs) const;
        vec2  projection(const vec2& rhs) const;

};

class vec3
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
        vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
        vec3(const vec3& _vec);

        // Assignment operators
        vec3& operator  = (const vec3& rhs);
        vec3& operator += (const vec3& rhs);
        vec3& operator -= (const vec3& rhs);
        vec3& operator *= (float rhs);

        // Arithmetic operators
        vec3 operator + (const vec3& rhs) const;
        vec3 operator - (const vec3& rhs) const;

 friend vec3 operator * (const vec3& lhs, float rhs);
 friend vec3 operator * (float lhs, const vec3& rhs);

        // Dot product
        float operator * (const vec3& rhs) const;

        // Member functions
        vec3& normalize ();
        float length    () const;

        bool  parallel  (const vec3& rhs) const;
        bool  orthogonal(const vec3& rhs) const;
        float angle_to  (const vec3& rhs) const;
        vec3  projection(const vec3& rhs) const;
        vec3  cross_product(const vec3& rhs) const;

};

class mat2x2
{
    //   2x2
    // [ a b ]
    // [ c d ]
    //   u v

    public:

        float a = 1.0f, b = 0.0f;
        float c = 0.0f, d = 1.0f;

        // Constructors
        mat2x2( float _a = 1.0f, float _b = 0.0f, 
                float _c = 0.0f, float _d = 1.0f );
        mat2x2(const vec2& u, const vec2& v);
        mat2x2(const mat2x2& _mat);

        // Assignment operators
        mat2x2& operator  = (const mat2x2& rhs);
        mat2x2& operator += (const mat2x2& rhs);
        mat2x2& operator -= (const mat2x2& rhs);

        mat2x2& operator *= (const mat2x2& rhs);
        mat2x2& operator *= (float rhs);

        // Arithmetic operators
        mat2x2 operator + (const mat2x2& rhs) const;
        mat2x2 operator - (const mat2x2& rhs) const;
        mat2x2 operator * (const mat2x2& rhs) const;

        vec2 operator * (const vec2& rhs) const;

 friend mat2x2 operator * (const mat2x2& lhs, float rhs);
 friend mat2x2 operator * (float lhs, const mat2x2& rhs);

        // Member functions
        float  determinant() const;
        mat2x2 inverse()     const;
        mat2x2 transpose()   const;

};

class mat3x3
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
        mat3x3( float _a = 1.0f, float _b = 0.0f, float _c = 0.0f, 
                float _d = 0.0f, float _e = 1.0f, float _f = 0.0f,
                float _g = 0.0f, float _h = 0.0f, float _i = 1.0f );
        mat3x3(const vec3& u, const vec3& v, const vec3& w);
        mat3x3(const mat3x3& _mat);

        // Assignment operators
        mat3x3& operator  = (const mat3x3& rhs);
        mat3x3& operator += (const mat3x3& rhs);
        mat3x3& operator -= (const mat3x3& rhs);

        mat3x3& operator *= (const mat3x3& rhs);
        mat3x3& operator *= (float rhs);

        // Arithmetic operators
        mat3x3 operator + (const mat3x3& rhs) const;
        mat3x3 operator - (const mat3x3& rhs) const;
        mat3x3 operator * (const mat3x3& rhs) const;

        vec3 operator * (const vec3& rhs) const;

 friend mat3x3 operator * (const mat3x3& lhs, float rhs);
 friend mat3x3 operator * (float lhs, const mat3x3& rhs);

        // Member functions
        float  determinant() const;
        mat3x3 adjugate()    const;
        mat3x3 inverse()     const;
        mat3x3 transpose()   const;

};


//  -- STD ostream  --  //

std::ostream& operator << (std::ostream& os, const vec2& rhs);
std::ostream& operator << (std::ostream& os, const vec3& rhs);
std::ostream& operator << (std::ostream& os, const mat2x2& rhs);
std::ostream& operator << (std::ostream& os, const mat3x3& rhs);


#endif // _VMATH_H_