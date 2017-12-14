#pragma once

#include <vector>
#include <list>
#include <tuple>
#include <numeric>
#include <chrono>

struct Move
{
    int cost;
    int city1;
    int city2;
};

struct TabuMove
{
    std::tuple<int, int> move;
    int tenure;
};

class Instance
{
public:
    Instance(std::vector<std::vector<int> > matrix);
    int getCost();
    void printTime();
    void printForTest();
private:
    std::tuple<int, int> findMin(const int row, std::vector<int>& visited);
    void greedyAlgorithm();
    int calculateDistance(std::vector<int>& tour, int city1, int city2, int cost) const;
    Move findBest(const std::vector<Move>& neighborhood, std::list<TabuMove>& tabuList);
    void changeTenure(std::list<TabuMove>& tabuList, float val);
    void verifyTenure(std::list<TabuMove>& tabuList);
    void tabuSearch();

    std::vector<std::vector<int> > costMatrix;
    std::vector<int> bestTour;
    std::chrono::duration<double> time;
    int bestCost = 0;
    int counter = 0;
    int tabuSize = 0;
    int tabuTenure = 0;
};