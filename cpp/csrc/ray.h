#ifndef RAY_H
#define RAY_H

#include "float3.h"

struct Ray {
    float3 origin;
    float3 direction;
    Ray() {}
    Ray(const float3& o, const float3& d) : origin(o), direction(d) {}
    float3 at(float distance) const { return origin + distance * direction; }
};

#endif  // RAY_H
