#include <TSPBranchAndBound.h>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <list>

TSPBranchAndBound::TSPBranchAndBound(const std::string &dataFilePath)
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

    upperBound = calculateUpperBound();
}

void TSPBranchAndBound::branchAndBound(Node &node)
{
    if (node.currentPath.size() == distances.size())
    {
        node.currentDistance += distances[node.currentPath.back()][0];
        if (node.currentDistance < bestDistance)
        {
            bestDistance = node.currentDistance;
            bestPath = node.currentPath;
        }
        return;
    }

    std::vector<Node> nodes;

    for(auto city : node.availableCities)
    {
        Node newNode;
        newNode.currentPath = node.currentPath;
        newNode.currentPath.push_back(city);
        newNode.currentDistance = node.currentDistance + distances[node.currentPath.back()][city];
        newNode.lowerBound = calculateNodeLowerBound(newNode);

        if(newNode.lowerBound < upperBound)
        {
            newNode.availableCities = node.availableCities;
            newNode.availableCities.erase(std::find(newNode.availableCities.begin(), newNode.availableCities.end(), city));

            nodes.push_back(newNode);
        }
    }

    for (auto& node : nodes)
    {
        branchAndBound(node);
    }
}

std::pair<std::vector<int>, double> TSPBranchAndBound::getPath()
{
    int startCity = 0;
    bestDistance = calculateUpperBound();

    Node rootNode;
    rootNode.currentPath.push_back(startCity);
    rootNode.lowerBound = calculateRootLowerBound();
    rootNode.currentDistance = 0;

    for(auto i = 0; i < distances.size(); ++i)
    {
        if(i != startCity)
            rootNode.availableCities.push_back(i);
    }

    branchAndBound(rootNode);

    return std::make_pair(bestPath, bestDistance);

    /*
    bool endOfCalculatingPath = false;
    std::vector<Node> latestNodes;
    std::vector<Node> currentNodes;



    latestNodes.push_back(rootNode);

    while(!endOfCalculatingPath)
    {
        currentNodes.clear();

        for(auto node : latestNodes)
        {
            if(node.availableCities.size() == 0)
            {
                node.availableCities.push_back(*node.currentPath.begin());
                endOfCalculatingPath = true;
            }

            for(auto nextCity : node.availableCities)
            {

            }
        }

        latestNodes.clear();

        for(auto node : currentNodes)
        {
            latestNodes.push_back(std::move(node));
        }

    }

    std::cout << "Number of latest nodes = " << latestNodes.size() << "\n";

    auto bestNode = std::min_element(latestNodes.begin(), latestNodes.end(), [](auto lhs, auto rhs)
                                                                            {
                                                                                return lhs.currentDistance < rhs.currentDistance;
                                                                            });

    return std::make_pair(bestNode->currentPath, bestNode->currentDistance);
     */
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
    int startCity = 0;
    int upperBound = 0;
    std::vector<int> path;
    std::list<int> availableCities;

    for(auto i = 0; i < distances.size(); ++i)
    {
        if(i != startCity)
        {
            availableCities.push_back(i);
        }
    }

    path.push_back(startCity);

    while(path.size() < distances.size())
    {
        auto lastCity = path.back();
        auto bestCity = *availableCities.begin();
        auto bestCityDistance = distances[lastCity][*availableCities.begin()];

        for(auto city : availableCities)
        {
            auto distance = distances[lastCity][city];

            if(distance < bestCityDistance)
            {
                bestCity = city;
                bestCityDistance = distance;
            }
        }

        path.push_back(bestCity);
        availableCities.remove(bestCity);
        upperBound += bestCityDistance;
    }

    upperBound += distances[path.back()][path.front()];
    path.push_back(*path.begin());

    return upperBound;
}

int TSPBranchAndBound::calculateNodeLowerBound(const Node& node) const
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

