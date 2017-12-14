#include "Parser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <iostream>

Parser::Parser()
{
}

void Parser::tryToLoadFromFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);

    if(!ifs.is_open())
    {
        throw std::runtime_error("Cannot open file!");
    }

    std::string line;
    std::string dataTypeLine;
    std::string dataFormat;
    std::string dataType;
    std::stringstream lineStream;

    auto loopNumber = 0;

    do
    {
        ++loopNumber;

        std::getline(ifs, line);
        lineStream = std::stringstream(line);
        lineStream >> dataFormat;

        if(dataFormat == "EDGE_WEIGHT_TYPE" || dataFormat == "EDGE_WEIGHT_TYPE:")
        {
            dataTypeLine = line;
        }

        if(loopNumber > 7)
            break;

    } while(dataFormat != "EDGE_WEIGHT_FORMAT" && dataFormat != "EDGE_WEIGHT_FORMAT:");

    std::stringstream typeStream(dataTypeLine);
    typeStream >> dataType;

    if(dataFormat == "EDGE_WEIGHT_FORMAT")
    {
        lineStream >> dataFormat;
        lineStream >> dataFormat;
    }
    else if(dataFormat == "EDGE_WEIGHT_FORMAT:")
    {
        lineStream >> dataFormat;
    }
    else if(dataType == "EDGE_WEIGHT_TYPE:")
    {
        typeStream >> dataType;
    }
    else if(dataType == "EDGE_WEIGHT_TYPE")
    {
        typeStream >> dataType;
        typeStream >> dataType;
    }

    ifs.close();

    if(dataFormat == "LOWER_DIAG_ROW" || dataType == "LOWER_DIAG_ROW")
    {
        loadLowerDiagonalRow(filePath);    
    }
    else if(dataFormat == "FULL_MATRIX" || dataType == "FULL_MATRIX")
    {
        loadCitiesMatrix(filePath);
    }
    else if(dataFormat == "EUC_2D" || dataType == "EUC_2D")
    {
        loadCitiesList(filePath);
    }
    else
    {
        throw std::runtime_error("Unknown data type!");
    }
}

std::vector<std::vector<int> > Parser::getCitiesMatrix() const
{
    return citiesMatrix;
}

void Parser::convertToMatrix()
{
    std::vector<std::vector<int> > matrix(citiesList.size(), std::vector<int>(citiesList.size()));
    int x, y;
    auto it1 = citiesList.begin();
    auto it2 = citiesList.begin();
    for (int i = 0; i < citiesList.size(); ++i, ++it1)
    {
        it2 = citiesList.begin();
        for (auto k = 0; k < citiesList.size(); ++k, ++it2)
        {
            x = std::get<1>(*it1) - std::get<1>(*it2);
            y = std::get<2>(*it1) - std::get<2>(*it2);
            matrix[i][k] = (lround(sqrt((x * x + y * y))));
        }
    }
    citiesMatrix = std::move(matrix);
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
            break;
        }
        citiesList.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }
    convertToMatrix();
    return true;
}

bool Parser::loadCitiesMatrix(const std::string& filename)
{
    int dimension = 0;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    file >> dimension;
    citiesMatrix.resize(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            file >> line;
            citiesMatrix[i].push_back(std::stoi(line));
        }
    }
    return true;
}

bool Parser::loadLowerDiagonalRow(const std::string & filename)
{
    int dimension = 0;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    file >> dimension;
    citiesMatrix.resize(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < (i + 1); ++j)
        {
            file >> line;
            citiesMatrix[i].push_back(std::stoi(line));
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

Parser::~Parser()
{
}
