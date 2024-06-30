#ifndef RAY_H
#define RAY_H

#include "utils.h"
#include "vec3.h"

struct Ray {
    point3 orig;
    vec3 dir;
    Ray() {}
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    point3 at(float distance) const { return orig + distance * dir; }
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }
};

#endif  // RAY_H
