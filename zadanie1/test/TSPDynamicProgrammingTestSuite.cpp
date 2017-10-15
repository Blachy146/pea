#include <TSPDynamicProgramming.h>

#include <gtest/gtest.h>
#include <fstream>

using namespace ::testing;

class TSPDynamicProgrammingTestSuite : public Test
{
public:
    TSPDynamicProgrammingTestSuite()
    {
        std::ofstream ofs(distancesPath);

        std::string city0 = "0.0  3.0  4.0  2.0  7.0";
        std::string city1 = "3.0  0.0  4.0  6.0  3.0";
        std::string city2 = "4.0  4.0  0.0  5.0  8.0";
        std::string city3 = "2.0  6.0  5.0  0.0  6.0";
        std::string city4 = "7.0  3.0  8.0  6.0  0.0";

        distances = city0 + "\n" + city1 + "\n" + city2 + "\n" + city3 + "\n" + city4;

        ofs << distances;

        ofs.close();

        distancesMatrix = {{0.0, 3.0, 4.0, 2.0, 7.0},
                           {3.0, 0.0, 4.0, 6.0, 3.0},
                           {4.0, 4.0, 0.0, 5.0, 8.0},
                           {2.0, 6.0, 5.0, 0.0, 6.0},
                           {7.0, 3.0, 8.0, 6.0, 0.0}};
    }

    const std::string distancesPath = "/tmp/distances";
    std::string distances;
    std::vector<std::vector<double>> distancesMatrix;
};

TEST_F(TSPDynamicProgrammingTestSuite, constructorShouldLoadDistancesFromFile)
{
    TSPDynamicProgramming salesman(distancesPath);

    EXPECT_EQ(distancesMatrix, salesman.getCitiesMatrix());
}
