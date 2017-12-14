#include "Instance.hpp"

#include <functional>
#include <algorithm>
#include <iostream>

Instance::Instance(std::vector<std::vector<int> > matrix) : costMatrix(std::move(matrix))
{
    using clock = std::chrono::high_resolution_clock;

    greedyAlgorithm();
    std::cout << "Before: " << getCost() << std::endl;
    
    auto begin = clock::now();
    tabuSearch();
    auto end = clock::now();
    time = end - begin;
    std::cout << "After: " << getCost() << std::endl;

    printTime();
}

int Instance::getCost()
{
    return bestCost;
}

void Instance::printTime()
{
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(time).count() << "s" << std::endl;
}

void Instance::printForTest()
{
    std::cout << bestCost << " ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << std::endl;
}

std::tuple<int, int> Instance::findMin(const int row, std::vector<int>& visited)
{
    int min = std::numeric_limits<int>::max();
    int position = 0;
    for (int i = 0; i < costMatrix.size(); ++i)
    {
        if (!visited[i])
        {
            if (costMatrix[row][i] < min)
            {
                min = costMatrix[row][i];
                position = i;
            }
        }
    }
    return { min, position };
}

void Instance::greedyAlgorithm()
{
    bestTour.push_back(0);
    std::tuple<int, int> move;
    std::vector<int> visited(costMatrix.size(), 0);
    visited[0] = 1;
    while (bestTour.size() != costMatrix.size())
    {
        move = findMin(bestTour.back(), visited);
        bestCost += std::get<0>(move);
        bestTour.push_back(std::get<1>(move));
        visited[std::get<1>(move)] = 1;
    }
    bestCost += costMatrix[bestTour.back()][0];
}

int Instance::calculateDistance(std::vector<int>& tour, int city1, int city2, int cost) const
{
    if (city1 - 1 != city2)
    {
        cost -= costMatrix[tour[city1 - 1]][tour[city1]];
        cost += costMatrix[tour[city1 - 1]][tour[city2]];
    }
    if (city1 + 1 == tour.size())
    {
        cost -= costMatrix[tour.back()][0];
        cost += costMatrix[tour[city2]][0];
        return cost;
    }
    if (city1 + 1 == city2)
    {
        cost -= costMatrix[tour[city1]][tour[city2]];
        cost += costMatrix[tour[city2]][tour[city1]];
        return cost;
    }
    cost -= costMatrix[tour[city1]][tour[city1 + 1]];
    cost += costMatrix[tour[city2]][tour[city1 + 1]];
    return cost;
}

Move Instance::findBest(const std::vector<Move>& neighborhood, std::list<TabuMove>& tabuList)
{
    int cost = std::numeric_limits<int>::max();
    std::tuple<int, int> move;
    auto position = neighborhood.begin();
    for (auto it = neighborhood.begin(); it != neighborhood.end(); ++it)
    {
        if (bestCost > it->cost)
        {
            bestCost = it->cost;
            cost = it->cost;
            position = it;
            counter = 0;
            if (tabuTenure == 0)
            {
                tabuTenure = bestTour.size();
            }
            tabuTenure *= 2;
            changeTenure(tabuList, 2.0f);
            continue;
        }
        if (cost > it->cost)
        {
            move = { it->city2, it->city1 };
            if (std::find_if(tabuList.begin(), tabuList.end(), [&move](const TabuMove& e) { return e.move == move; }) == tabuList.end())
            {
                cost = it->cost;
                position = it;
            }
        }
    }
    return *position;
}

void Instance::changeTenure(std::list<TabuMove>& tabuList, float val)
{
    for (auto it = tabuList.begin(); it != tabuList.end(); ++it)
    {
        it->tenure *= val;
    }
}

void Instance::verifyTenure(std::list<TabuMove>& tabuList)
{
    for (auto it = tabuList.begin(); it != tabuList.end();)
    {
        it->tenure--;
        if (it->tenure <= 0)
        {
            it = tabuList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Instance::tabuSearch()
{
    tabuSize = bestTour.size() * 2;
    tabuTenure = bestTour.size() * 8;
    int neighborhoodSize = 0;

    std::vector<int> currentTour = bestTour;
    std::vector<Move> neighborhood;
    Move bestMove;
    std::list<TabuMove> tabuList;

    for (int i = 1; i < bestTour.size(); ++i)
    {
        for (int k = i + 1; k < bestTour.size(); ++k)
        {
            ++neighborhoodSize;
        }
    }
    neighborhood.resize(neighborhoodSize);

    int currentCost = bestCost;
    int workingCost = bestCost;
    int iterations = 100;

    while (iterations > 0)
    {
        int j = 0;
        verifyTenure(tabuList);
        for (int i = 1; i < bestTour.size(); ++i)
        {
            for (int k = i + 1; k < bestTour.size(); ++k)
            {
                workingCost = calculateDistance(currentTour, i, k, currentCost);
                workingCost = calculateDistance(currentTour, k, i, workingCost);
                neighborhood[j] = { workingCost, i, k };
                ++j;
            }
        }
        bestMove = findBest(neighborhood, tabuList);
        std::swap(currentTour[bestMove.city1], currentTour[bestMove.city2]);
        currentCost = bestMove.cost;
        if (tabuList.size() < tabuSize)
        {
            tabuList.push_back({ {bestMove.city2, bestMove.city1}, tabuTenure });
        }
        else
        {
            auto it = std::min_element(tabuList.begin(), tabuList.end(), [](const auto& e1, const auto& e2) 
            {
                return (e1.tenure < e2.tenure);
            });
            *it = { { bestMove.city2, bestMove.city1 }, tabuTenure };
        }
        if (counter == 10)
        {
            counter = 0;
            changeTenure(tabuList, 0.5f);
            tabuTenure /= 2;
        }
        ++counter;
        --iterations;
    }
}
