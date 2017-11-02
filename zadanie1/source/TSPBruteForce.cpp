#include <TSPBruteForce.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


TSPBruteForce::TSPBruteForce(const std::string& dataFilePath)
{
    std::ifstream ifs(dataFilePath);
    auto numberOfCities = 0;
    std::string line = "";

    ifs >> numberOfCities;
    std::getline(ifs, line);

    for(auto i = 0; i < numberOfCities; ++i)
    {
        std::getline(ifs, line);

        std::stringstream lineStream(line);
        std::vector<double> oneCityDistances;

        for(auto j = 0; j < numberOfCities; ++j)
        {
            double distance;

            lineStream >> distance;
            oneCityDistances.push_back(distance);
        }

        distances.push_back(oneCityDistances);
    }
}

namespace
{

std::vector<int> createVectorOfCities(unsigned long numberOfCities)
{
    std::vector<int> cities;

    for(auto i = 0; i < numberOfCities; ++i)
    {
        cities.push_back(i);
    }

    return cities;
}

std::vector<int> fillCitiesWithReturnCity(const std::vector<int>& cities)
{
    auto citiesWithReturnCity = cities;
    citiesWithReturnCity.push_back(cities[0]);

    return citiesWithReturnCity;
}

}

std::pair<std::vector<int>, double> TSPBruteForce::getPath()
{
    std::vector<int> cities = createVectorOfCities(distances.size());

    auto bestPermutation = fillCitiesWithReturnCity(cities);
    auto bestDistance = getDistanceOfPermutation(bestPermutation);

    do
    {
        auto currentPermutation = fillCitiesWithReturnCity(cities);
        auto currentDistance = getDistanceOfPermutation(currentPermutation);

        if(currentDistance < bestDistance)
        {
            bestDistance = currentDistance;
            bestPermutation = currentPermutation;
        }
    }
    while(std::next_permutation(cities.begin(), cities.end()));

    return std::make_pair(bestPermutation, bestDistance);
}

double TSPBruteForce::getDistanceOfPermutation(const std::vector<int> &cities) const
{
    auto distance = 0.0;

    for(auto i = 0; i < cities.size()-1; ++i)
    {
        distance += distances[cities[i]][cities[i+1]];
    }

    distance += distances[cities[cities.size()-1]][cities[0]];

    return distance;
}

const std::vector<std::vector<double>>& TSPBruteForce::getCitiesMatrix() const
{
    return distances;
}

