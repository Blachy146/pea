#include <TSPBruteForce.h>
#include <TSPBranchAndBound.h>
#include <TSPBranchAndBoundGreedy.h>
#include <iostream>


int main()
{
    TSPBranchAndBoundGreedy tsp("/home/bmalecki/file");
    auto result = tsp.getPath();

    for(auto elem : result.first)
        std::cout << elem << " ";
    std::cout << "\n";
    std::cout << "Path length b&b greedy = " << result.second;
    std::cout << "\n";
//-----------------------------------------------------------------------
    TSPBruteForce tsp1("/home/bmalecki/1");
    auto result1 = tsp1.getPath();

    for(auto elem : result1.first)
        std::cout << elem << " ";
    std::cout << "\n";
    std::cout << "Path length brute = " << result1.second;
    std::cout << "\n";
//-----------------------------------------------------------------------
    TSPBranchAndBound tsp2("/home/bmalecki/1");
    auto result2 = tsp2.getPath();

    for(auto elem : result2.first)
        std::cout << elem << " ";
    std::cout << "\n";
    std::cout << "Path length b&b= " << result2.second << "\n";
//----------------------------------------------------------------
    auto matrix = tsp1.getCitiesMatrix();
    std::cout << "\n------------Matrix------------\n";
    for(auto i : matrix)
    {
        for(auto j : i)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
//--------------------------------------------------------------
}