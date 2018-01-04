#include "RandomGenerator.hpp"


RandomIntGenerator::RandomIntGenerator(int lowerBound, int upperBound)
    : engine(std::random_device{}()), distribution(lowerBound, upperBound)
{
}

int RandomIntGenerator::operator()()
{
    return distribution(engine);
}

RandomIntGenerator::~RandomIntGenerator()
{
}



RandomDoubleGenerator::RandomDoubleGenerator(double lowerBound, double upperBound)
    : engine(std::random_device{}()), distribution(lowerBound, upperBound)
{
}

double RandomDoubleGenerator::operator()()
{
    return distribution(engine);
}

RandomDoubleGenerator::~RandomDoubleGenerator()
{
}