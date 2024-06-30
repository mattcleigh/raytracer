#include "materials.h"

void Lambertian::scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                         unsigned &state) const {
    // Direction is cosine weighted random direction
    r.dir = random_lambertian(hitrecord.normal, state);

    // Standard updates
    r.orig = hitrecord.hitPoint;
    light += emmision * col * col;
    c *= col;
}

void Metal::scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                    unsigned &state) const {
    // Direction is reflected ray with a bit of fuzz
    vec3 reflected = reflect(r.direction(), hitrecord.normal);
    r.dir = reflected;
    if (fuzz > 0) {
        r.dir = r.dir.normalize() + fuzz * random_on_unit_sphere(state);
    }

    // Standard updates
    r.orig = hitrecord.hitPoint;
    light += emmision * col * c;
    c *= col;
}

void Dielectric::scatter(Ray &r, const HitRecord &hitrecord, color &c, color &light,
                         unsigned &state) const {
    // Calculate if we are entering or exiting the material
    float ref_ratio = hitrecord.hitFront ? 1.0 / refraction : refraction;

    // Check for total internal reflection
    vec3 normed_dir = r.dir.normalize();
    float cos_i = fmin(-dot(normed_dir, hitrecord.normal), 1.0);
    float sin_i = sqrt(fmax(1 - cos_i * cos_i, 0));
    bool tif = ref_ratio * sin_i > 1.0;
    if (tif) {
        r.dir = reflect(normed_dir, hitrecord.normal);
    }

    // Otherwise calculate the probability of reflection using Schlick's approximation
    else {
        float ref_prob = (1 - ref_ratio) / (1 + ref_ratio);
        ref_prob = ref_prob * ref_prob;
        ref_prob = ref_prob + (1 - ref_prob) * pow(1 - cos_i, 5);
        // Randomly choose between reflection and refraction
        if (random_uniform(state) < ref_prob) {
            r.dir = reflect(normed_dir, hitrecord.normal);
        } else {
            r.dir = refract(normed_dir, hitrecord.normal, ref_ratio);
        }
    }

    // Add a bit of fuzz
    if (fuzz > 0) {
        r.dir = r.dir + fuzz * random_on_unit_sphere(state);
    }

    // Standard updates
    r.orig = hitrecord.hitPoint;
    light += emmision * col * c;
    c *= col;
}
