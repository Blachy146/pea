#include "RandomGenerator.hpp"


RandomGenerator::RandomGenerator(int lowerBound, int upperBound)
    : engine(std::random_device{}()), distribution(lowerBound, upperBound)
{

}

int RandomGenerator::operator()()
{
    return distribution(engine);
}

RandomGenerator::~RandomGenerator()
{
}