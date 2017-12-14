#pragma once

#include "Parser.hpp"

#include <vector>
#include <string>

class TabuSearch
{
public:
    TabuSearch();

    void printDistancesMatrix() const;
    void tryToLoadFromFile(const std::string& filePath);

    ~TabuSearch();
private:
    Parser parser;
    std::vector<std::vector<int>> distances;
};