#include "lights.h"

#include <limits>

//  --  class Light Direction  --  //

Vec3 Light_Direction::get_direction(const Vec3& /*point*/) const
{
    return direction;
}

float Light_Direction::get_distance(const Vec3& /*point*/) const
{
    return std::numeric_limits<float>::max();
}