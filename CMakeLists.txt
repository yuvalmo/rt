cmake_minimum_required(VERSION 3.16)

project(rt)

# Build main executable
add_executable(rt
    src/main.cpp
    src/vec3.cpp
)

# Test
enable_testing()

# Tests
add_test(Runs         ./rt)
add_test(CreatesImage ./rt >> img.ppm)
