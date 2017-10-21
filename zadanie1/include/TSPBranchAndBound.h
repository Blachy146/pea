#pragma once

#include <TSP.h>

#include <string>
#include <vector>

class TSPBranchAndBound : public TSP
{
public:
    explicit TSPBranchAndBound(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() const override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    std::vector<std::vector<double>> distances;
};