#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    point3 _origin;
    vec3 _direction;

    public:
    ray() {}
    ray(const vec3& origin, const vec3& direction) : _origin(origin), _direction(direction) {}

    const point3& origin() const { return _origin; }
    const vec3 direction() const { return _direction; }

    point3 at(double t) const {
        return _origin + t * _direction;
    }
};

#endif //RAY_H
