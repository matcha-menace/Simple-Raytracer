//
// Created by Steve Hu on 1/8/25.
//

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <memory>
#include <iostream>
#include <cmath>
#include <limits>
#include <random>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358979323846;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACER_H
