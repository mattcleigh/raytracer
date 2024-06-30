#ifndef SCENE_H
#define SCENE_H

#include "hitrecord.h"
#include "interval.h"
#include "materials.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

struct Sphere;
struct Surface;

// Abstract class for any object in the scene
struct Surface {
    shared_ptr<Material> mat;
    virtual ~Surface() = default;  // Needed for virtual classes
    Surface(shared_ptr<Material> m) : mat(move(m)) {}
    virtual void ray_hit(HitRecord &hitrecord, const Ray &ray) const = 0;
};

// Basic sphere class with position and radius
struct Sphere : Surface {
    point3 center;
    float radius;
    Sphere(const point3 &c, const float r, shared_ptr<Material> m)
        : Surface(m), center(c), radius(r) {}
    void ray_hit(HitRecord &hitrecord, const Ray &ray) const override;
};

color trace_ray(Ray ray, const vector<Sphere> &spheres, int max_depth, unsigned &state);

#endif  // SCENE_H
