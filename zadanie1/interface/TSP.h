#pragma once

#include <vector>

class TSP
{
public:
    virtual std::pair<std::vector<int>, double> getPath() = 0;
    virtual ~TSP() { }
};