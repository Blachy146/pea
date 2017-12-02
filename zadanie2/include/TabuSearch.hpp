#pragma once

#include "Parser.hpp"
#include <string>
#include <vector>


class TabuSearch
{
public:
    TabuSearch();

    void loadFromFile(const std::string& filePath);
    void printDistancesMatrix() const;

    ~TabuSearch();
private:
    Parser parser;
    std::vector<std::vector<int>> distances;
};
