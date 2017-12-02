#include "Parser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <iostream>


std::list<std::tuple<int, int, int> > Parser::getCitiesList() const
{
    return citiesList;
}

std::vector<std::vector<int> > Parser::getCitiesMatrix() const
{
    return citiesMatrix;
}

void Parser::loadDataFromFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);

    if(!ifs.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    std::string line = "";

    for(auto i = 0; i < 5; ++i)
    {
        std::getline(ifs, line);
    }

    std::getline(ifs, line);
    std::stringstream lineStream(line);

    std::string dataTypeHeader = "";
    std::string dataType = "";

    lineStream >> dataTypeHeader;
    lineStream >> dataType;

    ifs.close();

    if(dataType == "FULL_MATRIX")
    {
        loadCitiesMatrix(filePath);
    }
    else if(dataType == "LOWER_DIAG_ROW")
    {
        loadLowerDiagonalRow(filePath);
    }
    else
    {
        throw std::runtime_error("Unknown data type!");
    }
}

bool Parser::loadCitiesList(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    int cityNumber, firstCoordinate, secondCoordinate;
    while (file.good())
    {
        file >> line;
        if (line == "NODE_COORD_SECTION")
        {
            break;
        }
    }
    for (;;)
    {
        file >> cityNumber >> firstCoordinate >> secondCoordinate;
        if (!file.good())
        {
            return true;
        }
        citiesList.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }
}

bool Parser::loadCitiesMatrix(const std::string& filename)
{
    std::ifstream ifs(filename);

    if (!ifs.is_open())
    {
        throw std::runtime_error("Can't open ifs");
    }

    std::string line;

    for(auto i = 0; i < 2; ++i)
    {
        std::getline(ifs, line);
    }

    std::getline(ifs, line);

    std::string dimensionHeader = "";
    int dimension = 0;

    std::stringstream lineStream(line);

    lineStream >> dimensionHeader;
    lineStream >> dimension;

    citiesMatrix.resize(dimension);

    for(auto i = 0; i < 4; ++i)
    {
        std::getline(ifs, line);
    }

    std::string distance = "";

    for (auto i = 0; i < dimension; ++i)
    {
        for (auto j = 0; j < dimension; ++j)
        {
            ifs >> distance;
            citiesMatrix[i].push_back(std::stoi(distance));
        }
    }

    return true;
}

bool Parser::loadLowerDiagonalRow(const std::string & filename)
{
    std::ifstream ifs(filename);

    if (!ifs.is_open())
    {
        throw std::runtime_error("Can't open ifs");
    }

    std::string line;

    for(auto i = 0; i < 2; ++i)
    {
        std::getline(ifs, line);
    }

    std::getline(ifs, line);

    std::string dimensionHeader = "";
    int dimension = 0;

    std::stringstream lineStream(line);

    lineStream >> dimensionHeader;
    lineStream >> dimension;

    citiesMatrix.resize(dimension);

    for(auto i = 0; i < 4; ++i)
    {
        std::getline(ifs, line);
    }

    std::string distance = "";

    for (auto i = 0; i < dimension; ++i)
    {
        for (auto j = 0; j < (i + 1); ++j)
        {
            ifs >> distance;
            citiesMatrix[i].push_back(std::stoi(distance));
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = i + 1; j < dimension; ++j)
        {
            citiesMatrix[i].push_back(citiesMatrix[j][i]);
        }
    }

    return true;
}