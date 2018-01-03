#include "GeneticTSP.hpp"
#include "Parser.hpp"
#include "RandomGenerator.hpp"
#include "Solution.hpp"

#include <unordered_set>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <set>


GeneticTSP::GeneticTSP()
    : calculationTime(0), populationSize(0), mutationRate(0.0), crossoverRate(0.0)
{
}

void GeneticTSP::geneticAlgorithm()
{
    auto startPopulation = generateRandomPopulation(populationSize);
    auto numberOfSurvivors = static_cast<int>(populationSize * survivalRate);
    double time = calculationTime;

    std::set<Solution> sortedStartPopulation;

    for(auto solution : startPopulation)
    {
        sortedStartPopulation.insert(solution);
    }

    while(time > 0.0)
    {
        auto startTimePoint = std::chrono::steady_clock::now();



        auto endTimePoint = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::ratio<1,1>>(endTimePoint - startTimePoint);
        time -= duration.count();
    }
}

std::vector<Solution> GeneticTSP::generateRandomPopulation(int numberOfSolutions) const 
{
    RandomGenerator randomGenerator(1, distances.size()-1);
    std::vector<Solution> randomPopulation;
    int startCity = 0;

    for(auto i = 0; i < numberOfSolutions; ++i)
    {
        std::unordered_set<int> cities;
        std::vector<int> randomPath;

        while(cities.size() < distances.size() - 1)
        {
            cities.insert(randomGenerator());            
        }

        randomPath.push_back(startCity);

        for(auto city : cities)
        {
            randomPath.push_back(city);
        }

        randomPath.push_back(startCity);

        Solution solution {calculatePathDistance(randomPath), randomPath};
        randomPopulation.push_back(solution);
    }

    return randomPopulation;
}

void GeneticTSP::printDistancesMatrix() const
{
    for(auto row : distances)
    {
        for(auto distance : row)
        {
            std::cout << distance << " ";
        }

        std::cout << "\n";
    }
}

void GeneticTSP::tryToLoadFromFile(const std::string& filePath)
{
    try
    {
        parser.tryToLoadFromFile(filePath);
    }
    catch(const std::runtime_error& e)
    {
        throw e;
    }

    distances = parser.getDistancesMatrix();
}

int GeneticTSP::calculatePathDistance(const std::vector<int>& path) const 
{
    int pathDistance = 0; 

    for(auto i = 0; i < path.size()-1; ++i)
    {
        pathDistance += distances[path[i]][path[i+1]];
    }

    return pathDistance;
}

void GeneticTSP::setCalculationTime(double time)
{
    calculationTime = time;
}

void GeneticTSP::setPupulationSize(int size)
{
    populationSize = size;
}

void GeneticTSP::setMutationRate(double rate)
{
    mutationRate = rate;
}

void GeneticTSP::setCrossoverRate(double rate)
{
    crossoverRate = rate;
}

void GeneticTSP::setSurvivalRate(double rate)
{
    survivalRate = rate;
}

GeneticTSP::~GeneticTSP()
{
}