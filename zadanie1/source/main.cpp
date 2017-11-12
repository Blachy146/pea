#include <TSPBruteForce.h>
#include <TSPBranchAndBound.h>
#include <iostream>
#include <TSPGenerator.h>
#include <chrono>
#include <memory>
#include <fstream>

void printMenu()
{
    std::cout << "------------MENU------------\n";
    std::cout << "1. Bruteforce\n";
    std::cout << "2. BnB\n";
    std::cout << "3. Bruteforce i BnB\n";
    std::cout << "0. Wyjscie\n";
}

int getOption()
{
    int option = 0;
    std::cin >> option;

    return option;
}

std::string getFileName()
{
    std::string file;
    std::cout << "Plik: ";
    std::cin >> file;

    return file;
}

int main()
{
    bool endProgram = false;

    while(!endProgram)
    {
        printMenu();
        int option = getOption();

        switch(option)
        {
        case 1:
        {
            auto tsp = std::make_unique<TSPBruteForce>(getFileName());
            auto result = tsp->getPath();
            std::cout << "Distance = " << result.second << "\n";
            for(auto city : result.first)
                std::cout << city << " ";
            std::cout << "\n";
            break;
        }
        case 2:
        {
            auto tsp = std::make_unique<TSPBranchAndBound>(getFileName());
            auto result = tsp->getPath();
            std::cout << "Distance = " << result.second << "\n";
            for(auto city : result.first)
                std::cout << city << " ";
            std::cout << "\n";
            break;
        }
        case 3:
        {
            auto file = getFileName();
            auto brute = std::make_unique<TSPBruteForce>(file);
            auto bnb = std::make_unique<TSPBranchAndBound>(file);
            auto result1 = brute->getPath();
            std::cout << "BruteForce: \n";
            std::cout << "Distance = " << result1.second << "\n";
            for(auto city : result1.first)
                std::cout << city << " ";
            std::cout << "\n";
            auto result2 = bnb->getPath();
            std::cout << "Branch and bound: \n";
            std::cout << "Distance = " << result2.second << "\n";
            for(auto city : result2.first)
                std::cout << city << " ";
            std::cout << "\n";
            break;
        }
        case 0:
            endProgram = true;
            break;
        default:
            break;
        }
    }
}