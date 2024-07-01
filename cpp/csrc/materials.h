#ifndef MATERIALS_H
#define MATERIALS_H

#include "float3.h"
#include "hitrecord.h"
#include "ray.h"

// Base class for a material
struct Material {
    float3 col;                     // Color of the underlying material
    float emmision;                 // How much light is emitted
    virtual ~Material() = default;  // Needed for virtual classes
    Material() : col(0.5, 0.5, 0.5), emmision(0) {}
    Material(const float3 &c, float e) : col(c), emmision(e) {}
    virtual void scatter(Ray &r, const HitRecord &hitrecord, float3 &col, float3 &light,
                         unsigned &state) const = 0;
};

// Lambertian material
struct Lambertian : Material {
    Lambertian() : Material() {}
    Lambertian(const float3 &c, float e) : Material(c, e) {}
    void scatter(Ray &r, const HitRecord &hitrecord, float3 &c, float3 &light,
                 unsigned &state) const override;
};

// Metal material
struct Metal : Material {
    float fuzz;  // How much the reflection is scattered
    Metal() : Material(), fuzz(0) {}
    Metal(const float3 &c, float e, float f) : Material(c, e), fuzz(f) {}

    virtual void scatter(Ray &r, const HitRecord &hitrecord, float3 &c, float3 &light,
                         unsigned &state) const override;
};

// Dielectric material (glass)
struct Dielectric : Metal {
    float refraction;  // Refraction index
    Dielectric() : Metal(), refraction(1.5) {}
    Dielectric(const float3 &c, float e, float r, float f)
        : Metal(c, e, f), refraction(r) {}

    void scatter(Ray &r, const HitRecord &hitrecord, float3 &c, float3 &light,
                 unsigned &state) const override;
};

#endif  // MATERIALS_H
