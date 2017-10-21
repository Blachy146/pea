#pragma once

#include <TSP.h>

#include <string>
#include <vector>

class TSPBranchAndBound : public TSP
{
public:
    explicit TSPBranchAndBound(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    int calculateUpperBound() const;
    int calculateRootLowerBound() const;

    std::vector<std::vector<double>> distances;
};