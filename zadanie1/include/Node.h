#pragma once

#include <vector>

class Node
{
public:
    std::vector<int> currentPath;
    std::vector<int> availableCities;
    double lowerBound;
    double currentDistance;
};
