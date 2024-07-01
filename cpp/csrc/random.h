#ifndef RANDOM_H
#define RANDOM_H

#include <cmath>

float random_uniform(unsigned& state);

float random_uniform(float a, float b, unsigned& state);

float random_normal(unsigned& state);

float random_normal(float mean, float stddev, unsigned& state);

#endif  // RANDOM_H
