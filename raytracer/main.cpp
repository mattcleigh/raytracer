#include "camera.h"
#include "factory.h"
#include "materials.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"
#include "vec3.h"

int main(int argc, char** argv) {
    // Check if the config file is provided
    string conf_name = (argc == 2) ? argv[1] : "config.json";

    // Open the JSON file
    ifstream file(conf_name);
    json config = json::parse(file);

    // Camera setup
    cout << "Setting up camera...\n";
    Camera cam = create_camera(config["camera"]);

    // Scene setup
    cout << "Setting up scene...\n";
    vector<Sphere> scene;
    if (!config.contains("scene")) {
        scene = create_scene();
    } else {
        for (auto& s : config["scene"]) {
            Sphere sphere = create_sphere(s);
            scene.push_back(sphere);
        }
    }

    // Render
    cout << "Starting render...\n";
    bool prog = config["show_progress"];
    vector<vector<color>> pixels = cam.render(scene, prog);

    // Write to output file
    string filename = config["output_file"];
    write_to_file(pixels, filename);
    cout << "\nImage written to " << filename << '\n';

    return 0;
}
