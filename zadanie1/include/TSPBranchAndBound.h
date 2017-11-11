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
    void branchAndBound(Node& node);
    int calculateUpperBound() const;
    int calculateRootLowerBound() const;
    int calculateNodeLowerBound(const Node& node) const;

    std::vector<std::vector<double>> distances;
    double upperBound;
    double bestDistance;
    std::vector<int> bestPath;
};