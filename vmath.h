#ifndef _VMATH_H_
#define _VMATH_H_

#include <ostream>

const float PI = 3.1415927;

// -- Helper functions -- //
bool  equal_floats(float lhs, float rhs);
float radian_to_degree(float rad);
float degree_to_radian(float deg);

class vec2
{
    public:

        float x = 0.0f;
        float y = 0.0f;

        // Constructors
        vec2(float _x = 0.0f, float _y = 0.0f);
        vec2(const vec2& _vec);

        // Type conversion
        //operator vec3 const ()

        // Assignment operators
        vec2& operator  = (const vec2& rhs);
        vec2& operator += (const vec2& rhs);
        vec2& operator -= (const vec2& rhs);
        vec2& operator *= (float rhs);

        // Arithmetic operators
        vec2 operator + (const vec2& rhs) const;
        vec2 operator - (const vec2& rhs) const;
        vec2 operator * (float rhs)       const;
 friend vec2 operator * (float lhs, const vec2& rhs);

        // Dot product
        float operator * (const vec2& rhs) const;

        // Member functions
        void  normalize ();
        float length    () const;

        bool  parallel  (const vec2& rhs) const;
        bool  orthogonal(const vec2& rhs) const;
        float angle_to  (const vec2& rhs) const;
        vec2  projection(const vec2& rhs) const;

        // Std outstream
 friend std::ostream& operator << (std::ostream& os, vec2 rhs)
        {
            return os << "[" << rhs.x << " " << rhs.y << "]";
        } 
};

class mat2x2
{
    public:

        float a = 1.0f; //
        float b = 0.0f; // [ a  b ] 
        float c = 0.0f; // [ c  d ] 
        float d = 1.0f; //   v  u

        // Constructors
        mat2x2( float _a = 1.0f, 
                float _b = 0.0f, 
                float _c = 0.0f, 
                float _d = 1.0f );
        mat2x2(const vec2& v, const vec2& u);
        mat2x2(const mat2x2& _matrix);

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

        mat2x2 operator * (float rhs) const;
        

        // Access operators

        // Member functions
        float  determinant() const;
        mat2x2 inverse() const;

 friend std::ostream& operator << (std::ostream& os, const mat2x2 rhs)
        {
            return os << "[ " << rhs.a << " " << rhs.b << " "
                      << "| " << rhs.c << " " << rhs.d << " ]";
        }
};



#endif