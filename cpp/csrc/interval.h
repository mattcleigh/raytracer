#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const float infinity = std::numeric_limits<float>::infinity();

// Simple interval class
class interval {
   public:
    float min, max;
    interval() : min(+infinity), max(-infinity) {}
    interval(float min, float max) : min(min), max(max) {}
    float size() const { return max - min; }
    bool in(float x) const { return min <= x && x <= max; }
    bool in_excl(float x) const { return min < x && x < max; }
    float clamp(float x) const { return x < min ? min : (x > max ? max : x); }
};

#endif  // INTERVAL_H
