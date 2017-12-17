#pragma once

#include "Parser.hpp"
#include "Move.hpp"

#include <vector>
#include <string>

class TabuSearch
{
public:
    TabuSearch();

    void tabuSearch();
    void setExecuteTime(double time);
    void printDistancesMatrix() const;
    void tryToLoadFromFile(const std::string& filePath);
    void setDiversificationMaxCount(int maxCount);
    void setDiversification(bool divers);
    void setTabuTenure(int tenure);
    void setTabuSize(int size);

    ~TabuSearch();
private:
    std::vector<int> calculateGreedy() const;
    int calculatePathDistance(const std::vector<int>& path) const;
    int calculateNeighborhoodSize() const;
    void verifyTabuList(std::list<TabuMove>& tabuList);
    Move findBestMove(const std::vector<Move>& neighborhood, std::list<TabuMove>& tabuList);
    std::vector<int> generateRandomSolution() const;

    Parser parser;
    std::vector<std::vector<int>> distances;
    std::vector<int> bestPath; 
    int bestDistance;
    double executeTimeSeconds;
    bool diversification;
    int diversificationMaxCount;
    int counter;
    int tabuSize;
    int tabuTenure;
};