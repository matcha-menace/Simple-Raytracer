//
// Created by Steve Hu on 1/8/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"
using namespace std;

class camera {
    public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10; // max no of rays bouncing into scene
    color background_up_color = color(0.3, 0.4, 0.6);
    color background_down_color = color(0.8, 0.8, 1.0);

    double vfov = 90;
    point3 position = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 up = vec3(0, 1, 0);

    double depth_of_field_angle = 0; // Variation angle of rays through each pixel
    double focus_distance = 10;

    void render(const hittable& world) {
        initialize();

        cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(cout, pixel_sample_scale * pixel_color);
            }
        }

        clog << "\rDone.                 \n";
    }

    private:
    int image_height;
    double pixel_sample_scale;
    point3 center;
    point3 pixel00_location;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;
    vec3 dop_disk_u;
    vec3 dop_disk_v;

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_sample_scale = 1.0 / samples_per_pixel;

        center = position;

        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_distance;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = unit_vector(position - lookat);
        u = unit_vector(cross(up, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center - (focus_distance * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_distance * tan(degrees_to_radians(depth_of_field_angle / 2));
        dop_disk_u = u * defocus_radius;
        dop_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) {
        auto offset = sample_square();
        auto pixel_sample = pixel00_location
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = (depth_of_field_angle <= 0) ? center : dop_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 dop_disk_sample() const {
        auto p = random_in_unit_disk();
        return center + (p[0] * dop_disk_u) + (p[1] * dop_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) {
        if (depth <= 0)
            return color(0,0,0);

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, depth - 1, world);
            }
            return color(0,0,0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * background_down_color + a * background_up_color;
    }
};

#endif //CAMERA_H
