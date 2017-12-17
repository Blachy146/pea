#include "TabuSearch.hpp"
#include "Parser.hpp"

#include <string>
#include <iostream>
#include <memory>


void printMenu()
{
    std::cout << "------------MENU------------\n";
    std::cout << "1. Wczytaj plik\n";
    std::cout << "2. Ustaw rozmiar listy tabu\n";
    std::cout << "3. Ustaw dywersyfikację\n";
    std::cout << "4. Ustaw czas dzialania\n";
    std::cout << "5. Ustaw maksymalna liczbe iteracji bez resetowania\n";
    std::cout << "6. Ustaw kadencje\n";
    std::cout << "7. Uruchom\n"; 
    std::cout << "8. Pomiary\n"; 
    std::cout << "0. Koniec\n";
}

int getOption()
{
    int option = 0;
    std::cin >> option;

    return option;
}

int getValue()
{
    int value;
    std::cout << "Wartosc: ";
    std::cin >> value;

    return value;
}

std::string getBool()
{
    std::string value;
    std::cout << "T/N: ";
    std::cin >> value;

    return value;
}

std::string getFileName()
{
    std::string file;
    std::cout << "Plik: ";
    std::cin >> file;

    return file;
}

void makeMeasurments()
{
    auto ts = std::make_unique<TabuSearch>(); 

    std::vector<std::string> dataFileAsym {"/home/bmalecki/Downloads/br17.atsp/data",
                                           "/home/bmalecki/Downloads/ftv170.atsp/data",
                                           "/home/bmalecki/Downloads/rbg403.atsp/data"};

    std::vector<std::string> dataFileSym {"/home/bmalecki/Downloads/gr17.tsp/data",
                                           "/home/bmalecki/Downloads/pr439.tsp/data",
                                           "/home/bmalecki/Downloads/pr1002.tsp/data"};

    std::vector<double> executeTimes = {0.001, 0.01, 0.1, 1.0, };

}

int main()
{
    bool endProgram = false;
    auto ts = std::make_unique<TabuSearch>(); 

    while(!endProgram)
    {
        printMenu();
        int option = getOption();

        switch(option)
        {
        case 1:
        {
            auto file = getFileName();
            ts->tryToLoadFromFile(file);
            break;
        }
        case 2:
        {
            auto value = getValue();
            ts->setTabuSize(value);
            break;
        }
        case 3:
        {
            auto value = getBool();
            if(value == "T")
            {
                ts->setDiversification(true);
            }
            else 
            {
                ts->setDiversification(false);
            }
            break;
        }
        case 4:
        {
            double value;
            std::cout << "Wartosc: ";
            std::cin >> value;
            ts->setExecuteTime(value);
            break;
        }
        case 5:
        {
            auto value = getValue();
            ts->setDiversificationMaxCount(value);
            break;
        }
        case 6:
        {
            auto value = getValue();
            ts->setTabuTenure(value);
            break;
        }
        case 7:
        {
            ts->tabuSearch();
            break;
        }
        case 8:
        {
            makeMeasurments();
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