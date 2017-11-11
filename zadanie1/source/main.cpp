#include <TSPBruteForce.h>
#include <TSPBranchAndBound.h>
#include <TSP.h>
#include <TSPBranchAndBoundGreedy.h>
#include <iostream>
#include <TSPGenerator.h>
#include <chrono>
#include <memory>
#include <fstream>


int main()
{
    std::ofstream ofs("/home/bmalecki/times");
    const std::vector<int> instanceSizes {6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
    const int numberOfInstances = 3;
    std::vector<double> times {0.0, 0.0, 0.0};

    TSPGenerator tspGenerator;

    for(auto instanceSize : instanceSizes)
    {
        for(auto i = 0; i < numberOfInstances; ++i)
        {
            tspGenerator.generate(instanceSize);

            for(auto j = 0; j < 3; ++j)
            {
                std::unique_ptr<TSP> tsp;

                std::cout << "--------------------------------------------\n";
                std::cout << "Number of cities = " << instanceSize << "\n";

                switch(j)
                {
                    case 0:
                        std::cout << "BnB Greedy\n";
                        tsp = std::make_unique<TSPBranchAndBoundGreedy>("/home/bmalecki/tsp");
                        break;
                    case 1:
                        std::cout << "BnB\n";
                        tsp = std::make_unique<TSPBranchAndBound>("/home/bmalecki/tsp");
                        break;
                    case 2:
                        if(instanceSize <= 12)
                        {
                            std::cout << "Bruteforce\n";
                            tsp = std::make_unique<TSPBruteForce>("/home/bmalecki/tsp");
                        }
                        else
                        {
                            std::cout << "Too much for bruteforce\n";
                        }
                        break;
                }

                if(tsp != nullptr)
                {
                    auto start = std::chrono::steady_clock::now();
                    auto result = tsp.get()->getPath();
                    auto end = std::chrono::steady_clock::now();

                    std::cout << "Result = " << result.second << "\n";

                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    std::cout << "Duration = " << duration << "\n";
                    std::cout << "--------------------------------------------\n";

                    times[j] += duration;
                }
            }
        }

        for(auto k = 0; k < times.size(); ++k)
        {
            if(k == 0)
            {
                ofs << "---------------------------------------\n";
                ofs << "BnB Greedy:\n";
            }
            else if(k == 1)
            {
                ofs << "---------------------------------------\n";
                ofs << "BnB:\n";
            }
            else if(k == 2)
            {
                ofs << "---------------------------------------\n";
                ofs << "Bruteforce:\n";
            }

            ofs << "Instance size = " << instanceSize << "\n";
            ofs << "Time = " << times[k]/numberOfInstances << "\n";
            ofs << "---------------------------------------\n";
        }

        times[0] = 0.0;
        times[1] = 0.0;
        times[2] = 0.0;
    }

    ofs.close();
}