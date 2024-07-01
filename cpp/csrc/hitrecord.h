#ifndef HITRECORD_H
#define HITRECORD_H

#include <memory>

#include "interval.h"
#include "ray.h"

class Material;  // Forward declaration to prevent circular dependency

class HitRecord {
   public:
    bool didHit = false;        // If the ray hit any object
    float3 hitPoint;            // The point in 3D space where the ray hit the object
    float3 normal;              // The normal vector at the hit point
    float distance = infinity;  // The distance from the ray origin to the hit point
    bool hitFront;              // If the ray hit the front or backside of the object
    std::shared_ptr<Material> mat;  // The material properties of the object hit

    // Update the hit record with new information
    void update(const Ray &r, float d, float3 p, const float3 &outward_normal,
                std::shared_ptr<Material> m) {
        distance = d;
        hitPoint = p;
        hitFront = dot(r.direction, outward_normal) < 0;
        normal = hitFront ? outward_normal : -outward_normal;
        mat = move(m);
        didHit = true;
    }
};

#endif  // HITRECORD_H
