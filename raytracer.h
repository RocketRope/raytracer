#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include <vector>

#include "vmath.h"
#include "shapes.h"

#include <string>
#include <chrono>
#include <iostream>

class Timer
{
    private:

        std::string msg;
        std::chrono::high_resolution_clock::time_point start_point;

        std::ostream& os;

    public:

        Timer(const std::string& _msg = "Timer", std::ostream& _os = std::cout )
            : msg{_msg} , os{_os}
        {
            start_point = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            std::chrono::high_resolution_clock::time_point end_point;
            end_point = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_point - start_point);

            os << msg << " : " << delta_time.count() << "s" << std::endl; 
        }
};

class Camera
{

    private:

        int width;
        int height;

        float fov;
        float aspect_ratio;

        Vec3 image_plane_pixel_origin;
        Vec3 offset_vec_width;
        Vec3 offset_vec_height;

        Vec3 position;

    public:

        // Constructors
        Camera(int _width = 800, int _height = 600, float _fov = 45.0f);

        // Member functions
        Ray get_primary_ray(int x, int y) const;
};

class Raytracer
{

    private:

        int width;
        int height;
        Color* frame;

        Camera camera;

        std::vector<Shape*> shapes;


    public:

        // Constructors
        Raytracer(int _width = 800, int _height = 600);
        // Destructor
        ~Raytracer();

        // Member functions
        void  add(Shape* p_shape);
        unsigned char* render() const;

        Color cast_ray(const Ray& ray) const;
};

#endif // _RAYTRACER_H_ 