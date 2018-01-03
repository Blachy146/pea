#include "GeneticTSP.hpp"

#include <iostream>


int main()
{
    GeneticTSP genetic;

    genetic.tryToLoadFromFile("/home/bmalecki/Downloads/gr17.tsp/data");
    genetic.setPupulationSize(5);
    genetic.geneticAlgorithm();
}