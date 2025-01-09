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

    auto material_clear = make_shared<metal>(color(1, 1, 1), 0.0);
    auto material_red = make_shared<metal>(color(0.9, 0.1, 0.1), 1.0);
    auto material_blue = make_shared<metal>(color(0.1, 0.1, 0.9), 1.0);
    auto material_glass = make_shared<dielectric>(1.5);
    auto material_black = make_shared<metal>(color(0.9, 0.92, 0.95), 0.9);

    world.add(make_shared<sphere>(point3( 0.0, 1.0, -3.0), 2, material_clear));
    world.add(make_shared<sphere>(point3(0.0, 0.0, 4.0), 1.5, material_red));
    world.add(make_shared<sphere>(point3(1.1, -0.45, -1.0), 0.5, material_blue));
    // world.add(make_shared<sphere>(point3(0.0, -0.5, 1.0), 1.0, material_glass));
    world.add(make_shared<sphere>(point3(6.0, -6.0, -9.0), 9, material_black));

    camera cam;

    cam.aspect_ratio = 4.0 / 3.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 20;
    cam.max_depth = 50;

    cam.vfov = 60;
    cam.position = point3(0, -1, 2);
    cam.lookat = point3(0, 0, -1);
    cam.up = vec3(0, 1, 0);
    cam.background_up_color = color(0.2, 0.2, 0.6);
    // cam.background_down_color = color(0.5, 0.4, 0.7);

    cam.render(world);

    return 0;
}
