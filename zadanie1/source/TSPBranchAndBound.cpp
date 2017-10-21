#include <TSPBranchAndBound.h>

#include <fstream>
#include <sstream>

TSPBranchAndBound::TSPBranchAndBound(const std::string &dataFilePath)
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

std::pair<std::vector<int>, double> TSPBranchAndBound::getPath()
{
    return std::make_pair(std::vector<int>(), double());
}

const std::vector<std::vector<double>>& TSPBranchAndBound::getCitiesMatrix() const
{
    return distances;
}

int TSPBranchAndBound::calculateFirstUpperBound() const
{
    return 0;
}
