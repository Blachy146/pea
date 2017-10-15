#include <TSPDynamicProgramming.h>

#include <fstream>
#include <sstream>

TSPDynamicProgramming::TSPDynamicProgramming(const std::string &dataFilePath)
{
    std::ifstream ifs(dataFilePath);

    while(!ifs.eof())
    {
        std::string line = "";

        std::getline(ifs, line);

        std::stringstream lineStream(line);
        std::vector<double> oneCityDistances;

        while(!lineStream.eof())
        {
            double distance;

            lineStream >> distance;
            oneCityDistances.push_back(distance);
        }

        distances.push_back(oneCityDistances);
    }
}

std::pair<std::vector<int>, double> TSPDynamicProgramming::getPath() const
{
    return std::make_pair(std::vector<int>(), double());
}

const std::vector<std::vector<double>>& TSPDynamicProgramming::getCitiesMatrix() const
{
    return distances;
}
