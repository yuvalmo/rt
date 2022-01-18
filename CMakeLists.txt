cmake_minimum_required(VERSION 3.16)

project(rt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")

# Include path
include_directories(src)
include_directories(third-party)

# Find source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Build main executable
add_executable(rt
    ${SOURCES}
)

# Test
enable_testing()

# Tests
add_test(Runs         ./rt)
add_test(CreatesImage ./rt >> img.ppm)
