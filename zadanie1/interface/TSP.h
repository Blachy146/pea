#pragma once

#include <vector>

class TSP
{
public:
    virtual std::pair<std::vector<int>, double> getPath() const = 0;
    virtual ~TSP() { }
};