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
    std::vector<std::vector<int>> getCitiesMatrix() const;

    ~Parser();
private:
    bool loadCitiesList(const std::string& filename);
    bool loadCitiesMatrix(const std::string& filename);
    bool loadLowerDiagonalRow(const std::string& filename);

    void convertToMatrix();

    std::list<std::tuple<int, int, int> > citiesList;
    std::vector<std::vector<int> > citiesMatrix;
};