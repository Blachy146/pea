#pragma once

#include <TSP.h>

#include <string>
#include <vector>
#include <Node.h>

class TSPBranchAndBound : public TSP
{
public:
    explicit TSPBranchAndBound(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    int calculateUpperBound() const;
    int calculateRootLowerBound() const;
    int calculateNodeLowerBound(const std::vector<int> &usedCities, const std::vector<double> &usedDistances) const;

    std::vector<std::vector<double>> distances;
    std::vector<Node> latestNodes;
    double upperBound;
};