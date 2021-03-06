#include <TSPBranchAndBoundGreedy.h>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

TSPBranchAndBoundGreedy::TSPBranchAndBoundGreedy(const std::string &dataFilePath){
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

std::pair<std::vector<int>, double> TSPBranchAndBoundGreedy::getPath()
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

            Node lowestLowerBoundNode;

            lowestLowerBoundNode.currentPath = node.currentPath;
            lowestLowerBoundNode.currentPath.push_back(availableCities[0]);
            lowestLowerBoundNode.lowerBound = calculateNodeLowerBound(node);
            lowestLowerBoundNode.currentDistance = node.currentDistance + distances[node.currentPath.back()][availableCities[0]];

            for(auto nextCity : availableCities)
            {
                Node newNode;

                newNode.currentPath = node.currentPath;
                newNode.currentPath.push_back(nextCity);
                newNode.lowerBound = calculateNodeLowerBound(newNode);
                newNode.currentDistance = node.currentDistance + distances[node.currentPath.back()][nextCity];

                if(newNode.lowerBound < lowestLowerBoundNode.lowerBound)
                {
                    lowestLowerBoundNode = newNode;
                }
            }

            branchNodes.push_back(lowestLowerBoundNode);
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

const std::vector<std::vector<double>>& TSPBranchAndBoundGreedy::getCitiesMatrix() const
{
    return distances;
}

int TSPBranchAndBoundGreedy::calculateRootLowerBound() const
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

int TSPBranchAndBoundGreedy::calculateNodeLowerBound(const Node& node) const
{
    int lowerBound = 0;

    lowerBound += node.currentDistance;

    auto lastCity = node.currentPath.back();

    std::vector<double> availableDistances;

    for(auto city : node.availableCities)
    {
        availableDistances.push_back(distances[lastCity][city]);
    }

    if(availableDistances.size() == 0)
        return lowerBound;

    lowerBound += *std::min_element(availableDistances.begin(), availableDistances.end());

    auto citiesTo = node.availableCities;
    std::vector<int> citiesFrom = node.availableCities;
    citiesTo.push_back(*node.currentPath.begin());

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

