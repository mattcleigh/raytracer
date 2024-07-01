#include "float3.h"

float3& float3::operator+=(const float3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

float3& float3::operator*=(const float3& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

float3& float3::operator-=(const float3& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

float3& float3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

float3& float3::operator/=(const float t) { return *this *= 1 / t; }

float3 float3::set_length(float l) const { return *this * l / length(); }

float3 float3::normalize() const { return *this / length(); }

std::ostream& operator<<(std::ostream& out, const float3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

float3 operator*(const float3& u, float t) {
    return float3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

float3 operator*(float t, const float3& u) { return u * t; }

float3 operator/(const float3& u, float t) { return u * (1 / t); }

float3 operator/(float t, const float3& u) { return u / t; }

float3 operator*(const float3& v, const float3& u) {
    return float3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

float3 operator+(const float3& v, const float3& u) {
    return float3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

float3 operator-(const float3& v, const float3& u) {
    return float3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

float3 cross(const float3& v, const float3& u) {
    return float3(v.e[1] * u.e[2] - v.e[2] * u.e[1], v.e[2] * u.e[0] - v.e[0] * u.e[2],
                  v.e[0] * u.e[1] - v.e[1] * u.e[0]);
}

float dot(const float3& v, const float3& u) {
    return v.e[0] * u.e[0] + v.e[1] * u.e[1] + v.e[2] * u.e[2];
}

float3 reflect(const float3& v, const float3& n) { return v - 2 * dot(v, n) * n; }

float3 rotate(const float3& v, const float3& axis, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return v * c + cross(axis, v) * s + axis * dot(axis, v) * (1 - c);
}

float3 refract(const float3& v, const float3& n, float eta_ratio) {
    float cos_theta = fminf32(dot(-v, n), 1.0);
    float3 r_perp = eta_ratio * (v + cos_theta * n);
    float3 r_parallel = -sqrt(fabs(1.0 - r_perp.length_squared())) * n;
    return r_perp + r_parallel;
}

float3 random_vec(unsigned& state) {
    return float3(random_uniform(state), random_uniform(state), random_uniform(state));
}

float3 random_vec(float min, float max, unsigned& state) {
    return float3(random_uniform(min, max, state), random_uniform(min, max, state),
                  random_uniform(min, max, state));
}

float3 random_on_unit_sphere(unsigned& state) {
    float3 p(random_uniform(state), random_uniform(state), random_uniform(state));
    return p.normalize();
}

float3 random_on_hemisphere(const float3& normal, unsigned& state) {
    float3 p = random_on_unit_sphere(state);
    return dot(p, normal) > 0 ? p : -p;
}

float3 random_lambertian(const float3& normal, unsigned& state) {
    float3 p = random_on_unit_sphere(state) + normal;
    return p.near_zero() ? normal : p.normalize();
}

float3 random_on_disk(unsigned& state) {
    float angle = 2 * M_PI * random_uniform(state);
    float radius = sqrt(random_uniform(state));
    return float3(radius * cos(angle), radius * sin(angle), 0);
}
