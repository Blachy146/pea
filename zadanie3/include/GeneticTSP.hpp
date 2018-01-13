#pragma once

#include "Parser.hpp"
#include "Solution.hpp"

#include <vector>
#include <set>


enum class MutationType
{
    Transposition,
    Inversion
};


class GeneticTSP
{
public:
    GeneticTSP();

    int geneticAlgorithm();
    void tryToLoadFromFile(const std::string& filePath);
    void printDistancesMatrix() const;
    void setPupulationSize(int size);
    void setCalculationTime(double time);
    void setMutationRate(double rate);
    void setCrossoverRate(double rate);
    void setSurvivalRate(double rate);
    void setMutationType(const MutationType& type);

    ~GeneticTSP();
private:
    std::vector<Solution> generateRandomPopulation(int numberOfSolutions) const;
    int calculatePathDistance(const std::vector<int>& path) const;
    Solution mutateTransposition(const std::vector<Solution>& solutions) const;
    Solution mutateInversion(const std::vector<Solution>& solutions) const;
    std::pair<Solution, Solution> crossoverOX(const std::vector<Solution>& solutions) const;

    double calculationTime;
    int populationSize;
    double mutationRate;
    double crossoverRate;
    double survivalRate;
    MutationType mutationType;

    Parser parser;
    std::vector<std::vector<int>> distances;
};