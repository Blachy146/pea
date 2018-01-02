#include "GeneticTSP.hpp"
#include "Parser.hpp"

#include <stdexcept>


GeneticTSP::GeneticTSP()
{
}

void GeneticTSP::geneticAlgorithm()
{

}

void GeneticTSP::tryToLoadFromFile(const std::string& filePath)
{
    try
    {
        parser.tryToLoadFromFile(filePath);
    }
    catch(const std::runtime_error& e)
    {
        throw e;
    }

    distances = parser.getDistancesMatrix();
}

GeneticTSP::~GeneticTSP()
{
}