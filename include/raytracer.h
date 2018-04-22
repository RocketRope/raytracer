#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include <vector>

#include <string>
#include <chrono>
#include <iostream>
#include <thread>

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
        

        Camera camera;

        std::vector<Shape*> shapes;
        std::vector<Light*> lights;

        Color ambient;
        Color background;

        int   max_recursion_depth = 4;
        float min_influence       = 0.01;

    public:

        uint8_t* frame;

        // Constructors
        Raytracer(int _width = 800, int _height = 600);
        // Destructor
        ~Raytracer();

        // Public Member functions
        void add(Shape* p_shape);
        void add(Light* p_light);

        unsigned char* render() const;
        Color cast_ray(const Ray& ray,
                       int recursion_depth = 0,
                       float influence = 1.0f ) const;

    private: 

        // Private Member functions
        Shape* intersection_closest( const Ray& ray, 
                                     float& closest_depth, 
                                     Shape* ignore_shape = nullptr ) const;

        bool point_in_shadow( const Light* light,
                              const Vec3&  light_direction,
                              const Vec3&  point ) const;

        Color shade_point( const Ray& ray,
                           const Vec3& point,
                           const Vec3& normal,
                           const Material& material,
                           int recursion_depth ) const;

        Color shade_diffuse( float incident,
                             const Light* light,
                             const Material& material ) const;
        
        Color shade_specular( float incident,
                              const Vec3& normal,
                              const Ray& ray,
                              const Light* light,
                              const Vec3& light_direction,
                              const Material& material ) const;

        Color shade_reflection( const Ray& ray,
                                const Vec3& normal,
                                const Vec3& point,
                                const Material& material,
                                int recursion_depth ) const;
};


#endif // _RAYTRACER_H_ 