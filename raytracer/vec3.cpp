#include "vec3.h"

// Scalar multiplication
vec3 operator*(const vec3& u, float t) {
    return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}
vec3 operator*(float t, const vec3& u) { return u * t; }

// Scalar division
vec3 operator/(const vec3& u, float t) { return u * (1 / t); }
vec3 operator/(float t, const vec3& u) { return u / t; }

// Vector multiplication
vec3 operator*(const vec3& v, const vec3& u) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Vector addition
vec3 operator+(const vec3& v, const vec3& u) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector subtraction
vec3 operator-(const vec3& v, const vec3& u) {
    return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

// Vector dot product
float dot(const vec3& v, const vec3& u) {
    return v.e[0] * u.e[0] + v.e[1] * u.e[1] + v.e[2] * u.e[2];
}

// Vector cross product
vec3 cross(const vec3& v, const vec3& u) {
    return vec3(v.e[1] * u.e[2] - v.e[2] * u.e[1], v.e[2] * u.e[0] - v.e[0] * u.e[2],
                v.e[0] * u.e[1] - v.e[1] * u.e[0]);
}

// unary operators
std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Rotation about an axis
vec3 rotate(const vec3& v, const vec3& axis, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return v * c + cross(axis, v) * s + axis * dot(axis, v) * (1 - c);
}

// Reflection
vec3 reflect(const vec3& v, const vec3& n) { return v - 2 * dot(v, n) * n; }

// Refraction
vec3 refract(const vec3& v, const vec3& n, float eta_ratio) {
    float cos_theta = fminf32(dot(-v, n), 1.0);
    vec3 r_perp = eta_ratio * (v + cos_theta * n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_perp.length_squared())) * n;
    return r_perp + r_parallel;
}

// Color functions
std::ostream& write_color(std::ostream& out, const color& c) {
    return out << c.r() << ' ' << c.g() << ' ' << c.b() << '\n';
}

// Write the pixels to a file
void write_to_file(const vector<vector<color>>& pixels, const string filename) {
    ofstream file_stream;
    file_stream.open(filename);

    // First line of any PPM file
    int image_h = pixels.size();
    int image_w = pixels[0].size();
    file_stream << "P3\n" << image_w << ' ' << image_h << "\n255\n";

    // Loop through all pixels and write the color
    for (int i = image_h; i--;) {
        for (int j = 0; j < image_w; j++) {
            write_color(file_stream, pixels[i][j]);
        }
    }
    file_stream.close();
}

// Random generation
vec3 random_vec(unsigned& state) {
    return vec3(random_uniform(state), random_uniform(state), random_uniform(state));
}

vec3 random_vec(float min, float max, unsigned& state) {
    return vec3(random_uniform(min, max, state), random_uniform(min, max, state),
                random_uniform(min, max, state));
}

vec3 random_on_unit_sphere(unsigned& state) {
    vec3 p(random_uniform(state), random_uniform(state), random_uniform(state));
    return p.normalize();
}

vec3 random_on_hemisphere(const vec3& normal, unsigned& state) {
    vec3 p = random_on_unit_sphere(state);
    return dot(p, normal) > 0 ? p : -p;
}

vec3 random_lambertian(const vec3& normal, unsigned& state) {
    vec3 p = random_on_unit_sphere(state) + normal;
    return p.near_zero() ? normal : p.normalize();
}

vec3 random_on_disk(unsigned& state) {
    float angle = 2 * M_PI * random_uniform(state);
    float radius = sqrt(random_uniform(state));
    return vec3(radius * cos(angle), radius * sin(angle), 0);
}
