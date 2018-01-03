#pragma once

#include <vector>


struct Solution
{
    int distance = 0;
    std::vector<int> path {};

    bool operator<(const Solution& other) const
    {
        return this->distance < other.distance;
    }
};