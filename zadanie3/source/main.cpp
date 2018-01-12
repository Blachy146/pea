#include "GeneticTSP.hpp"

#include <iostream>
#include <memory>


int main()
{
    auto genetic = std::make_unique<GeneticTSP>();

    genetic->tryToLoadFromFile("/home/bmalecki/Downloads/gr17.tsp/data");
    genetic->setPupulationSize(100);
    genetic->setMutationRate(0.01);
    genetic->setCrossoverRate(0.8);
    genetic->setSurvivalRate(0.4);
    genetic->setCalculationTime(10.0);
    genetic->geneticAlgorithm();
}