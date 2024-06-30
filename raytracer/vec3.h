#ifndef VEC3_H
#define VEC3_H

#include "interval.h"
#include "random.h"
#include "utils.h"

// Forward declaration
class vec3;

// Alternative names for vec3
using point3 = vec3;  // 3D point
using color = vec3;   // RGB color

// Function declarations
vec3 operator*(const vec3& u, float t);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(float t, const vec3& u);
vec3 operator/(const vec3& u, float t);
vec3 operator+(const vec3& v, const vec3& u);
vec3 operator-(const vec3& v, const vec3& u);
float dot(const vec3& v, const vec3& u);
vec3 cross(const vec3& v, const vec3& u);
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 rotate(const vec3& v, const vec3& axis, float angle);
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, float eta_ratio);
std::ostream& write_color(std::ostream& out, const color& c);
void write_to_file(const vector<vector<color>>& pixels, const string filename);
vec3 random_vec(unsigned& state);
vec3 random_vec(float min, float max, unsigned& state);
vec3 random_on_unit_sphere(unsigned& state);
vec3 random_on_hemisphere(const vec3& normal, unsigned& state);
vec3 random_lambertian(const vec3& normal, unsigned& state);
vec3 random_on_disk(unsigned& state);

// Convert to color space
static const interval intensity(0.000, 0.999);
inline float lin_to_gamma(float x) { return x > 0 ? sqrt(x) : 0; }
inline float gamma_to_lin(float x) { return x * x; }
inline int col8bit(float x) { return int(256 * intensity.clamp(lin_to_gamma(x))); }

class vec3 {
   public:
    // Attributes
    float e[3];

    // Constructors
    vec3() : e{0.0f, 0.0f, 0.0f} {}
    vec3(float e0) : e{e0, e0, e0} {}
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}
    vec3(float e[3]) : e{e[0], e[1], e[2]} {}
    vec3(const vector<float>& v) : e{v[0], v[1], v[2]} {}

    // Used specifically for color initialisation
    vec3(const vector<int>& v)
        : e{gamma_to_lin(v[0] / 255.0f), gamma_to_lin(v[1] / 255.0f),
            gamma_to_lin(v[2] / 255.0f)} {}

    // Getters
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    // 8-bit color getters (in gamma space)
    int r() const { return col8bit(x()); }
    int g() const { return col8bit(y()); }
    int b() const { return col8bit(z()); }

    // Operators
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    vec3& operator*=(const vec3& v) {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }
    vec3& operator-=(const vec3& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }
    vec3& operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3& operator/=(const float t) { return *this *= 1 / t; }

    // Basic Methods
    vec3& _normalize() { return *this /= length(); }
    vec3& _set_length(float l) { return *this *= l / length(); }
    vec3 set_length(float l) { return *this * l / length(); }
    vec3 normalize() const { return *this / length(); }
    bool near_zero() const {
        return (fabs(e[0]) < 1e-6) && (fabs(e[1]) < 1e-6) && (fabs(e[2]) < 1e-6);
    }
    vec3& set(float x, float y, float z) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        return *this;
    }
    vec3& set(float x) {
        e[0] = x;
        e[1] = x;
        e[2] = x;
        return *this;
    }
    float length() const { return std::sqrt(length_squared()); }
    float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
};

#endif  // VEC3_H
