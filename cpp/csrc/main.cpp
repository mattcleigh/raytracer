#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "camera.h"
#include "factory.h"
#include "float3.h"
#include "io.h"
#include "materials.h"
#include "ray.h"
#include "scene.h"

int main(int argc, char** argv) {
    // Check if the config file is provided
    std::string conf_name = (argc == 2) ? argv[1] : "configA.json";

    // Open the JSON file
    std::ifstream file(conf_name);
    nlohmann::json config = nlohmann::json::parse(file);

    // Camera setup
    std::cout << "Setting up camera...\n";
    Camera cam = create_camera(config["camera"]);

    // Scene setup
    std::cout << "Setting up scene...\n";
    std::vector<Sphere> scene;
    if (!config.contains("scene")) {
        scene = create_default_scene();
    } else {
        for (auto& s : config["scene"]) {
            Sphere sphere = create_sphere(s);
            scene.push_back(sphere);
        }
    }

    // Render
    std::cout << "Starting render...\n";
    bool prog = config["show_progress"];
    std::vector<std::vector<float3>> pixels = cam.render(scene, prog);

    // Write to output file
    std::string filename = config["output_file"];
    write_to_file(pixels, filename);
    std::cout << "\nImage written to " << filename << '\n';

    return 0;
}
