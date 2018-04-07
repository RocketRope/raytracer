#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include <vector>

#include <string>
#include <chrono>
#include <iostream>

#include <random>
#include <limits>

#include "vmath.h"
#include "shapes.h"
#include "lights.h"

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
        uint8_t* frame;

        Camera camera;

        std::vector<Shape*> shapes;
        std::vector<Light*> lights;

        Color ambient_color;
        Color background_color;

    public:

        // Constructors
        Raytracer(int _width = 800, int _height = 600);
        // Destructor
        ~Raytracer();

        // Member functions
        void add(Shape* p_shape);
        void add(Light* p_light);
        unsigned char* render() const;

        Color cast_ray(const Ray& ray) const;

        bool   intersection_exist(const Ray& ray, Shape* ignore_shape = nullptr) const;
        Shape* intersection_closest( const Ray& ray, 
                                     float& closest_depth, 
                                     Shape* ignore_shape = nullptr ) const;
};

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

            std::chrono::duration<double> delta_time = end_point - start_point;

            os << std::endl << msg << " : " << delta_time.count() << "s" << std::endl; 
        }
};


template < typename T >
class Random
{
    private:

        std::default_random_engine device;
        std::uniform_real_distribution<double> dist;

    public:

        Random( T low = std::numeric_limits<T>::min() , T high = std::numeric_limits<T>::max() )
            : dist{ (double) low , (double) high}
        {
            device.seed( std::chrono::system_clock::now().time_since_epoch().count() );
        }

        T operator () (void) 
        {
            return (T) dist(device);
        }
};


#endif // _RAYTRACER_H_ 