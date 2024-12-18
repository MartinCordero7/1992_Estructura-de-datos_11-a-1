
#include "ListaDoble.hpp"
#include "Sort.hpp"
#include <iostream>

int main()
{
    std::cout << "Lista Simple: " << std::endl;
    ListaDoble<int> listaS = { 16, 7, 2, 8, 29, 4, 12, 18, 3, 7, 18 };
    listaS.mostrar();
    std::cout << std::endl;
    Sort::bubbleSort(listaS);
    listaS.mostrar();
    std::cout << std::endl << std::endl;

    std::cout << "Lista Doble: " << std::endl;
    ListaDoble<int> listaD = { 16, 7, 2, 8, 29, 4, 12, 18, 3, 7, 18 };
    listaD.mostrar();
    std::cout << std::endl;
    Sort::bubbleSort(listaD);
    listaD.mostrar();
    std::cout << std::endl;
    return 0;
}