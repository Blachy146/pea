#include "GeneticTSP.hpp"
#include "Parser.hpp"
#include "RandomGenerator.hpp"
#include "Solution.hpp"

#include <unordered_set>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <set>
#include <algorithm>


GeneticTSP::GeneticTSP()
    : calculationTime(0), populationSize(0), mutationRate(0.0), 
      crossoverRate(0.0), mutationType(MutationType::Transposition)
{
}

void GeneticTSP::geneticAlgorithm()
{
    auto startPopulation = generateRandomPopulation(populationSize);
    auto numberOfSurvivors = static_cast<int>(populationSize * survivalRate);
    double time = calculationTime;

    std::sort(startPopulation.begin(), startPopulation.end());

    std::vector<Solution> population = startPopulation; 

    while(time > 0.0)
    {
        auto startTimePoint = std::chrono::steady_clock::now();

        std::vector<Solution> survivors;
        auto solutionPos = population.begin();

        for(auto i = 0; i < numberOfSurvivors; ++i)
        {
            survivors.push_back(population[i]);
        }

        auto newPopulation = survivors;
        RandomDoubleGenerator randomZeroOneGenerator(0.0, 1.0);

        while(newPopulation.size() < populationSize)
        {
            auto mutationRandomRate = randomZeroOneGenerator();

            if(mutationRandomRate < mutationRate)
            {
                switch(mutationType)
                {
                case MutationType::Inversion:
                    newPopulation.push_back(mutateInversion(survivors));
                    break;
                case MutationType::Transposition:
                    newPopulation.push_back(mutateTransposition(survivors));
                    break;
                default:
                    break;
                }
            }

            auto crossoverRandomRate = randomZeroOneGenerator();

            if(crossoverRandomRate < crossoverRate)
            {
                auto children = crossoverOX(survivors);

                newPopulation.push_back(children.first);
                newPopulation.push_back(children.second);
            }
        }

        std::sort(newPopulation.begin(), newPopulation.end());
        population = newPopulation;

        auto endTimePoint = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::ratio<1,1>>(endTimePoint - startTimePoint);
        time -= duration.count();
    }

    std::cout << "Best solution: " << population.begin()->distance << "\n";
}

std::pair<Solution, Solution> GeneticTSP::crossoverOX(const std::vector<Solution>& solutions) const
{
    RandomIntGenerator randomSolutionGenerator(0, solutions.size()-1);
    RandomIntGenerator randomCityGenerator(1, solutions[0].path.size()-2);
    auto solutionPosIncrement1 = randomSolutionGenerator();
    auto solutionPosIncrement2 = randomSolutionGenerator();
    auto city1 = randomCityGenerator();
    auto city2 = randomCityGenerator();

    while(solutionPosIncrement1 == solutionPosIncrement2)
    {
        solutionPosIncrement1 = randomSolutionGenerator();
        solutionPosIncrement2 = randomSolutionGenerator();
    }

    while(city1 == city2)
    {
        city1 = randomCityGenerator();
        city2 = randomCityGenerator();
    }

    if(city1 > city2)
    {
        std::swap(city1, city2);
    }

    auto parent1 = solutions[solutionPosIncrement1];
    auto parent2 = solutions[solutionPosIncrement2];
    auto child1 = parent2;

    std::vector<int> usedCities;
    std::vector<int> availableCities;

    for(auto i = city1; i <= city2; ++i)
    {
        usedCities.push_back(child1.path[i]);
    }

    for(auto i = 1, j = city1 + 1; i < child1.path.size() - 1; ++i, ++j)
    {
        if(j == child1.path.size() - 1)
        {
            j = 1;
        }

        if(std::find(usedCities.begin(), usedCities.end(), parent1.path[j]) == usedCities.end())
        {
            availableCities.push_back(parent1.path[j]);
        }
    }

    for(auto i = 1, j = 0; i < child1.path.size() - 1; ++i, ++j)
    {
        if(i == city1) 
        {
            i = city2 + 1;

            if(i >= child1.path.size() - 1)
            {
                continue;
            }
        }

        child1.path[i] = availableCities[j];
    }

    child1.distance = calculatePathDistance(child1.path);

    parent1 = solutions[solutionPosIncrement2];
    parent2 = solutions[solutionPosIncrement1];
    auto child2 = parent2;

    usedCities = {};
    availableCities = {};

    for(auto i = city1; i <= city2; ++i)
    {
        usedCities.push_back(child2.path[i]);
    }

    for(auto i = 1, j = city1 + 1; i < child2.path.size() - 1; ++i, ++j)
    {
        if(j == child2.path.size() - 1)
        {
            j = 1;
        }

        if(std::find(usedCities.begin(), usedCities.end(), parent1.path[j]) == usedCities.end())
        {
            availableCities.push_back(parent1.path[j]);
        }
    }

    for(auto i = 1, j = 0; i < child2.path.size() - 1; ++i, ++j)
    {
        if(i == city1) 
        {
            i = city2 + 1;

            if(i >= child1.path.size() - 1)
            {
                continue;
            }
        }

        child2.path[i] = availableCities[j];
    }

    child2.distance = calculatePathDistance(child2.path);

    return std::make_pair(child1, child2);
}

Solution GeneticTSP::mutateTransposition(const std::vector<Solution>& solutions) const
{
    RandomIntGenerator randomSolutionGenerator(0, solutions.size()-1);
    RandomIntGenerator randomCityGenerator(1, distances.size()-1);
    auto solutionPosIncrement = randomSolutionGenerator();
    auto city1 = randomCityGenerator();
    auto city2 = randomCityGenerator();

    auto solutionToMutate = solutions[solutionPosIncrement]; 

    std::swap(solutionToMutate.path[city1], solutionToMutate.path[city2]);
    solutionToMutate.distance = calculatePathDistance(solutionToMutate.path);
    
    return std::move(solutionToMutate);
}

Solution GeneticTSP::mutateInversion(const std::vector<Solution>& solutions) const
{
    RandomIntGenerator randomSolutionGenerator(0, solutions.size()-1);
    RandomIntGenerator randomCityGenerator(1, distances.size()-1);
    auto solutionPosIncrement = randomSolutionGenerator();
    auto city1 = randomCityGenerator();
    auto city2 = randomCityGenerator();

    if(city1 > city2)
    {
        std::swap(city1, city2);
    }

    auto solutionToMutate = solutions[solutionPosIncrement];

    if(city1 != city2)
    {
        std::reverse(solutionToMutate.path.begin() + city1, solutionToMutate.path.begin() + city2);
        solutionToMutate.distance = calculatePathDistance(solutionToMutate.path);
    }

    return std::move(solutionToMutate);
}

std::vector<Solution> GeneticTSP::generateRandomPopulation(int numberOfSolutions) const 
{
    RandomIntGenerator randomGenerator(1, distances.size()-1);
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

void GeneticTSP::setMutationType(const MutationType& type)
{
    mutationType = type;
}

GeneticTSP::~GeneticTSP()
{
}