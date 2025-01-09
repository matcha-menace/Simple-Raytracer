#include "raytracer.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace std;

int main() {
    // world
    hittable_list world;

    for (int i = 0; i < 12; i++) {
        color random_color = i * color::random();
        double f = random_double(0.4, 0.8);
        auto random_material = make_shared<metal>(random_color, f);
        world.add(make_shared<sphere>(
            point3(i * random_double(-1.0, 1.0), -0.3, (i + 1) *random_double(3.0, -3.0)),
            0.2, random_material));
    }

    auto material_clear = make_shared<metal>(color(1, 1, 1), 0.0);
    auto material_red = make_shared<metal>(color(0.9, 0.1, 0.1), 1.0);
    auto material_blue = make_shared<metal>(color(0.1, 0.1, 0.9), 1.0);
    auto material_glass = make_shared<dielectric>(1.5);
    auto material_white = make_shared<metal>(color(0.9, 0.92, 0.95), 0.9);

    // world.add(make_shared<sphere>(point3(0.0, 1.0, -3.0), 2, material_clear));
    world.add(make_shared<sphere>(point3(0.0, 2.0, -3.0), 2, material_clear));
    // world.add(make_shared<sphere>(point3(1.1, 0.4, -1.0), 0.3, material_blue));
    // world.add(make_shared<sphere>(point3(0.0, -0.5, 1.0), 1.0, material_glass));
    world.add(make_shared<sphere>(point3(0.0, -1000.5, -3.0), 1000, material_white));

    camera cam;

    cam.aspect_ratio = 4.0 / 3.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 20;
    cam.max_depth = 50;
    // cam.background_up_color = color(0.2, 0.2, 0.6);
    // cam.background_down_color = color(0.5, 0.4, 0.7);

    cam.vfov = 50;
    cam.position = point3(0, 0, 3);
    cam.lookat = point3(0, 2, -3);
    cam.up = vec3(0, 1, 0);

    cam.depth_of_field_angle = 0.6;
    cam.focus_distance = 10;

    cam.render(world);

    return 0;
}
