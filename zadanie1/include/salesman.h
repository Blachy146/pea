#pragma once

#include <string>

class TravellingSalesman
{
public:
    TravellingSalesman(std::string dataFilePath);

    std::string getPath();

    ~TravellingSalesman();
private:
    std::string fileContent;
};
