#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "vmath.h"
#include "shapes.h"

int main(int arg, char* argv[])
{

    std::ofstream ofs{"img.raw", std::ios::binary};

    sphere s = sphere(vec3(2.0f, 2.0f, 10.0f), 2.0f);
    

    int width  = std::stoi(argv[1]); 
    int height = std::stoi(argv[2]);

    float aspect_ratio = (float) width / (float) height;
    float fov = degree_to_radian(45.0f);
     
    for (int pixel_y = 0 ; pixel_y < height ; pixel_y++)
    {
        for (int pixel_x = 0 ; pixel_x < width ; pixel_x++)
        {
            float ss_x = (2.0f * ( ( ((float) pixel_x + 0.5f) / width  ))) - 1.0f;
            
            float ss_y = 1.0f - ( 2.0f * ( ( ((float) pixel_y + 0.5f) / height )));

            ss_x *= aspect_ratio * std::tan(fov / 2.0f);
            ss_y *= std::tan(fov / 2.0f);

            vec3 dir = vec3(ss_x, ss_y, 1.0f);
            dir.normalize();

            ray r(dir, vec3(0.0f, 0.0f, 0.0f));

            float depth = 0.0f;

            if ( s.intersect(r, depth) )
                ofs << (unsigned char) (depth * 2.0f);
            else
                ofs << (unsigned char) 0;
        }
    }


    ofs.close();

    return 0;
} 