#include "TabuSearch.hpp"
#include "Parser.hpp"

#include <string>
#include <iostream>

int main()
{
    TabuSearch tabuSearch;

    std::string filePath = "";

    std::cout << "File path: ";
    std::cin >> filePath;

    tabuSearch.tryToLoadFromFile(filePath);
    tabuSearch.setExecuteTime(5.0);
    tabuSearch.tabuSearch();
}