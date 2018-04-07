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
                                      1.0f );

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
    frame = new uint8_t[width * height * 4];

    ambient_color    = Color(0.1f, 0.1f, 0.14f);
    background_color = Color(0.0f, 0.0f, 0.0f);
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
void Raytracer::add(Light* p_light)
{
    if ( p_light != nullptr )
        lights.push_back(p_light);
}

unsigned char* Raytracer::render() const
{
    Timer render_time("Render time", std::cout);
    
    int index = 0;
    for ( int y = 0 ; y < height ; y++ )
    {
        for ( int x = 0 ; x < width ; x++ )
        {
            Ray primary_ray = camera.get_primary_ray(x, y);
            Color color = cast_ray(primary_ray);
            
            frame[index++] = color.red   * 255.0f;
            frame[index++] = color.green * 255.0f;
            frame[index++] = color.blue  * 255.0f;
            frame[index++] = 0xFF;
        }
    }

    return (unsigned char*) frame;
}

Color Raytracer::cast_ray(const Ray& ray) const
{
    float  closest_depth = 0.0f;
    Shape* closest_shape = intersection_closest(ray, closest_depth);

    Color output_color(0.0f, 0.0f, 0.0f);

    if ( closest_shape == nullptr )
    {
        output_color = background_color;
    }
    else
    {
        Vec3  point  = ray.dir * closest_depth;
        Vec3  normal = closest_shape->get_normal(point);
        Color color  = closest_shape->color;

        for ( Light* light : lights )
        {
            Vec3  light_direction = light->get_direction(point);
            float incident = normal * (-light_direction);

            if ( incident > 0.0f )
            {
                // Shadow
                 Ray   shadow_ray(-light_direction, point);
                float shadow_depth;
                
                Shape* closest_shape_shadow = intersection_closest( shadow_ray,
                                                                    shadow_depth,
                                                                    closest_shape );

                float light_distance = light->get_distance(point);
                if( ( closest_shape_shadow == nullptr ) || ( shadow_depth > light_distance ))
                {
                    // Diffuse
                    output_color += incident * light->color * closest_shape->color;

                    // Specular
                    Vec3 light_reflection = light_direction + ( 2.0f * incident * normal );
                    output_color += std::pow(ray.dir * light_reflection, 20.0f) * light->color;    
                }
            }
        }

        output_color += ambient_color;
    }

    output_color.red   = ( output_color.red   > 1.0f ) ? 1.0f : output_color.red;
    output_color.green = ( output_color.green > 1.0f ) ? 1.0f : output_color.green;
    output_color.blue  = ( output_color.blue  > 1.0f ) ? 1.0f : output_color.blue;


    return output_color;
}

bool Raytracer::intersection_exist(const Ray& ray, Shape* ignore_shape ) const
{
    for ( Shape* shape : shapes )
        if ( shape != ignore_shape )
            if ( shape->intersect(ray) > 0.0f )
                return true;
    
    return false;
}
Shape* Raytracer::intersection_closest( const Ray& ray, 
                                        float& closest_depth, 
                                        Shape* ignore_shape ) const
{
    Shape* closest_shape = nullptr;
    closest_depth = std::numeric_limits<float>::max();

    for ( Shape* shape : shapes )
    {
        if ( shape != ignore_shape )
        {
            float depth = shape->intersect(ray);

            if ( ( depth > 0.0f ) && ( depth < closest_depth) )
            {
                closest_depth = depth;
                closest_shape = shape;
            }
        }
    }

    return closest_shape;
}