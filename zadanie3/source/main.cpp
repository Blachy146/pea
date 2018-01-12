#include "GeneticTSP.hpp"

#include <iostream>


int main()
{
    GeneticTSP genetic;

    genetic.tryToLoadFromFile("/home/bmalecki/Downloads/gr17.tsp/data");
    genetic.setPupulationSize(100);
    genetic.setMutationRate(0.1);
    genetic.setCrossoverRate(0.8);
    genetic.setSurvivalRate(0.4);
    genetic.setCalculationTime(2.0);
    genetic.geneticAlgorithm();
}