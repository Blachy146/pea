#pragma once


#include <TSP.h>

#include <string>
#include <vector>
#include <Node.h>

class TSPBranchAndBoundGreedy : public TSP
{
public:
    explicit TSPBranchAndBoundGreedy(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    int calculateRootLowerBound() const;
    int calculateNodeLowerBound(const Node& node) const;

    std::vector<std::vector<double>> distances;
    std::vector<Node> latestNodes;
};
