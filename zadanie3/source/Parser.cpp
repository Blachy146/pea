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
    euclideanList = {};
    distancesMatrix = {};
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
        loadCitiesLowerDiagonalRow(filePath);    
    }
    else if(dataFormat == "FULL_MATRIX" || dataType == "FULL_MATRIX")
    {
        loadCitiesMatrix(filePath);
    }
    else if(dataFormat == "EUC_2D" || dataType == "EUC_2D")
    {
        loadCitiesEuclideanList(filePath);
    }
    else
    {
        throw std::runtime_error("Unknown data type!");
    }
}

std::vector<std::vector<int> > Parser::getDistancesMatrix() const
{
    return distancesMatrix;
}

bool Parser::loadCitiesEuclideanList(const std::string& filename)
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

    while(true) 
    {
        file >> cityNumber >> firstCoordinate >> secondCoordinate;
        if (!file.good())
        {
            break;
        }

        euclideanList.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }

    std::vector<std::vector<int>> matrix(euclideanList.size(), std::vector<int>(euclideanList.size()));
    int x, y;
    auto pos1 = euclideanList.begin();
    auto pos2 = euclideanList.begin();

    for (int i = 0; i < euclideanList.size(); ++i, ++pos1)
    {
        pos2 = euclideanList.begin();

        for (auto k = 0; k < euclideanList.size(); ++k, ++pos2)
        {
            x = std::get<1>(*pos1) - std::get<1>(*pos2);
            y = std::get<2>(*pos1) - std::get<2>(*pos2);
            matrix[i][k] = (round(sqrt((x * x + y * y))));
        }
    }

    distancesMatrix = std::move(matrix);

    return true;
}

bool Parser::loadCitiesMatrix(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    std::string dimensionString;
    std::string line;

    for(auto i = 0; i < 4; ++i)
    {
        std::getline(file, line);
    }

    std::stringstream lineStream(line);
    lineStream >> dimensionString;

    int dimension = 0;

    if(dimensionString == "DIMENSION:")
    {
        lineStream >> dimension;
    }
    else if(dimensionString == "DIMENSION")
    {
        lineStream >> dimensionString;
        lineStream >> dimension;
    }

    distancesMatrix.resize(dimension);

    for(auto i = 0; i < 3; ++i)
    {
        std::getline(file, line);
    }

    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            file >> line;
            distancesMatrix[i].push_back(std::stoi(line));
        }
    }

    return true;
}

bool Parser::loadCitiesLowerDiagonalRow(const std::string & filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    std::string dimensionString;
    std::string line;

    for(auto i = 0; i < 4; ++i)
    {
        std::getline(file, line);
    }

    std::stringstream lineStream(line);
    lineStream >> dimensionString;

    int dimension = 0;

    if(dimensionString == "DIMENSION:")
    {
        lineStream >> dimension;
    }
    else if(dimensionString == "DIMENSION")
    {
        lineStream >> dimensionString;
        lineStream >> dimension;
    }

    for(auto i = 0; i < 3; ++i)
    {
        std::getline(file, line);
    }

    distancesMatrix.resize(dimension);

    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < (i + 1); ++j)
        {
            file >> line;
            distancesMatrix[i].push_back(std::stoi(line));
        }
    }

    for (int i = 0; i < dimension; ++i)
    {
        for (int j = i + 1; j < dimension; ++j)
        {
            distancesMatrix[i].push_back(distancesMatrix[j][i]);
        }
    }
    return true;
}

Parser::~Parser()
{
}
