cmake_minimum_required(VERSION 3.16)

project(rt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build main executable
add_executable(rt
    src/camera.cpp
    src/hittable_list.cpp
    src/main.cpp
    src/ray.cpp
    src/sphere.cpp
    src/vec3.cpp
)

# Test
enable_testing()

# Tests
add_test(Runs         ./rt)
add_test(CreatesImage ./rt >> img.ppm)
