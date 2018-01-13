#include "GeneticTSP.hpp"

#include <iostream>
#include <memory>

void printMenu()
{
    std::cout << "------------MENU------------\n";
    std::cout << "1. Wczytaj plik\n";
    std::cout << "2. Ustaw rozmiar populacji\n";
    std::cout << "3. Ustaw rodzaj muracji\n";
    std::cout << "4. Ustaw czas dzialania\n";
    std::cout << "5. Ustaw odsetek mutacji\n";
    std::cout << "6. Ustaw odsetek krzyzowan\n";
    std::cout << "7. Ustaw odsetek przezywalnosci\n";
    std::cout << "8. Uruchom\n"; 
    std::cout << "9. Pomiary\n"; 
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

std::string getFileName()
{
    std::string file;
    std::cout << "Plik: ";
    std::cin >> file;

    return file;
}

/*
void makeMeasurments()
{
    auto genetic = std::make_unique<GeneticTSP>(); 

    std::vector<std::string> dataFileAsym {"/home/bmalecki/Downloads/ftv170.atsp/data"};

    std::vector<std::string> dataFileSym {"/home/bmalecki/Downloads/pr439.tsp/data"};

    std::vector<int> asymResults {2755}; 
    std::vector<int> symResults {107217};
    std::vector<int> asymSizes {170}; 
    std::vector<int> symSizes {439};
    std::vector<double> executeTimes = {0.001, 0.01, 0.1, 1.0, 10.0, 20.0, 40.0, 60.0};

    for(auto i = 0; i < dataFileAsym.size(); ++i)
    {
        genetic->tryToLoadFromFile(dataFileAsym[i]);

        for(auto time : executeTimes)
        {
            genetic->setExecuteTime(time);

            for(auto divers : falseTrue)
            {
                genetic->setDiversification(divers);

                auto result = genetic->tabuSearch();
                double percentage = ((result - asymResults[i]) / (double)asymResults[i]) * 100.0;
                std::cout << "Number of cities" << ";" << "Time" << ";" << "Error" << ";" << "Diversification" << ";" << "\n";
                std::cout << asymSizes[i] << ";" << time << ";" << percentage << ";" << divers << ";" << "\n"; 
            }
        }
    }

    genetic = std::make_unique<GeneticTSP>(); 

    for(auto i = 0; i < dataFileSym.size(); ++i)
    {
        genetic->tryToLoadFromFile(dataFileSym[i]);
        genetic->setDiversificationMaxCount(symSizes[i]*8);
        genetic->setTabuTenure((int)(symSizes[i]*3));
        genetic->setTabuSize((int)(symSizes[i]*3));

        for(auto time : executeTimes)
        {
            genetic->setExecuteTime(time);

            for(auto divers : falseTrue)
            {
                genetic->setDiversification(divers);

                auto result = genetic->tabuSearch();
                double percentage = ((result - symResults[i]) / (double)symResults[i]) * 100.0;
                std::cout << "Number of cities" << ";" << "Time" << ";" << "Error" << ";" << "Diversification" << ";" << "\n";
                std::cout << symSizes[i] << ";" << time << ";" << percentage << ";" << divers << ";" << "\n"; 
            }
        }
    }
}
*/

int main()
{
    bool endProgram = false;
    auto genetic = std::make_unique<GeneticTSP>(); 

    while(!endProgram)
    {
        printMenu();
        int option = getOption();

        switch(option)
        {
        case 1:
        {
            auto file = getFileName();
            genetic->tryToLoadFromFile(file);
            break;
        }
        case 2:
        {
            auto value = getValue();
            genetic->setPupulationSize(value);
            break;
        }
        case 3:
        {
            std::cout << "1 - Inversion, 2 - Transposition\n";
            auto value = getValue();
            if(value == 1) 
            {
                genetic->setMutationType(MutationType::Inversion);
            }
            if(value == 2) 
            {
                genetic->setMutationType(MutationType::Transposition);
            }
            break;
        }
        case 4:
        {
            double value;
            std::cout << "Wartosc: ";
            std::cin >> value;
            genetic->setCalculationTime(value);
            break;
        }
        case 5:
        {
            double value;
            std::cout << "Wartosc: ";
            std::cin >> value;
            genetic->setMutationRate(value);
            break;
        }
        case 6:
        {
            double value;
            std::cout << "Wartosc: ";
            std::cin >> value;
            genetic->setCrossoverRate(value);
            break;
        }
        case 7:
        {
            double value;
            std::cout << "Wartosc: ";
            std::cin >> value;
            genetic->setSurvivalRate(value);
            break;
        }
        case 8:
        {
            genetic->geneticAlgorithm();
            break;
        }
        case 9:
        {
            //makeMeasurments();
            endProgram = true;
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

/*
int main()
{
    auto genetic = std::make_unique<GeneticTSP>();

    genetic->tryToLoadFromFile("/home/bmalecki/Downloads/pr152.tsp/data");
    genetic->setPupulationSize(20);
    genetic->setMutationRate(0.31);
    genetic->setCrossoverRate(0.9);
    genetic->setSurvivalRate(0.2);
    genetic->setCalculationTime(60.0);
    genetic->setMutationType(MutationType::Inversion);
    genetic->geneticAlgorithm();
}
*/