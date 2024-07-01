#ifndef FLOAT3_H
#define FLOAT3_H

#include <cmath>
#include <iostream>
#include <vector>

#include "random.h"

const float DEG2RAD = M_PI / 180.0;

// Convert to color space
inline float lin_to_gamma(float x) { return x > 0 ? sqrt(x) : 0; }
inline float gamma_to_lin(float x) { return x * x; }
inline int col8bit(float x) {
    return int(256 * lin_to_gamma(x < 0 ? 0 : (x > 1 ? 1 : x)));
}

class float3 {
   public:
    float e[3];

    float3() : e{0.0f, 0.0f, 0.0f} {}
    float3(float e0) : e{e0, e0, e0} {}
    float3(float e0, float e1, float e2) : e{e0, e1, e2} {}
    float3(float e[3]) : e{e[0], e[1], e[2]} {}
    float3(const std::vector<float>& v) : e{v[0], v[1], v[2]} {}
    float3(const std::vector<int>& v)
        : e{gamma_to_lin(v[0] / 255.0f), gamma_to_lin(v[1] / 255.0f),
            gamma_to_lin(v[2] / 255.0f)} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    int r() const { return col8bit(x()); }
    int g() const { return col8bit(y()); }
    int b() const { return col8bit(z()); }

    float3& operator+=(const float3& v);
    float3& operator*=(const float3& v);
    float3& operator-=(const float3& v);
    float3& operator*=(const float t);
    float3& operator/=(const float t);
    float3 set_length(float l) const;
    float3 normalize() const;

    float& operator[](int i) { return e[i]; }
    float operator[](int i) const { return e[i]; }
    float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    float length() const { return std::sqrt(length_squared()); }
    bool near_zero() const {
        return (fabs(e[0]) < 1e-6) && (fabs(e[1]) < 1e-6) && (fabs(e[2]) < 1e-6);
    }

    float3 operator-() const { return float3(-e[0], -e[1], -e[2]); }
    float3& _normalize() { return *this /= length(); }
    float3& _set_length(float l) { return *this *= l / length(); }

    float3& set(float x, float y, float z) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        return *this;
    }
    float3& set(float x) {
        e[0] = x;
        e[1] = x;
        e[2] = x;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const float3& v);
float3 operator*(const float3& u, float t);
float3 operator*(float t, const float3& u);
float3 operator/(const float3& u, float t);
float3 operator/(float t, const float3& u);
float3 operator*(const float3& v, const float3& u);
float3 operator+(const float3& v, const float3& u);
float3 operator-(const float3& v, const float3& u);
float3 cross(const float3& v, const float3& u);
float dot(const float3& v, const float3& u);
float3 reflect(const float3& v, const float3& n);
float3 rotate(const float3& v, const float3& axis, float angle);
float3 refract(const float3& uv, const float3& n, float eta_ratio);
float3 random_vec(unsigned& state);
float3 random_vec(float min, float max, unsigned& state);
float3 random_on_unit_sphere(unsigned& state);
float3 random_on_hemisphere(const float3& normal, unsigned& state);
float3 random_lambertian(const float3& normal, unsigned& state);
float3 random_on_disk(unsigned& state);

#endif  // FLOAT3_H
