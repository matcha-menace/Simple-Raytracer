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

    auto material_clear = make_shared<metal>(color(1, 1, 1), 0.3);
    auto material_red = make_shared<metal>(color(0.9, 0.1, 0.1), 0.5);
    auto material_blue = make_shared<metal>(color(0.1, 0.1, 0.9), 0.5);

    world.add(make_shared<sphere>(point3( 0.0, 0.0, -1.0), 1, material_clear));
    world.add(make_shared<sphere>(point3(-1.1, 0.0, -1.0), 0.5, material_red));
    world.add(make_shared<sphere>(point3(1.1, 0.0, -1.0), 0.5, material_blue));

    camera cam;

    cam.aspect_ratio = 4.0 / 3.0;
    cam.image_width = 640;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 50;
    cam.position = point3(-0.9, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.up = vec3(0, 1, 0);

    cam.render(world);

    return 0;
}
