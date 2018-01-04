#pragma once

#include <random>


class RandomIntGenerator
{
public:
    RandomIntGenerator(int lowerBound, int upperBound);
    int operator()();
    ~RandomIntGenerator();
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
};

class RandomDoubleGenerator
{
public:
    RandomDoubleGenerator(double lowerBound, double upperBound);
    double operator()();
    ~RandomDoubleGenerator();
private:
    std::default_random_engine engine;
    std::uniform_real_distribution<double> distribution;
};