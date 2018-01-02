#include "GeneticTSP.hpp"
#include "Parser.hpp"
#include "RandomGenerator.hpp"

#include <unordered_set>
#include <stdexcept>


GeneticTSP::GeneticTSP()
{
}

void GeneticTSP::geneticAlgorithm()
{

}

std::vector<std::vector<int>> GeneticTSP::generateRandomPopulation(int numberOfSolutions) const 
{
    RandomGenerator generator(1, distances.size()-1);
    std::vector<std::vector<int>> randomPopulation;
    std::unordered_set<int> cities;

    for(auto i = 0; i < numberOfSolutions; ++i)
    {

    }

    while(cities.size() < bestPath.size() - 2)
    {
        cities.insert(generator());
    }

    for(auto city : cities)
    {
        path.push_back(city);
    }

    path.push_back(path[0]);

    return path;
}

GeneticTSP::~GeneticTSP()
{
}