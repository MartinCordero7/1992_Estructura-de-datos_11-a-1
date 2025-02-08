#include <iostream>
#include <windows.h>
#include "menu.h"
#include "BTree.h"

// Ensure mostrarMenu is declared in menu.h and defined in the corresponding .cpp file
int main() {
    try {
        // Set locale to UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        mostrarMenu();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
