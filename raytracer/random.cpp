#include "random.h"

float random_uniform(unsigned& state) {
    state *= 747796405;
    state += 2891336453;
    unsigned result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
    return result / 4294967296.0;
}

float random_uniform(float a, float b, unsigned& state) {
    return a + (b - a) * random_uniform(state);
}

float random_normal(unsigned& state) {
    float theta = 2 * M_PI * random_uniform(state);
    float rho = sqrt(-2 * log(random_uniform(state)));
    return rho * cos(theta);
}

float random_normal(float mean, float stddev, unsigned& state) {
    return mean + stddev * random_normal(state);
}
