#include "TabuSearch.hpp"

#include <iostream>


int main()
{
    TabuSearch tabuSearch;
    tabuSearch.loadFromFile("/home/bmalecki/Downloads/atsp");
    std::cout << "----------Matrix----------\n";
    tabuSearch.printDistancesMatrix();
    tabuSearch.loadFromFile("/home/bmalecki/Downloads/tsp");
    std::cout << "----------Lower diagonal----------\n";
    tabuSearch.printDistancesMatrix();
}