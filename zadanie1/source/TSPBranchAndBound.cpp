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
    std::cerr << "1\n";
    bool endOfCalculatingPath = false;
    int startCity = 0;

    Node rootNode;

    rootNode.currentPath.push_back(startCity);
    rootNode.lowerBound = calculateRootLowerBound();
    rootNode.currentDistance = 0;

    latestNodes.push_back(rootNode);
    std::cerr << "2\n";

    while(!endOfCalculatingPath)
    {
        std::vector<std::vector<Node>> currentBranches;
        std::cerr << "3\n";

        for(auto node : latestNodes)
        {
            std::cerr << "4\n";
            std::vector<int> availableCities;

            for(auto i = 0; i < distances.size(); ++i)
            {
                if(std::find(node.currentPath.begin(), node.currentPath.end(), i) == node.currentPath.end())
                {
                    availableCities.push_back(i);
                    std::cerr << "5\n";
                }
            }
            std::cerr << "6\n";

            if(availableCities.size() == 0)
            {
                availableCities.push_back(*node.currentPath.begin());
                std::cerr << "7\n";
                endOfCalculatingPath = true;
            }

            std::vector<Node> branchNodes;
            std::cerr << "8\n";

            for(auto nextCity : availableCities)
            {
                std::cerr << "9\n";
                Node newNode;

                std::cerr << "x\n";
                newNode.currentPath = node.currentPath;
                std::cerr << "xx\n";
                newNode.currentPath.push_back(nextCity);
                std::cerr << "xxx\n";
                newNode.currentPathDistances = node.currentPathDistances;
                std::cerr << "xxxx\n";
                newNode.currentPathDistances.push_back(distances[node.currentPath.back()][nextCity]);
                std::cerr << "xxxxx\n";
                newNode.lowerBound = calculateNodeLowerBound(newNode.currentPath, newNode.currentPathDistances);
                std::cerr << "xxxxxx\n";
                newNode.currentDistance = node.currentDistance + newNode.currentPathDistances.back();
                std::cerr << "xxxxxxx\n";

                if(newNode.lowerBound <= upperBound)
                {
                    branchNodes.push_back(newNode);
                    std::cerr << "10\n";
                }
            }

            currentBranches.push_back(branchNodes);
            std::cerr << "11\n";
        }

        latestNodes.clear();
        std::cerr << "12\n";

        for(auto branch : currentBranches)
        {
            for(auto node : branch)
            {
                latestNodes.push_back(node);
                std::cerr << "13\n";
            }
        }

        currentBranches.clear();
    }
    std::cerr << "14\n";

    auto bestNode = std::min_element(latestNodes.begin(), latestNodes.end(), [](auto lhs, auto rhs)
                                                                            {
                                                                                return lhs.currentDistance < rhs.currentDistance;
                                                                            });
    std::cerr << "15\n";

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
    std::cerr << "i\n";
    int lowerBound = 0;

    for(auto usedDistance : usedDistances)
    {
        lowerBound += usedDistance;
    }

    auto lastCity = usedCities.back();
    std::vector<int> citiesTo;

    std::cerr << "ii\n";
    for(auto i = 0; i < distances.size(); ++i)
    {
        if(std::find(usedCities.begin(), usedCities.end(), i) == usedCities.end())
        {
            citiesTo.push_back(i);
        }
    }

    std::cerr << "iii\n";
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

    std::cerr << "iiii\n";
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
    std::cerr << "iiiii\n";

    return lowerBound;
}

