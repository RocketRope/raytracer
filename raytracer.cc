#include "raytracer.h"

#include <cmath>
#include <limits>

//  --  class Camera  --  //

// Constructors
Camera::Camera(int _width, int _height, float _fov)
    : width{_width} , height{_height} ,
      position{0.0f, 0.0f, 0.0f}
{
    fov = degree_to_radian(_fov);
    aspect_ratio = (float) width / (float) height;

    float image_plane_width  = 2.0f * std::tan(fov / 2.0f) * aspect_ratio;
    float image_plane_height = 2.0f * std::tan(fov / 2.0f);

    offset_vec_width = Vec3( image_plane_width / width, 
                             0.0f, 
                             0.0f );

    offset_vec_height = Vec3(  0.0f, 
                              -image_plane_height / height, 
                               0.0f );

    image_plane_pixel_origin = Vec3 (-image_plane_width / 2.0f,
                                      image_plane_height / 2.0f,
                                     -1.0f );

    image_plane_pixel_origin += offset_vec_width  * 0.5f;
    image_plane_pixel_origin += offset_vec_height * 0.5f;
}

// Member functions
Ray Camera::get_primary_ray(int x, int y) const
{
    Vec3 dir = image_plane_pixel_origin + 
               (offset_vec_width  * x)  + 
               (offset_vec_height * y);

    dir.normalize();

    return Ray(dir, position);
}

//  --  class Raytracer  --  //

// Constructors
Raytracer::Raytracer(int _width, int _height)
    : width{_width} , height{_height} ,
      camera{_width , _height , 45.0f}
{
    frame = new Color[width * height];
}
// Destructor
Raytracer::~Raytracer()
{
    delete[] frame;

    for ( Shape* shape : shapes )
        delete shape;
}

// Member functions

void Raytracer::add(Shape* p_shape)
{
    if ( p_shape != nullptr )
        shapes.push_back(p_shape);
}

unsigned char* Raytracer::render() const
{
    int index = 0;

    for ( int y = 0 ; y < height ; y++ )
    {
        for ( int x = 0 ; x < width ; x++ )
        {
            Ray ray = camera.get_primary_ray(x, y);
            frame[index++] = trace_ray(ray);
        }
    }

    return (unsigned char*) frame;
}

Color Raytracer::trace_ray(const Ray& ray) const
{
    float  closest_depth = std::numeric_limits<float>::max();
    Shape* closest_shape = nullptr;

    for ( Shape* shape : shapes )
    {
        float depth = shape->intersect(ray);

        if ( ( depth > 0.0f ) && ( depth < closest_depth) )
        {
            closest_depth = depth;
            closest_shape = shape;
        }
    }

    Color output_color(Color::TRANSPARENT);

    if ( closest_shape != nullptr )
    {
        Vec3 point  = ray.dir * depth;
        Vec3 normal = closest_shape->get_normal(point);
        
        output_color = closest_shape->color;
    }

    return output_color;
}