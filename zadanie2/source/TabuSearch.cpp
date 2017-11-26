#include "TabuSearch.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

TabuSearch::TabuSearch()
{

}

void TabuSearch::readDistancesFromFile(const std::string& filePath) 
{
    std::ifstream ifs(filePath);

    auto numberOfCities = 0;
    std::string line = "";

    ifs >> numberOfCities;
    std::getline(ifs, line);

    for(auto i = 0; i < numberOfCities; ++i)
    {
        std::getline(ifs, line);

        std::stringstream lineStream(line);
        std::vector<int> oneCityDistances;

        for(auto j = 0; j < numberOfCities; ++j)
        {
            int distance;

            lineStream >> distance;
            oneCityDistances.push_back(distance);
        }

        distances.push_back(oneCityDistances);
    }
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
