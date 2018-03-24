#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <cstdint>

class Color
{
    public:

        uint8_t r = 0x00;
        uint8_t g = 0x00;
        uint8_t b = 0x00;
        uint8_t a = 0xFF;


        // Constructors
        Color() {};
        Color(uint8_t _r, uint8_t _g, uint8_t _b);
        Color(uint32_t hex);
        Color(const Color& _color);

        // Assignment operators
        Color& operator =  (const Color& rhs);
        Color& operator += (const Color& rhs);
        Color& operator -= (const Color& rhs);
        Color& operator *= (float rhs);

        // Arithmetic operators
        Color operator + (const Color& rhs) const;
        Color operator - (const Color& rhs) const;

 friend Color operator * (const Color& lhs, float rhs);
 friend Color operator * (float lhs, const Color& rhs);

        // Member functions
        void set(uint8_t _r, uint8_t _g, uint8_t _b);
        void set(uint32_t hex);

};

#endif