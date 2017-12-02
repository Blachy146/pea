#include "TabuSearch.hpp"

#include <fstream>
#include <sstream>
#include <iostream>


TabuSearch::TabuSearch()
{
}

void TabuSearch::loadFromFile(const std::string& filePath) 
{
    parser.loadDataFromFile(filePath);
    distances = parser.getCitiesMatrix();
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

TabuSearch::~TabuSearch()
{
}
