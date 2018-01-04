#include "GeneticTSP.hpp"

#include <iostream>


int main()
{
    GeneticTSP genetic;

    genetic.tryToLoadFromFile("/home/bmalecki/Downloads/gr17.tsp/data");
    genetic.setPupulationSize(5);
    genetic.setMutationRate(1.0);
    genetic.setSurvivalRate(0.5);
    genetic.setCalculationTime(0.00001);
    genetic.geneticAlgorithm();
}