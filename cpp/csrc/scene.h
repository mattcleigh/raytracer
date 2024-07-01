#ifndef SCENE_H
#define SCENE_H

#include "float3.h"
#include "hitrecord.h"
#include "interval.h"
#include "materials.h"
#include "ray.h"

// Abstract class for any object in the scene
struct Surface {
    std::shared_ptr<Material> mat;
    virtual ~Surface() = default;  // Needed for virtual classes
    Surface(std::shared_ptr<Material> m) : mat(move(m)) {}
    virtual void ray_hit(HitRecord &hitrecord, const Ray &ray) const = 0;
};

// Basic sphere class with position and radius
struct Sphere : Surface {
    float3 center;
    float radius;
    Sphere(const float3 &c, const float r, std::shared_ptr<Material> m)
        : Surface(m), center(c), radius(r) {}
    void ray_hit(HitRecord &hitrecord, const Ray &ray) const override;
};

float3 trace_ray(Ray ray, const std::vector<Sphere> &spheres, int max_depth,
                 unsigned &state);

#endif  // SCENE_H
