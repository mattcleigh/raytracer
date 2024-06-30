#include "scene.h"

using namespace std;

// Return the background color based on the ray direction
color get_background(const Ray &ray) {
    vec3 unit_direction = ray.direction().normalize();
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

// Check if a ray hits a sphere and update the hit record if it does
void Sphere::ray_hit(HitRecord &hitrecord, const Ray &ray) const {
    // The vector from the ray origin to the center of the sphere
    vec3 oc = center - ray.origin();

    // Quadratic equation coefficients
    float a = ray.direction().length_squared();
    float h = dot(ray.direction(), oc);
    float c = oc.length_squared() - radius * radius;
    float d = h * h - a * c;

    // Has to have a solution
    if (d < 0) return;

    // Find the nearest root that lies in the acceptable range.
    // Update the hit information
    float root = (h - sqrt(d)) / a;
    if (0.0001 < root && root < hitrecord.distance) {
        vec3 point = ray.at(root);
        vec3 out_normal = (point - center) / radius;
        hitrecord.update(ray, root, point, out_normal, mat);
    }
}

// Trace the path of a ray of light as it bounces around the scene and return its
// color
color trace_ray(Ray ray, const vector<Sphere> &spheres, int max_depth,
                unsigned &state) {
    color ray_color(1.0f);       // Initialize the color to black (color is multiplied)
    color incoming_light(0.0f);  // Initialize the light to white (light is added)

    // Maximum number of bounces
    for (int i = 0; i < max_depth; i++) {
        HitRecord rec;  // Initialized with infinite distance

        // Loop through all of the spheres in the scene updating the hist info
        // This will make sure the HitRecod has the information of the closest hit!
        for (const auto &sphere : spheres) {
            sphere.ray_hit(rec, ray);
        }

        // If we hit a sphere then we can bounce the ray and try again
        // This also updates the ray_color and incoming_light
        if (rec.didHit) {
            rec.mat->scatter(ray, rec, ray_color, incoming_light, state);
        }

        // If we didn't hit anything then we return the background color
        else {
            incoming_light += ray_color * get_background(ray);
            break;
        }
    }
    return incoming_light;
}
