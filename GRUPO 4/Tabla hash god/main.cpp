#include <iostream>
#include <list>
#include <vector>
#include <graphics.h>
#include "HashTable.h"

int main() {
    int tableSize;
    std::cout << "Ingresa el tamanio de la tabla hash: ";
    while (!(std::cin >> tableSize) || tableSize <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor no valido. Ingresa un numero entero positivo: ";
    }

    HashTable<int> htInt(tableSize);
    HashTable<std::string> htString(tableSize);
    menu(htInt, htString);

    return 0;
}
