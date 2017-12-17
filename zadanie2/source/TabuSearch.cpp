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

void TabuSearch::tabuSearch()
{
    std::cout << "Distance before = " << bestDistance << "\n";

    int tabuSize = bestPath.size() * 3;
    int tabuTenure = bestPath.size() * 3;
    int neighborhoodSize = calculateNeighborhoodSize();
    Move bestMove;

    std::vector<int> currentPath = bestPath;
    std::vector<Move> neighborhood(neighborhoodSize);
    std::list<TabuMove> tabuList;

    int currentCost = bestDistance;
    int workingCost = bestDistance;

    while(executeTimeSeconds > 0.0)
    {
        auto startTimePoint = std::chrono::steady_clock::now();

        auto k = 0;
        for(auto i = 1; i < bestPath.size()-1; ++i)
        {
            for(auto j = i+1; j < bestPath.size()-1; ++j)
            {
                    std::vector<int> workingPath = currentPath;
                    std::swap(workingPath[i], workingPath[j]);
                    workingCost = calculatePathDistance(workingPath); 
                    neighborhood[k] = {workingCost, i, j};
                    ++k;
            }
        }

        verifyTabuList(tabuList);

        bestMove = findBestMove(neighborhood, tabuList);
        std::swap(currentPath[bestMove.cityFrom], currentPath[bestMove.cityTo]);
        currentCost = bestMove.cost;

        if (tabuList.size() < tabuSize)
        {
            tabuList.push_back(TabuMove { std::make_pair(bestMove.cityTo, bestMove.cityFrom), tabuTenure });
        }
        else
        {
            auto it = std::min_element(tabuList.begin(), tabuList.end(), [](const auto& e1, const auto& e2) 
                                                                        {
                                                                            return (e1.tenure < e2.tenure);
                                                                        });
            *it = TabuMove { std::make_pair(bestMove.cityTo, bestMove.cityFrom), tabuTenure };
        }

        if(counter == 100)
        {
            currentPath = generateRandomSolution();
            counter == 0;
            currentCost = calculatePathDistance(currentPath);
        }

        ++counter;

        auto endTimePoint = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::ratio<1,1>>(endTimePoint - startTimePoint);
        executeTimeSeconds -= duration.count();
    }
    std::cout << "Distance after = " << bestDistance << "\n";
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

    std::cout << "Path: ";
    for(auto city : path)
    {
        std::cout << city << " ";
    }
    std::cout << "\n";

    return path;
}

Move TabuSearch::findBestMove(const std::vector<Move>& neighborhood, std::list<TabuMove>& tabuList)
{
    int cost = std::numeric_limits<int>::max();
    std::pair<int, int> move;
    auto position = neighborhood.begin();
    for (auto it = neighborhood.begin(); it != neighborhood.end(); ++it)
    {
        if (bestDistance > it->cost)
        {
            bestDistance = it->cost;
            cost = it->cost;
            position = it;
            counter = 0;
            if (tabuTenure == 0)
            {
                tabuTenure = bestPath.size();
            }
            continue;
        }
        if (cost > it->cost)
        {
            move = std::make_pair(it->cityTo, it->cityFrom);
            if (std::find_if(tabuList.begin(), tabuList.end(), [&move](const TabuMove& e) { return e.move == move; }) == tabuList.end())
            {
                cost = it->cost;
                position = it;
            }
        }
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
    tabuSize = 0;
    tabuTenure = 0;
}

void TabuSearch::setDivirsificationMaxCount(int maxCount)
{
    diversificationMaxCount = maxCount;
}

void TabuSearch::setDivirsification(bool diver)
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