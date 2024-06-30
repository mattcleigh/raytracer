#ifndef MATERIALS_H
#define MATERIALS_H

#include "ray.h"
#include "scene.h"
#include "utils.h"
#include "vec3.h"

// Base class for a material
struct Material {
    color col;                      // Color of the underlying material
    float emmision;                 // How much light is emitted
    virtual ~Material() = default;  // Needed for virtual classes
    Material() : col(0.5, 0.5, 0.5), emmision(0) {}
    Material(const color &c, float e) : col(c), emmision(e) {}
    virtual void scatter(Ray &r, const HitRecord &hitrecord, color &col, color &light,
                         unsigned &state) const = 0;
};

// Lambertian material
struct Lambertian : Material {
    Lambertian() : Material() {}
    Lambertian(const color &c, float e) : Material(c, e) {}
    void scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                 unsigned &state) const override;
};

// Metal material
struct Metal : Material {
    float fuzz;  // How much the reflection is scattered
    Metal() : Material(), fuzz(0) {}
    Metal(const color &c, float e, float f) : Material(c, e), fuzz(f) {}

    virtual void scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                         unsigned &state) const override;
};

// Dielectric material (glass)
struct Dielectric : Metal {
    float refraction;  // Refraction index
    Dielectric() : Metal(), refraction(1.5) {}
    Dielectric(const color &c, float e, float r, float f)
        : Metal(c, e, f), refraction(r) {}

    void scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                 unsigned &state) const override;
};

#endif  // MATERIALS_H
