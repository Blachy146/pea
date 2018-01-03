#pragma once

#include "Parser.hpp"
#include "Solution.hpp"

#include <vector>


class GeneticTSP
{
public:
    GeneticTSP();

    void geneticAlgorithm();
    void tryToLoadFromFile(const std::string& filePath);
    void printDistancesMatrix() const;
    void setPupulationSize(int size);
    void setCalculationTime(double time);
    void setMutationRate(double rate);
    void setCrossoverRate(double rate);
    void setSurvivalRate(double rate);

    ~GeneticTSP();
private:
    std::vector<Solution> generateRandomPopulation(int numberOfSolutions) const;
    int calculatePathDistance(const std::vector<int>& path) const;

    double calculationTime;
    int populationSize;
    double mutationRate;
    double crossoverRate;
    double survivalRate;

    Parser parser;
    std::vector<std::vector<int>> distances;
};