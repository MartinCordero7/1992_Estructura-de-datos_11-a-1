#include "hash.h"
#include <iostream>

HashInt::HashInt() {
    tabla = new Nodo*[TAMANO]();
}

HashInt::~HashInt() {
    for(int i = 0; i < TAMANO; ++i) {
        Nodo* actual = tabla[i];
        while(actual) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    delete[] tabla;
}

int HashInt::calcularHash(int clave) {
    return clave % TAMANO;
}

int HashInt::hash2(int clave) {
    return 7 - (clave % 7); // Función hash secundaria para Double Hashing
}

void HashInt::insertar(int clave, int metodo) {
    int indice = calcularHash(clave);
    int i = 0;
    while (tabla[indice] != nullptr) {
        if (metodo == 1) { // Linear Probing
            indice = (calcularHash(clave) + i) % TAMANO;
        } else if (metodo == 2) { // Quadratic Probing
            indice = (calcularHash(clave) + i * i) % TAMANO;
        } else if (metodo == 3) { // Double Hashing
            indice = (calcularHash(clave) + i * hash2(clave)) % TAMANO;
        }
        i++;
    }
    tabla[indice] = new Nodo(clave);
}

bool HashInt::buscar(int clave, int metodo) {
    int indice = calcularHash(clave);
    int i = 0;
    while (tabla[indice] != nullptr) {
        if (tabla[indice]->dato == clave) return true;
        if (metodo == 1) { // Linear Probing
            indice = (calcularHash(clave) + i) % TAMANO;
        } else if (metodo == 2) { // Quadratic Probing
            indice = (calcularHash(clave) + i * i) % TAMANO;
        } else if (metodo == 3) { // Double Hashing
            indice = (calcularHash(clave) + i * hash2(clave)) % TAMANO;
        }
        i++;
    }
    return false;
}

void HashInt::eliminar(int clave, int metodo) {
    int indice = calcularHash(clave);
    int i = 0;
    while (tabla[indice] != nullptr) {
        if (tabla[indice]->dato == clave) {
            delete tabla[indice];
            tabla[indice] = nullptr;
            return;
        }
        if (metodo == 1) { // Linear Probing
            indice = (calcularHash(clave) + i) % TAMANO;
        } else if (metodo == 2) { // Quadratic Probing
            indice = (calcularHash(clave) + i * i) % TAMANO;
        } else if (metodo == 3) { // Double Hashing
            indice = (calcularHash(clave) + i * hash2(clave)) % TAMANO;
        }
        i++;
    }
}

void HashInt::mostrar() {
    for(int i = 0; i < TAMANO; ++i) {
        std::cout << "Bucket " << i << ": ";
        if (tabla[i] != nullptr) {
            std::cout << tabla[i]->dato;
        }
        std::cout << std::endl;
    }
}

void HashInt::visualizar() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int cellSize = 60; // Square cells
    int spacing = 10;
    
    // Calculate cells per row based on screen width
    int cellsPerRow = (screenWidth - 100) / (cellSize + spacing); // Leave some margin
    int numRows = (TAMANO + cellsPerRow - 1) / cellsPerRow; // Ceiling division
    
    // Calculate total width and height of the table
    int tableWidth = (std::min(cellsPerRow, TAMANO) * (cellSize + spacing)) - spacing;
    int tableHeight = (numRows * (cellSize + spacing * 2));
    
    // Calculate margins to center the table
    int marginLeft = (screenWidth - tableWidth) / 2;
    int marginTop = (screenHeight - tableHeight) / 2;

    initwindow(screenWidth, screenHeight, "Tabla HashInt", -3, -3); // -3, -3 for fullscreen
    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    for (int i = 0; i < TAMANO; i++) {
        int row = i / cellsPerRow;
        int col = i % cellsPerRow;
        
        int x = marginLeft + col * (cellSize + spacing);
        int y = marginTop + row * (cellSize + spacing * 2);
        
        // Draw cell
        rectangle(x, y, x + cellSize, y + cellSize);
        
        // Draw index number below cell
        char indexStr[5];
        sprintf(indexStr, "[%d]", i);
        outtextxy(x + cellSize/2 - textwidth(indexStr)/2, y + cellSize + 5, indexStr);

        if (tabla[i] != nullptr) {
            char valueStr[10];
            sprintf(valueStr, "%d", tabla[i]->dato);
            
            int textWidth = textwidth(valueStr);
            int textHeight = textheight(valueStr);
            int textX = x + (cellSize - textWidth)/2;
            int textY = y + (cellSize - textHeight)/2;
            
            outtextxy(textX, textY, valueStr);
        }
    }

    getch();
    closegraph();
}