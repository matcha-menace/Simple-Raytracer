cmake_minimum_required(VERSION 3.30)
project(Raytracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(Raytracer main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
        raytracer.h
        interval.h
        camera.h
        material.h)
