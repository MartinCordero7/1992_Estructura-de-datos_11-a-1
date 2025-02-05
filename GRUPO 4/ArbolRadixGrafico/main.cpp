#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <graphics.h>
#include "aradix.h"
#include "Validaciones.cpp"
#include "Util.cpp" 

// Function to read the size of the graphics card and get the screen size
void getScreenSize(int& width, int& height) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    width = getmaxx();
    height = getmaxy();
    closegraph();
}

// Function to change the font size
void setFontSize(int size) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, size);
}

// Function to draw a line by positioning points
void drawLine(int x1, int y1, int x2, int y2) {
    setcolor(WHITE);
    line(x1, y1, x2, y2);
}

void drawNode(RadixTreeNode* node, int x, int y, int offset) {
    if (node == nullptr) return;

    // Draw the current node
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x, y, 20, 20);
    setcolor(WHITE);
    circle(x, y, 20);
    setbkcolor(BLACK);
    setcolor(WHITE);
    outtextxy(x - 10, y - 5, const_cast<char*>(node->prefix.c_str()));

    // Draw the children nodes
    int child_x = x - offset;
    for (auto& pair : node->children) {
        setcolor(WHITE);
        line(x, y + 20, child_x, y + 70);
        line(child_x, y + 70, child_x - 5, y + 65); // Arrow part 1
        line(child_x, y + 70, child_x + 5, y + 65); // Arrow part 2
        drawNode(pair.second, child_x, y + 100, offset / 2);
        child_x += offset;
    }
}

void drawTree(RadixTree& tree) {
    cleardevice();
    drawNode(tree.getRoot(), getmaxx() / 2, 50, getmaxx() / 4);
}

void getInput(char* input) {
    int i = 0;
    char ch;
    int input_x = 10;
    int input_y = getmaxy() - 20; // Adjusted position further up
    while (true) {
        ch = getch();
        if (ch == 13) { // Enter key
            input[i] = '\0';
            return;
        }
        if (ch == 8) { // Backspace key
            if (i > 0) {
                i--;
                setcolor(BLACK);
                outtextxy(input_x + i * 10, input_y, const_cast<char*>(" ")); // Clear the character
                setcolor(WHITE);
            }
        } else {
            input[i++] = ch;
            char str[2] = {ch, '\0'};
            outtextxy(input_x + (i - 1) * 10, input_y, str);
        }
    }
}

int getOption() {
    char optionInput[10];
    getInput(optionInput);
    try {
        return std::stoi(optionInput);
    } catch (const std::invalid_argument&) {
        return -1; // Invalid option
    }
}

int main() {
    RadixTree tree;
    int option;
    std::string word;
    std::string input;

    int width = 1024;
    int height = 768;
    initwindow(width, height);

    setbkcolor(BLACK);
    cleardevice();

    do {
        drawTree(tree);
        setcolor(WHITE);
        outtextxy(10, getmaxy() - 150, const_cast<char*>("1. Insertar palabra"));
        outtextxy(10, getmaxy() - 130, const_cast<char*>("2. Eliminar palabra"));
        outtextxy(10, getmaxy() - 110, const_cast<char*>("3. Salir"));
        outtextxy(10, getmaxy() - 90, const_cast<char*>("4. Cambiar tamaño de letra"));
        outtextxy(10, getmaxy() - 70, const_cast<char*>("5. Dibujar línea"));
        outtextxy(10, getmaxy() - 50, const_cast<char*>("Ingrese su opcion: "));
        
        option = getOption();

        int fontSize;
        char fontSizeInput[10];
        char lineInput[50];
        int x1, y1, x2, y2;

        switch (option) {
            case 1:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Ingrese la palabra a insertar: "));
                char insertWord[100];
                getInput(insertWord);
                word = insertWord;
                if (Validaciones::validarPalabra(word)) {
                    tree.insert(word);
                    outtextxy(10, getmaxy() - 30, const_cast<char*>("Palabra insertada correctamente."));
                } else {
                    outtextxy(10, getmaxy() - 30, const_cast<char*>("Palabra no válida."));
                }
                break;

            case 2:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Ingrese la palabra a eliminar: "));
                char deleteWord[100];
                getInput(deleteWord);
                word = deleteWord;
                if (Validaciones::validarPalabra(word)) {
                    tree.remove(word);
                    outtextxy(10, getmaxy() - 30, const_cast<char*>("Palabra eliminada correctamente."));
                } else {
                    outtextxy(10, getmaxy() - 30, const_cast<char*>("Palabra no válida."));
                }
                break;

            case 3:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Saliendo del programa..."));
                break;

            case 4:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Ingrese el tamaño de letra: "));
                getInput(fontSizeInput);
                fontSize = std::stoi(fontSizeInput);
                setFontSize(fontSize);
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Tamaño de letra cambiado."));
                break;

            case 5:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Ingrese las coordenadas x1, y1, x2, y2: "));
                getInput(lineInput);
                sscanf(lineInput, "%d %d %d %d", &x1, &y1, &x2, &y2);
                drawLine(x1, y1, x2, y2);
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Línea dibujada."));
                break;

            default:
                outtextxy(10, getmaxy() - 30, const_cast<char*>("Opción no válida. Intente de nuevo."));
                break;
        }

        // Wait for Enter key to continue
        while (getch() != 13) {
            // Do nothing, just wait for Enter key
        }

    } while (option != 3);

    closegraph();
    
    return 0;
}