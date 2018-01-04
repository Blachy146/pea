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

    std::set<Solution> bestSolutions = sortedStartPopulation;

    while(time > 0.0)
    {
        auto startTimePoint = std::chrono::steady_clock::now();

        std::set<Solution> newBestSolutions;
        auto solutionPos = bestSolutions.begin();

        for(auto i = 0; i < numberOfSurvivors; ++i)
        {
            newBestSolutions.insert(*solutionPos);
            ++solutionPos;
        }

        RandomDoubleGenerator randomZeroOneGenerator(0.0, 1.0);

        while(newBestSolutions.size() < populationSize)
        {
            auto mutationRandomRate = randomZeroOneGenerator();

            for(auto elem : newBestSolutions)
            {
                for(auto e : elem.path)
                {
                    std::cout << e << " ";
                }
                std::cout << "\n";
            }
            std::cout << "-------Before mut end-------------\n";

            if(mutationRandomRate < mutationRate)
            {
                mutateTransposition(newBestSolutions);
            }

            for(auto elem : newBestSolutions)
            {
                for(auto e : elem.path)
                {
                    std::cout << e << " ";
                }
                std::cout << "\n";
            }
            std::cout << "--------After mut end------------\n";
        }

        bestSolutions = newBestSolutions;

        auto endTimePoint = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::ratio<1,1>>(endTimePoint - startTimePoint);
        time -= duration.count();
    }
}

void GeneticTSP::mutateTransposition(std::set<Solution>& solutions)
{
    RandomIntGenerator randomSolutionGenerator(0, solutions.size()-1);
    RandomIntGenerator randomCityGenerator(1, distances.size()-1);
    auto solutionPosIncrement = randomSolutionGenerator();
    auto solutionPos = solutions.begin();
    auto city1 = randomCityGenerator();
    auto city2 = randomCityGenerator();

    for(auto i = 0; i < solutionPosIncrement; ++i)
    {
        ++solutionPos;
    }

    auto solutionToMutate = *solutionPos;

    solutions.erase(solutionPos);
    std::swap(solutionToMutate.path[city1], solutionToMutate.path[city2]);
    solutionToMutate.distance = calculatePathDistance(solutionToMutate.path);

    solutions.insert(solutionToMutate);
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

GeneticTSP::~GeneticTSP()
{
}