#include <iostream>

#include "TabuSearch.hpp"

int main()
{
    TabuSearch tabuSearch;

    tabuSearch.readDistancesFromFile("/home/bmalecki/tsp");
    tabuSearch.printDistancesMatrix();
}