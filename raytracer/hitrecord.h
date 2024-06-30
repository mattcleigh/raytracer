#ifndef HITRECORD_H
#define HITRECORD_H

#include "ray.h"
#include "vec3.h"

class Material;

struct HitRecord {
    bool didHit = false;        // If the ray hit any object
    point3 hitPoint;            // The point in 3D space where the ray hit the object
    vec3 normal;                // The normal vector at the hit point
    float distance = infinity;  // The distance from the ray origin to the hit point
    bool hitFront;              // If the ray hit the front or backside of the object
    shared_ptr<Material> mat;   // The material properties of the object hit

    // Update the hit record with new information
    void update(const Ray &r, float d, vec3 p, const vec3 &outward_normal,
                shared_ptr<Material> m) {
        distance = d;
        hitPoint = p;
        hitFront = dot(r.direction(), outward_normal) < 0;
        normal = hitFront ? outward_normal : -outward_normal;
        mat = move(m);
        didHit = true;
    }
};

#endif  // HITRECORD_H
