#include "GeneticTSP.hpp"

#include <iostream>
#include <memory>


int main()
{
    auto genetic = std::make_unique<GeneticTSP>();

    genetic->tryToLoadFromFile("/home/bmalecki/Downloads/pr152.tsp/data");
    genetic->setPupulationSize(20);
    genetic->setMutationRate(0.31);
    genetic->setCrossoverRate(0.9);
    genetic->setSurvivalRate(0.2);
    genetic->setCalculationTime(60.0);
    genetic->setMutationType(MutationType::Inversion);
    genetic->geneticAlgorithm();
}