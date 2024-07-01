#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "camera.h"
#include "materials.h"
#include "scene.h"

std::shared_ptr<Material> create_material(const nlohmann::json &config);
Sphere create_sphere(const nlohmann::json &config);
Camera create_camera(const nlohmann::json &config);
std::vector<Sphere> create_default_scene();

#endif  // FACTORY_H
