#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>


class Parser
{
public:
    Parser();
    void tryToLoadFromFile(const std::string& filePath);
    std::vector<std::vector<int>> getDistancesMatrix() const;
    ~Parser();
private:
    bool loadCitiesEuclideanList(const std::string& filename);
    bool loadCitiesMatrix(const std::string& filename);
    bool loadCitiesLowerDiagonalRow(const std::string& filename);

    std::list<std::tuple<int, int, int> > euclideanList;
    std::vector<std::vector<int> > distancesMatrix;
};