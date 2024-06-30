#ifndef CAMERA_H
#define CAMERA_H

#include "scene.h"
#include "utils.h"
#include "vec3.h"

class Camera {
   public:
    // Attributes
    int image_w = 256;            // Width of the image in number of pixels
    int image_h = 256;            // Height of the image in number of pixels
    point3 location = {0, 0, 0};  // Location of the camera center point
    vec3 lookat = {0, 0, -1};     // Point the camera is looking at (in focus)
    float fov = 90;               // Field of view in degrees
    float focal_dist = 1;         // Distance to the focal plane
    float defocus_angle = 0;      // Angle of defocus blur
    int rays_per_pixel = 1;       // Number of rays shot out at each pixel
    int max_depth = 1;            // Maximum number of bounces

    // Constructors
    Camera(int image_w, int image_h, point3 location, point3 lookat, float fov,
           float focal_dist, float defocus_angle, int rays_per_pixel, int max_depth)
        : image_w(image_w),
          image_h(image_h),
          location(location),
          lookat(lookat),
          fov(fov),
          focal_dist(focal_dist),
          defocus_angle(defocus_angle),
          rays_per_pixel(rays_per_pixel),
          max_depth(max_depth) {
        update_viewport();
    }

    // Methods
    void update_viewport();
    Ray ray_through_pixel(int i, int j, unsigned& state);
    vector<vector<color>> render(const vector<Sphere>& scene, bool show_progress);
    vector<vector<color>> render(const vector<Sphere>& scene);

   private:
    float viewport_w;    // Width of the viewport
    float viewport_h;    // Height of the viewport
    vec3 vx;             // Vector across the viewport
    vec3 vy;             // Vector up the viewport
    vec3 vz;             // Vector pointing to the center of the viewport
    vec3 delta_w;        // Vertical size between pixel centers
    vec3 delta_h;        // Horizontal size between pixel centers
    point3 bottom_left;  // Location of the bottom left of the viewport
    vec3 defocus_w;      // Defocus blur vector horizontal
    vec3 defocus_h;      // Defocus blur vector vertical
};

#endif
