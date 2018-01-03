#pragma once

#include "Parser.hpp"

#include <vector>


class GeneticTSP
{
public:
    GeneticTSP();

    void geneticAlgorithm();
    void tryToLoadFromFile(const std::string& filePath);
    void printDistancesMatrix() const;
    void setPupulationSize(int size);

    ~GeneticTSP();
private:
    std::vector<std::vector<int>> generateRandomPopulation(int numberOfSolutions) const;

    int calculationTime;
    int populationSize;
    double mutationRate;
    double crossoverRate;

    Parser parser;
    std::vector<std::vector<int>> distances;
};