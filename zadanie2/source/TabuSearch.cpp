#include "TabuSearch.hpp"
#include "Move.hpp"
#include "RandomGenerator.hpp"
#include <unordered_set>

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>


TabuSearch::TabuSearch()
{
}

int TabuSearch::tabuSearch()
{
    int neighborhoodSize = calculateNeighborhoodSize();
    double time = executeTimeSeconds;
    int tabuSizeVal = tabuSize;
    int tabuTenureVal = tabuTenure;
    Move bestMove;

    std::vector<int> currentPath = bestPath;
    std::vector<Move> neighborhood(neighborhoodSize);
    std::list<TabuMove> tabuList;

    int currentCost = bestDistance;
    int tempCost = bestDistance;

    while(time > 0.0)
    {
        auto startTimePoint = std::chrono::steady_clock::now();

        auto k = 0;
        for(auto i = 1; i < bestPath.size()-1; ++i)
        {
            for(auto j = i+1; j < bestPath.size()-1; ++j)
            {
                    std::vector<int> tempPath = currentPath;
                    std::swap(tempPath[i], tempPath[j]);
                    tempCost = calculatePathDistance(tempPath); 
                    neighborhood[k] = {tempCost, i, j};
                    ++k;
            }
        }

        verifyTabuList(tabuList);

        bestMove = findBestMove(neighborhood, tabuList);
        if(bestMove.cityFrom != 0 and bestMove.cityTo != 0 and bestMove.cost != 0)
        {
            std::swap(currentPath[bestMove.cityFrom], currentPath[bestMove.cityTo]);
            currentCost = bestMove.cost;

            if (tabuList.size() < tabuSize)
            {
                tabuList.push_back(TabuMove { std::make_pair(bestMove.cityTo, bestMove.cityFrom), tabuTenure });
            }
            else
            {
                auto minElemPos = std::min_element(tabuList.begin(), tabuList.end(), [](const auto& elem1, const auto& elem2) 
                                                                            {
                                                                                return (elem1.tenure < elem2.tenure);
                                                                            });

                *minElemPos = TabuMove { std::make_pair(bestMove.cityTo, bestMove.cityFrom), tabuTenure };
            }
        }

        if(counter == diversificationMaxCount && diversification)
        {
            currentPath = generateRandomSolution();
            counter = 0;
            currentCost = calculatePathDistance(currentPath);
        }

        ++counter;

        auto endTimePoint = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::ratio<1,1>>(endTimePoint - startTimePoint);
        time -= duration.count();
    }

    if(diversification)
    {
        std::cout << "Diversification = true\n";
    }    
    else
    {
        std::cout << "Diversification = false\n";
    }
    std::cout << "Tabu size = " << tabuSize << "\n";
    std::cout << "Tabu tenure = " << tabuTenure << "\n";
    std::cout << "Reset after " <<  diversificationMaxCount << "\n";
    std::cout << "Distance = " << bestDistance << "\n";

    int dist = bestDistance;

    bestPath = calculateGreedy();
    bestDistance = calculatePathDistance(bestPath);
    tabuSize = tabuSizeVal;
    tabuTenure = tabuTenureVal;

    return dist;
}

std::vector<int> TabuSearch::generateRandomSolution() const 
{
    RandomGenerator generator(1, bestPath.size()-2);
    std::vector<int> path;
    std::unordered_set<int> cities;
    path.push_back(0);

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

Move TabuSearch::findBestMove(const std::vector<Move>& neighborhood, std::list<TabuMove>& tabuList)
{
    int cost = std::numeric_limits<int>::max();
    int prevBest = bestDistance;
    std::pair<int, int> move;
    auto position = neighborhood.begin();

    for (auto minElemPos = neighborhood.begin(); minElemPos != neighborhood.end(); ++minElemPos)
    {
        if (bestDistance > minElemPos->cost)
        {
            bestDistance = minElemPos->cost;
            cost = minElemPos->cost;
            position = minElemPos;
            counter = 0;
            continue;
        }
    }

    if(prevBest == bestDistance)
    {
        return Move{0,0,0};
    }

    return *position;
}

void TabuSearch::verifyTabuList(std::list<TabuMove>& tabuList)
{
    auto newTabuListEnd = std::remove_if(tabuList.begin(), tabuList.end(), [](auto& elem)
                                                    {
                                                        return --elem.tenure <= 0; 
                                                    });

    tabuList.erase(newTabuListEnd, tabuList.end());
}

int TabuSearch::calculateNeighborhoodSize() const
{
    int neighborhoodSize = 0;

    for(auto i = 1; i < bestPath.size()-1; ++i)
    {
        for(auto j = i+1; j < bestPath.size()-1; ++j)
        {
            ++neighborhoodSize;
        }
    }

    return neighborhoodSize;
}

void TabuSearch::setExecuteTime(double time)
{
    executeTimeSeconds = time;
}

std::vector<int> TabuSearch::calculateGreedy() const
{
    int startCity = 0;
    std::vector<int> path;
    std::list<int> availableCities;

    for(auto i = 0; i < distances.size(); ++i)
    {
        if(i != startCity)
        {
            availableCities.push_back(i);
        }
    }

    path.push_back(startCity);

    while(path.size() < distances.size())
    {
        auto lastCity = path.back();
        auto bestCity = *availableCities.begin();
        auto bestCityDistance = distances[lastCity][*availableCities.begin()];

        for(auto city : availableCities)
        {
            auto distance = distances[lastCity][city];

            if(distance < bestCityDistance)
            {
                bestCity = city;
                bestCityDistance = distance;
            }
        }

        path.push_back(bestCity);
        availableCities.remove(bestCity);
    }

    path.push_back(*path.begin());

    return path;
}

int TabuSearch::calculatePathDistance(const std::vector<int>& path) const
{
    int pathDistance = 0; 

    for(auto i = 0; i < path.size()-1; ++i)
    {
        pathDistance += distances[path[i]][path[i+1]];
    }

    return pathDistance;
}

void TabuSearch::printDistancesMatrix() const
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

void TabuSearch::tryToLoadFromFile(const std::string& filePath)
{
    distances = {};
    bestPath = {};
    bestDistance = 0;

    try
    {
        parser.tryToLoadFromFile(filePath);
    }
    catch(const std::runtime_error& e)
    {
        throw e;
    }

    distances = parser.getDistancesMatrix();
    bestPath = calculateGreedy();
    bestDistance = calculatePathDistance(bestPath);
    counter = 0;
}

void TabuSearch::setDiversificationMaxCount(int maxCount)
{
    diversificationMaxCount = maxCount;
}

void TabuSearch::setDiversification(bool diver)
{
    diversification = diver;
}

void TabuSearch::setTabuSize(int size)
{
    tabuSize = size;
}

void TabuSearch::setTabuTenure(int tenure)
{
    tabuTenure = tenure;
}

TabuSearch::~TabuSearch()
{
}