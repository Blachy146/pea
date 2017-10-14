#pragma once

#include <TravellingSalesman.h>

#include <string>
#include <vector>

class TravellingSalesmanBruteForce : public TravellingSalesman
{
public:
    explicit TravellingSalesmanBruteForce(const std::string& dataFilePath);

    std::pair<std::vector<int>, double> getPath() const override;
    const std::vector<std::vector<double>>& getCitiesMatrix() const;
private:
    double getDistanceOfPermutation(const std::vector<int>& cities) const;

    std::vector<std::vector<double>> distances;
};
