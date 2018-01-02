#pragma once

#include <random>


class RandomGenerator
{
public:
    RandomGenerator(int lowerBound, int upperBound);
    int operator()();
    ~RandomGenerator();
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
};