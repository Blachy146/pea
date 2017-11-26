#pragma once

#include <string>
#include <vector>

class TabuSearch
{
public:
    TabuSearch();

    void readDistancesFromFile(const std::string& filePath);
    void printDistancesMatrix() const;

    ~TabuSearch();
private:
    std::vector<std::vector<int>> distances;
};
