#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <graphics.h>
#include "aradix.h" // Corregir el nombre del archivo de cabecera
#include "validaciones.h" // Incluir el archivo de cabecera para validaciones
#include "Util.cpp" // Incluir el archivo de cabecera para validaciones

void drawNode(RadixTreeNode* node, int x, int y, int offset) {
    if (node == nullptr) return;

    // Draw the current node
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    fillellipse(x, y, 20, 20);
    setcolor(BLACK);
    circle(x, y, 20);
    setbkcolor(LIGHTBLUE);
    setcolor(BLACK);
    outtextxy(x - 10, y - 5, const_cast<char*>(node->prefix.c_str()));

    // Draw the children nodes
    int child_x = x - offset;
    for (auto& pair : node->children) {
        setcolor(WHITE);
        line(x, y + 20, child_x, y + 70);
        drawNode(pair.second, child_x, y + 100, offset / 2);
        child_x += offset;
    }
}

void drawTree(RadixTree& tree) {
    cleardevice();
    drawNode(tree.getRoot(), getmaxx() / 2, 50, getmaxx() / 4);
}

int main() {
    RadixTree tree;
    int option;
    std::string word;
    std::string input;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    do {
        displayMenu();
        option = Util::validarNumero(1,11);

        switch (option) {
            case 1:
                std::cout << "Ingrese la palabra a insertar: ";
                std::getline(std::cin, word);
                tree.insert(word);
                std::cout << "Palabra insertada correctamente." << std::endl;
                drawTree(tree);
                break;

            case 2:
                std::cout << "Ingrese la palabra a buscar: ";
                std::getline(std::cin, word);
                if (tree.search(word)) {
                    std::cout << "La palabra '" << word << "' esta en el arbol." << std::endl;
                } else {
                    std::cout << "La palabra '" << word << "' no esta en el arbol." << std::endl;
                }
                break;

            case 3:
                std::cout << "Ingrese la palabra a eliminar: ";
                std::getline(std::cin, word);
                tree.remove(word);
                std::cout << "Palabra eliminada correctamente." << std::endl;
                drawTree(tree);
                break;

            case 4:
                std::cout << "Recorrido Prefijo:" << std::endl;
                tree.displayPrefix();
                break;

            case 5:
                std::cout << "Recorrido Postfijo:" << std::endl;
                tree.displayPostfix();
                break;

            case 6:
                std::cout << "Recorrido Infijo:" << std::endl;
                tree.displayInfix();
                break;

            case 7:
                std::cout << "Altura del arbol: " << tree.height() << std::endl;
                break;

            case 8:
                std::cout << "Ingrese la palabra para calcular su profundidad: ";
                std::getline(std::cin, word);
                std::cout << "Profundidad de '" << word << "': " << tree.depth(word) << std::endl;
                break;

            case 9:
                std::cout << "Ingrese la palabra para calcular su nivel: ";
                std::getline(std::cin, word);
                std::cout << "Nivel de '" << word << "': " << tree.level(word) << std::endl;
                break;

            case 10:
                std::cout << "Arbol Radix:" << std::endl;
                tree.printTreeStructured();
                break;

            case 11:
                std::cout << "Saliendo del programa..." << std::endl;
                break;

            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    } while (option != 11);

    closegraph();
    return 0;
}