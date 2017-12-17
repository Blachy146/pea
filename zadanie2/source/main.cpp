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

    std::vector<int> asymResults {39, 2755, 2465}; 
    std::vector<int> symResults {2085, 107217, 259045};
    std::vector<int> asymSizes {17, 170, 403}; 
    std::vector<int> symSizes {17, 439, 1002};
    std::vector<double> executeTimes = {0.001, 0.01, 0.1, 1.0, 10.0, 20.0};
    std::vector<bool> falseTrue {false, true};
    std::vector<double> tabuSizeMultiplies {0.1, 1.0, 3.0, 10.0};
    std::vector<double> tabuTenureMultiplies {0.1, 1.0, 3.0, 10.0};
    std::vector<double> diverCounts {10, 100, 1000};

    for(auto i = 0; i < dataFileAsym.size(); ++i)
    {
        ts->tryToLoadFromFile(dataFileAsym[i]);
        ts->setDiversificationMaxCount(asymSizes[i]*8);
        ts->setTabuTenure(asymSizes[i]*3);

        for(auto time : executeTimes)
        {
            ts->setExecuteTime(time);

            for(auto divers : falseTrue)
            {
                ts->setDiversification(divers);

                for(auto sizeMul : tabuSizeMultiplies)
                {
                    ts->setTabuSize((int)(asymSizes[i]*sizeMul));
                    std::cout << "-----------Asym--------------------------------\n";
                    std::cout << "instance: " << asymSizes[i] << " | time: " << time << " | divers: " << divers << " | tabuSize: " << (int)(asymSizes[i]*sizeMul) << "\n";
                    auto result = ts->tabuSearch();
                    double percentage = ((result - asymResults[i]) / (double)asymResults[i]) * 100.0;
                    std::cout << "Result: " << percentage << " %\n"; 
                    std::cout << "-------------------------------------------\n";
                }
            }
        }
    }
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