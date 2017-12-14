#include "TabuSearch.hpp"

#include <iostream>


TabuSearch::TabuSearch()
{
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

    distances = parser.getCitiesMatrix();
}

TabuSearch::~TabuSearch()
{
}