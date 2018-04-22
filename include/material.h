#ifndef _MATERIAL_H_
#define _MATERIAL_H_

struct Color
{
    public:
        
        float red   = 0.0f;
        float green = 0.0f;
        float blue  = 0.0f;

        // Constructors
        Color(const Color& _color) = default;
        explicit Color(float r = 0.0f, float g = 0.0f, float b = 0.0f)
            : red{r} , green{g} , blue{b} {}
        explicit Color(unsigned int hex);

        // Assignment operators
        Color& operator  = (const Color& rhs);
        Color& operator *= (float rhs);
        Color& operator *= (const Color& rhs);
        Color& operator += (const Color& rhs);
        Color& operator -= (const Color& rhs);

        // Arithmetic operators
        Color operator * (const Color& rhs);
        Color operator + (const Color& rhs);
        Color operator - (const Color& rhs);

 friend Color operator * (const Color& lhs, float rhs);
 friend Color operator * (float lhs, const Color& rhs);

        static const unsigned int RED    = 0xEC4339FF;
        static const unsigned int YELLOW = 0xEFB920FF;
        static const unsigned int ORANGE = 0xF47B16FF;
        static const unsigned int GREEN  = 0x7CB82FFF;
        static const unsigned int TEAL   = 0x00AEB3FF;
        static const unsigned int BLUE   = 0x00A0DCFF;
        static const unsigned int PURPLE = 0x8C68CBFF;

        static const unsigned int WHITE      = 0xFFFFFFFF;
        static const unsigned int LIGHT_GRAY = 0xD0D3D6FF;
        static const unsigned int GRAY       = 0x86898CFF;
        static const unsigned int DARK_GRAY  = 0x595C5FFF;
        static const unsigned int BLACK      = 0x000000FF;

        static const unsigned int TRANSPARENT = 0x00000000;
};


struct Material
{
    public:

        Color color;
        float specular   = 0.0f;
        float reflection = 0.0f;

        // Constructors
        //Material() = default;
        Material( const Color& _color, 
                  float _specular   = 0.0f, 
                  float _reflection = 0.0f )
            : color{_color} , specular{_specular}, reflection{_reflection} {} 
};

#endif // MATERIAL_H_