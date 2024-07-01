#include "camera.h"

// Update all the viewport vectors based on the current camera attributes
void Camera::update_viewport() {
    // Get the vector pointing to the center of the viewport
    vz = (lookat - location);

    // Use the lookat vector as the focal distance if not set
    if (focal_dist == 0) {
        focal_dist = vz.length();
    } else {
        vz._set_length(focal_dist);  // Inplace
    }

    // Determine the viewport dimensions
    viewport_w = focal_dist * tan(fov * DEG2RAD / 2) * 2;
    viewport_h = viewport_w * image_h / image_w;

    // Get the vectors pointing across the viewport (local x-axis and y-axis)
    vy.set(0, 1, 0);
    vx = cross(vz, vy).set_length(viewport_w);
    vy = cross(vx, vz).set_length(viewport_h);  // Make sure its orthogonal

    // Calculate the pixel-wise deltas
    delta_w = vx / image_w;  // Divide by the number of pixels
    delta_h = vy / image_h;

    // The location of the PIXEL on the botton-left corner of the viewport
    // This is used for iteratively building the viewport
    bottom_left = location + vz;             // Center of the viewport
    bottom_left -= (vx + vy) / 2;            // Bottom-left corner
    bottom_left += (delta_w + delta_h) / 2;  // Bottom-left pixel

    // For defocus blur we need the radius
    auto defocus_radius = focal_dist * tan(defocus_angle / 2 * DEG2RAD);
    defocus_w = vx.normalize() * defocus_radius;
    defocus_h = vy.normalize() * defocus_radius;
}

// Get a ray that shoots from the camera through the pixel at (i, j)
Ray Camera::ray_through_pixel(int i, int j, unsigned& state) {
    // Calculate the nominal start and end points of the ray
    float3 ray_start = location;
    float3 pixel_center = bottom_left + i * delta_h + j * delta_w;

    // Add some randomness (for anti-aliasing)
    pixel_center += delta_w * random_uniform(-0.5, 0.5, state);
    pixel_center += delta_h * random_uniform(-0.5, 0.5, state);

    // Add some defocus blur
    if (defocus_angle > 0) {
        float3 offset = random_on_disk(state);
        offset = offset.x() * defocus_w + offset.y() * defocus_h;
        ray_start += offset;
    }

    return Ray(ray_start, pixel_center - ray_start);
}

// Get a grid of pixels by pathtacing rays into the scene
std::vector<std::vector<float3>> Camera::render(const std::vector<Sphere>& scene,
                                                bool show_progress) {
    // Initialize the image with the correct dimensions
    std::vector<std::vector<float3>> pixels(image_h, std::vector<float3>(image_w));

    // Loop through all pixels in the image and write the pixel colour
    Ray pixel_ray;
    unsigned random_state;

    for (int i = 0; i < image_h; i++) {
        int perc = (int)(100 * i / (float)image_h);
        if (show_progress) std::cout << "\r..." << perc << '%' << std::flush;

        for (int j = 0; j < image_w; j++) {
            // Each pixel needs a random seed
            random_state = i * image_w + j;
            pixels[i][j].set(0);
            for (int s = 0; s < rays_per_pixel; s++) {
                Ray pixel_ray = ray_through_pixel(i, j, random_state);
                pixels[i][j] += trace_ray(pixel_ray, scene, max_depth, random_state);
            }
            pixels[i][j] /= rays_per_pixel;
        }
    }
    if (show_progress) std::cout << "\r..." << "100%     \n";

    return pixels;
}

std::vector<std::vector<float3>> Camera::render(const std::vector<Sphere>& scene) {
    return render(scene, false);
}
