//
// Created by Steve Hu on 1/8/25.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "raytracer.h"

class sphere : public hittable {
    point3 center;
    double radius;
    shared_ptr<material> mat_;

    public:
    sphere(const point3& center, double radius, shared_ptr<material> mat)
        : center(center), radius(std::fmax(0, radius)), mat_(mat) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = h * h - a * c;

        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat_;

        return true;
    }
};

#endif //SPHERE_H
