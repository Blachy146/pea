#pragma once

#include <vector>

class Node
{
public:
    std::vector<int> currentPath;
    std::vector<double> currentPathDistances;
    double lowerBound;
    double currentDistance;
};
