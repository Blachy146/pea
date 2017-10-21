#include <TSPBranchAndBound.h>

#include <fstream>
#include <sstream>
#include <algorithm>

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

int TSPBranchAndBound::calculateRootLowerBound() const
{
    int lowerBound = 0;

    for(auto oneCityDistances : distances)
    {
        lowerBound += *std::min_element(oneCityDistances.begin(), oneCityDistances.end(), [](auto lhs, auto rhs)
                                                                                        {
                                                                                            if(lhs == 0)
                                                                                                return false;
                                                                                            else if(rhs == 0)
                                                                                                return true;
                                                                                            else
                                                                                                return lhs < rhs;
                                                                                        });
    }

    return lowerBound;
}

int TSPBranchAndBound::calculateUpperBound() const
{
    int upperBound = 0;

    for(auto distance : distances[0])
    {
        upperBound += distance;
    }

    upperBound += distances[distances.size() - 1][0];

    return upperBound;
}
