#pragma once

#include "Parser.hpp"

#include <vector>


class GeneticTSP
{
public:
    GeneticTSP();

    void geneticAlgorithm();
    void tryToLoadFromFile(const std::string& filePath);

    ~GeneticTSP();
private:
    int calculationTime;
    int populationSize;
    double mutationRate;
    double crossoverRate;
    Parser parser;
    std::vector<std::vector<int>> distances;
};