#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

// Simple interval class
struct interval {
    float min, max;
    interval() : min(+infinity), max(-infinity) {}
    interval(float min, float max) : min(min), max(max) {}
    inline float size() const { return max - min; }
    inline bool in(float x) const { return min <= x && x <= max; }
    inline bool in_excl(float x) const { return min < x && x < max; }
    inline float clamp(float x) const { return x < min ? min : x > max ? max : x; }
};

static const interval empty = interval(+infinity, -infinity);
static const interval universe = interval(-infinity, +infinity);

#endif  // INTERVAL_H
