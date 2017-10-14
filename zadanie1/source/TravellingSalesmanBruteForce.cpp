#include <TravellingSalesmanBruteForce.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


TravellingSalesmanBruteForce::TravellingSalesmanBruteForce(const std::string& dataFilePath)
{
    std::ifstream ifs(dataFilePath);

    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<double> oneCityDistances;
        std::stringstream lineStream(line);

        while(!lineStream.eof())
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

std::pair<std::vector<int>, double> TravellingSalesmanBruteForce::getPath() const
{
    std::vector<int> cities = createVectorOfCities(distances.size());

    auto bestPermutation = fillCitiesWithReturnCity(cities);
    auto bestDistance = getDistanceOfPermutation(cities);

    do
    {
        auto currentPermutation = fillCitiesWithReturnCity(cities);
        auto currentDistance = getDistanceOfPermutation(cities);

        if(currentDistance < bestDistance)
        {
            bestDistance = currentDistance;
            bestPermutation = currentPermutation;
        }
    }
    while(std::next_permutation(cities.begin(), cities.end()));

    return std::make_pair(bestPermutation, bestDistance);
}

double TravellingSalesmanBruteForce::getDistanceOfPermutation(const std::vector<int> &cities) const
{
    auto distance = 0.0;

    for(auto i = 0; i < cities.size()-1; ++i)
    {
        distance += distances[cities[i]][cities[i+1]];
    }

    distance += distances[cities[cities.size()-1]][cities[0]];

    return distance;
}

const std::vector<std::vector<double>>& TravellingSalesmanBruteForce::getCitiesMatrix() const
{
    return distances;
}

