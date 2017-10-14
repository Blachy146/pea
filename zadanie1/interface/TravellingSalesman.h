#pragma once

#include <vector>

class TravellingSalesman
{
public:
    virtual std::pair<std::vector<int>, double> getPath() const = 0;
    virtual ~TravellingSalesman() { }
};