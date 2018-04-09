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

    dir -= position;
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

    ambient    = Color(0.1f, 0.1f, 0.13f);
    background = Color(0x8b9dc300);
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
    Color output;

    float  closest_depth = 0.0f;
    Shape* closest_shape = intersection_closest(ray, closest_depth);

    if ( closest_shape != nullptr )
    {
        Vec3  point  = (ray.dir * closest_depth) + ray.ori;
        Vec3  normal = closest_shape->get_normal(point);
        
        output = shade_point(ray, point, normal, closest_shape->material);

        output.red   = ( output.red   > 1.0f ) ? 1.0f : output.red;
        output.green = ( output.green > 1.0f ) ? 1.0f : output.green;
        output.blue  = ( output.blue  > 1.0f ) ? 1.0f : output.blue;
    }
    else
    {
        output = background;
    }

    return output;
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

bool Raytracer::shadow_test( const Light* light,
                             const Vec3&  light_direction,
                             const Vec3&  point ) const
{
    Ray   shadow_ray(light_direction, point);
    float shadow_depth;
    
    Shape* closest_shape_shadow = intersection_closest( shadow_ray,
                                                        shadow_depth );

    float light_distance = light->get_distance(point);

    return (closest_shape_shadow == nullptr ) || ( shadow_depth > light_distance);
}


Color Raytracer::shade_point( const Ray& ray,
                              const Vec3& point,
                              const Vec3& normal,
                              const Material& material ) const
{
    Color diffuse;
    Color specular;
    Color reflection;

    for ( Light* light : lights )
    {
        Vec3  light_direction = light->get_direction(point) * (-1.0f);
        float incident = normal * light_direction;

        if ( incident > 0.0f )
        {
            if( point_in_shadow(light, light_direction, point) )
            {
                diffuse  += shade_diffuse( incident,
                                           light, 
                                           material );

                specular += shade_specular( incident,
                                            normal,
                                            ray,
                                            light,
                                            light_direction,
                                            material );
            }
        }
    }

    reflection = shade_reflection( ray, normal, point, material);

    return diffuse + specular + reflection + ( ambient * (1.0f - material.reflection));
}

Color Raytracer::shade_diffuse( float incident,
                                const Light* light,
                                const Material& material ) const
{
    if ( material.reflection < 1.0f )
        return incident *
               light->color *
               material.color *
               (1.0f - material.reflection);
    
    return Color(0.0f, 0.0f, 0.0f);
}

Color Raytracer::shade_specular( float incident,
                                 const Vec3& normal,
                                 const Ray& ray,
                                 const Light* light,
                                 const Vec3& light_direction,
                                 const Material& material ) const
{
    if ( material.specular > 1.0f )
    {
        Vec3 light_reflection = light_direction - ( 2.0f * incident * normal );

        float dot_reflection = ray.dir * light_reflection;

        if ( dot_reflection > 0.0f )
            return std::pow(dot_reflection, material.specular) * light->color;
    }

    return Color(0.0f, 0.0f, 0.0f);
}

Color Raytracer::shade_reflection( const Ray& ray,
                                   const Vec3& normal,
                                   const Vec3& point,
                                   const Material& material ) const
{
    if ( material.reflection > 0.0f )
    {
        Vec3 reflection = ray.dir - (2.0f * (ray.dir * normal) * normal);

        reflection.normalize(); // ????
        
        Ray ray_reflection(reflection, point);

        return material.reflection * cast_ray(ray_reflection);
    }

    return Color(0.0f, 0.0f, 0.0f);
}