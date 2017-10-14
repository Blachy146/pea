#include <salesman.h>

#include <iostream>

int main()
{
    TravellingSalesman salesman{"/some/file"};

    std::cout << "salesman.getPath() = " << salesman.getPath() << "\n";
}