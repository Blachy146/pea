#include "GeneticTSP.hpp"
#include "Parser.hpp"
#include "RandomGenerator.hpp"

#include <unordered_set>
#include <stdexcept>
#include <iostream>


GeneticTSP::GeneticTSP()
    : calculationTime(0), populationSize(0), mutationRate(0.0), crossoverRate(0.0)
{
}

void GeneticTSP::geneticAlgorithm()
{
    auto startPopulation = generateRandomPopulation(populationSize);

    for(auto solution : startPopulation)
    {
        for(auto city : solution)
        {
            std::cout << city << " ";
        }

        std::cout << "\n";
    }
}

std::vector<std::vector<int>> GeneticTSP::generateRandomPopulation(int numberOfSolutions) const 
{
    RandomGenerator randomGenerator(1, distances.size()-1);
    std::vector<std::vector<int>> randomPopulation;
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
        randomPopulation.push_back(randomPath);
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

void GeneticTSP::setPupulationSize(int size)
{
    populationSize = size;
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

GeneticTSP::~GeneticTSP()
{
}