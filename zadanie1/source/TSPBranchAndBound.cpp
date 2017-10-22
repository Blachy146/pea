#include <TSPBranchAndBound.h>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

TSPBranchAndBound::TSPBranchAndBound(const std::string &dataFilePath)
{
    std::ifstream ifs(dataFilePath);

    while(!ifs.eof())
    {
        std::string line = "";

        std::getline(ifs, line);

        std::stringstream lineStream(line);
        std::vector<double> oneCityDistances;

        while(!lineStream.eof())
        {
            double distance;

            lineStream >> distance;
            oneCityDistances.push_back(distance);
        }

        distances.push_back(oneCityDistances);
    }

    upperBound = calculateUpperBound();
}

std::pair<std::vector<int>, double> TSPBranchAndBound::getPath()
{
    bool endOfCalculatingPath = false;
    int startCity = 0;

    Node rootNode;

    rootNode.currentPath.push_back(startCity);
    rootNode.lowerBound = calculateRootLowerBound();
    rootNode.currentDistance = 0;

    latestNodes.push_back(rootNode);

    while(!endOfCalculatingPath)
    {
        std::vector<std::vector<Node>> currentBranches;

        for(auto node : latestNodes)
        {
            std::vector<int> availableCities;

            for(auto i = 0; i < distances.size(); ++i)
            {
                if(std::find(node.currentPath.begin(), node.currentPath.end(), i) == node.currentPath.end())
                {
                    availableCities.push_back(i);
                }
            }

            if(availableCities.size() == 0)
            {
                availableCities.push_back(*node.currentPath.begin());
                endOfCalculatingPath = true;
            }

            std::vector<Node> branchNodes;

            for(auto nextCity : availableCities)
            {
                Node newNode;

                newNode.currentPathDistances = node.currentPathDistances;
                newNode.currentPathDistances.push_back(distances[node.currentPath.back()][nextCity]);
                newNode.currentPath = node.currentPath;
                newNode.currentPath.push_back(nextCity);
                newNode.lowerBound = calculateNodeLowerBound(newNode.currentPath, newNode.currentPathDistances);
                newNode.currentDistance = node.currentDistance + newNode.currentPathDistances.back();

                if(newNode.lowerBound <= upperBound)
                {
                    branchNodes.push_back(newNode);
                }
            }

            currentBranches.push_back(branchNodes);
        }

        latestNodes.clear();

        for(auto branch : currentBranches)
        {
            for(auto node : branch)
            {
                latestNodes.push_back(node);
            }
        }

        currentBranches.clear();
    }

    auto bestNode = std::min_element(latestNodes.begin(), latestNodes.end(), [](auto lhs, auto rhs)
                                                                            {
                                                                                return lhs.currentDistance < rhs.currentDistance;
                                                                            });

    return std::make_pair(bestNode->currentPath, bestNode->currentDistance);
}

const std::vector<std::vector<double>>& TSPBranchAndBound::getCitiesMatrix() const
{
    return distances;
}

int TSPBranchAndBound::calculateRootLowerBound() const
{
    int lowerBound = 0;

    for(auto oneCityDistances : distances)
    {
        lowerBound += *std::min_element(oneCityDistances.begin(), oneCityDistances.end(), [](auto lhs, auto rhs)
                                                                                        {
                                                                                            if(lhs == 0)
                                                                                                return false;
                                                                                            else if(rhs == 0)
                                                                                                return true;
                                                                                            else
                                                                                                return lhs < rhs;
                                                                                        });
    }

    return lowerBound;
}

int TSPBranchAndBound::calculateUpperBound() const
{
    int upperBound = 0;

    for(auto distance : distances[0])
    {
        upperBound += distance;
    }

    upperBound += distances[distances.size() - 1][0];

    return upperBound;
}

int TSPBranchAndBound::calculateNodeLowerBound(const std::vector<int> &usedCities, const std::vector<double> &usedDistances) const
{
    int lowerBound = 0;

    for(auto usedDistance : usedDistances)
    {
        lowerBound += usedDistance;
    }

    auto lastCity = usedCities.back();
    std::vector<int> citiesTo;

    for(auto i = 0; i < distances.size(); ++i)
    {
        if(std::find(usedCities.begin(), usedCities.end(), i) == usedCities.end())
        {
            citiesTo.push_back(i);
        }
    }

    std::vector<double> availableDistances;

    for(auto city : citiesTo)
    {
        availableDistances.push_back(distances[lastCity][city]);
    }

    if(availableDistances.size() == 0)
        return lowerBound;

    lowerBound += *std::min_element(availableDistances.begin(), availableDistances.end());

    std::vector<int> citiesFrom = citiesTo;
    citiesTo.push_back(*usedCities.begin());

    for(auto cityFrom : citiesFrom)
    {
        availableDistances.clear();

        for(auto cityTo : citiesTo)
        {
            if(cityFrom != cityTo)
            {
                availableDistances.push_back(distances[cityFrom][cityTo]);
            }
        }

        lowerBound += *std::min_element(availableDistances.begin(), availableDistances.end());
    }

    return lowerBound;
}

