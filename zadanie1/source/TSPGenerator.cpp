#include <TSPGenerator.h>

#include <fstream>
#include <random>


class RandomGenerator
{
public:
    RandomGenerator(int lowerBound, int upperBound)
            : distribution(lowerBound, upperBound), engine(std::random_device{}())
    { }

    int operator()()
    {
        return distribution(engine);
    }

    ~RandomGenerator() { }
private:
    std::uniform_int_distribution<int> distribution;
    std::default_random_engine engine;
};

void TSPGenerator::generate(int numberOfCities)
{
    std::ofstream ofs("/home/bmalecki/tsp");
    RandomGenerator randomGenerator(1, 100);
    ofs << numberOfCities;

    for(auto i = 0; i < numberOfCities; ++i)
    {
        ofs << "\n";

        for(auto j = 0; j < numberOfCities; ++j)
        {
            if(i == j)
            {
                ofs << 0 << " ";
            }
            else
            {
                ofs << randomGenerator() << " ";
            }
        }
    }

    ofs.close();
}
