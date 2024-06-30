// All main files should include this file
// We will include all the necessary headers here

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <nlohmann/json.hpp>
#include <random>
#include <vector>

// C++ Std Usings
using namespace std;
using json = nlohmann::json;

// Constants
const float infinity = numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;
const float deg2rad = pi / 180.0f;

#endif  // RAYTRACER_H
