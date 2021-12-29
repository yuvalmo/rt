/**
 * RNG.
 */
#pragma once

#include <random>

/**
 * Get a random double in the [0,1] range.
 */
inline double random_double()
{
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 generator;
    return dist(generator);
};

/**
 * Get a random double in the [min,max] range.
 */
inline double random_double(double min, double max)
{
    // Need to check that min < max.
    return min + random_double() * (max - min);
};
