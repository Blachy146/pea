#include "GeneticTSP.hpp"

#include <iostream>
#include <memory>

void printMenu()
{
    std::cout << "------------MENU------------\n";
    std::cout << "1. Wczytaj plik\n";
    std::cout << "2. Ustaw rozmiar populacji\n";
    std::cout << "3. Ustaw rodzaj mutacji\n";
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

void makeMeasurments()
{
    auto genetic = std::make_unique<GeneticTSP>(); 

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
    std::vector<double> executeTimes {1.0, 10.0, 20.0, 40.0, 60.0};
    std::vector<double> populationSizesMul {0.5, 1, 2};
    std::vector<double> survivalRates {0.25};
    std::vector<int> mutationTypes {1, 2};
    double mutationRate = 0.01;
    double crossoverRate = 0.8;

    genetic->setMutationRate(mutationRate);
    genetic->setCrossoverRate(crossoverRate);

    std::cout << "Number of cities" << ";" << "Time" << ";" << "Error" << ";" << "Population size" << ";" << "Mutation type" << ";" << "Mutation rate" << ";" << "Crossover rate" << ";" << "Survival rate" << ";" << "\n";

    for(auto i = 0; i < dataFileAsym.size(); ++i)
    {
        genetic->tryToLoadFromFile(dataFileAsym[i]);

        for(auto time : executeTimes)
        {
            genetic->setCalculationTime(time);

            for(auto populationSizeMul : populationSizesMul)
            {
                auto populationSize = static_cast<int>(populationSizeMul * asymSizes[i]);
                if(populationSize % 2 != 0) ++populationSize;
                genetic->setPupulationSize(populationSize);

                for(auto survivalRate : survivalRates)
                {
                    genetic->setSurvivalRate(survivalRate);

                    for(auto mutationType : mutationTypes)
                    {
                        if(mutationType == 1)
                            genetic->setMutationType(MutationType::Inversion);
                        else
                            genetic->setMutationType(MutationType::Transposition);

                        auto result = genetic->geneticAlgorithm();
                        double percentage = ((result - asymResults[i]) / (double)asymResults[i]) * 100.0;
                        std::cout << asymSizes[i] << ";" << time << ";" << percentage << ";" << populationSize << ";" << mutationType << ";" << mutationRate << ";" << crossoverRate << ";" << survivalRate << ";" << "\n"; 
                    }
                }
            }
        }
    }

    genetic = std::make_unique<GeneticTSP>(); 
    genetic->setMutationRate(mutationRate);
    genetic->setCrossoverRate(crossoverRate);

    std::cout << "Number of cities" << ";" << "Time" << ";" << "Error" << ";" << "Population size" << ";" << "Mutation type" << ";" << "Mutation rate" << ";" << "Crossover rate" << ";" << "Survival rate" << ";" << "\n";

    for(auto i = 0; i < dataFileSym.size(); ++i)
    {
        genetic->tryToLoadFromFile(dataFileSym[i]);

        for(auto time : executeTimes)
        {
            genetic->setCalculationTime(time);

            for(auto populationSizeMul : populationSizesMul)
            {
                auto populationSize = static_cast<int>(populationSizeMul * symSizes[i]);
                if(populationSize % 2 != 0) ++populationSize;
                genetic->setPupulationSize(populationSize);

                for(auto survivalRate : survivalRates)
                {
                    genetic->setSurvivalRate(survivalRate);

                    for(auto mutationType : mutationTypes)
                    {
                        if(mutationType == 1)
                            genetic->setMutationType(MutationType::Inversion);
                        else
                            genetic->setMutationType(MutationType::Transposition);

                        auto result = genetic->geneticAlgorithm();
                        double percentage = ((result - symResults[i]) / (double)symResults[i]) * 100.0;
                        std::cout << symSizes[i] << ";" << time << ";" << percentage << ";" << populationSize << ";" << mutationType << ";" << mutationRate << ";" << crossoverRate << ";" << survivalRate << ";" << "\n"; 
                    }
                }
            }
        }
    }
}

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
            makeMeasurments();
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

    //makeMeasurments();
}
