#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "camera.h"
#include "materials.h"
#include "scene.h"

std::shared_ptr<Material> create_material(const json &config) {
    string type = config["type"];
    color col = point3(config["color"].get<vector<int>>());
    float emmision = config["emmision"];

    if (type == "lambertian") {
        return std::make_shared<Lambertian>(col, emmision);
    } else if (type == "metal") {
        float fuzz = config["fuzz"];
        return std::make_shared<Metal>(col, emmision, fuzz);
    } else if (type == "glass" || type == "dielectric") {
        float refraction = config["refraction"];
        float fuzz = config["fuzz"];
        return std::make_shared<Dielectric>(col, emmision, refraction, fuzz);
    } else {
        cout << "Material type not found: " << type << endl;
        return nullptr;
    }
}

Sphere create_sphere(const json &config) {
    point3 center = config["center"].get<vector<float>>();
    float radius = config["radius"];
    auto mat = create_material(config["material"]);
    return Sphere(center, radius, mat);
}

Camera create_camera(const json &config) {
    int image_w = config["image_w"];
    int image_h = config["image_h"];
    point3 location = config["location"].get<vector<float>>();
    vec3 lookat = config["lookat"].get<vector<float>>();
    float fov = config["fov"];
    int rays_per_pixel = config["rays_per_pixel"];
    int max_depth = config["max_depth"];
    float focal_dist = config["focal_dist"];
    float defocus_angle = config["defocus_angle"];
    return Camera(image_w, image_h, location, lookat, fov, focal_dist, defocus_angle,
                  rays_per_pixel, max_depth);
}

vector<Sphere> create_scene() {
    vector<Sphere> world;
    unsigned state = 32;

    // Ground
    auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5), 0.0);
    world.push_back(Sphere(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_uniform(state);
            point3 center(a + 0.9 * random_uniform(state), 0.2,
                          b + 0.9 * random_uniform(state));

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> material;

                if (choose_mat < 0.8) {
                    // diffuse
                    color albedo = random_vec(state) * random_vec(state);
                    material = make_shared<Lambertian>(albedo, 0.0);
                } else if (choose_mat < 0.95) {
                    // metal
                    color albedo = random_vec(0.5, 1, state);
                    float fuzz = random_uniform(0, 0.5, state);
                    material = make_shared<Metal>(albedo, 0.0, fuzz);
                } else {
                    // glass
                    color albedo = {1.0f, 1.0f, 1.0f};
                    float fuzz = 0.0;
                    float refraction = 1.5;
                    material = make_shared<Dielectric>(albedo, 0.0, refraction, fuzz);
                }
                world.push_back(Sphere(center, 0.2, material));
            }
        }
    }

    auto col = color(1.0f, 1.0f, 1.0f);
    auto material1 = make_shared<Dielectric>(col, 0, 1.5, 0.0);
    world.push_back(Sphere(point3(0, 1, 0), 1.0, material1));

    col = color(0.4, 0.2, 0.1);
    auto material2 = make_shared<Lambertian>(col, 0.0);
    world.push_back(Sphere(point3(-4, 1, 0), 1.0, material2));

    col = color(0.7, 0.6, 0.5);
    auto material3 = make_shared<Metal>(col, 0.0, 0.0);
    world.push_back(Sphere(point3(4, 1, 0), 1.0, material3));
    return world;
}

#endif  // FACTORY_H
