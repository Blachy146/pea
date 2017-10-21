#pragma once

#include <TSP.h>

#include <string>
#include <vector>

class TSPBruteForce : public TSP
{
public:
    explicit TSPBruteForce(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    double getDistanceOfPermutation(const std::vector<int>& cities) const;

    std::vector<std::vector<double>> distances;
};
