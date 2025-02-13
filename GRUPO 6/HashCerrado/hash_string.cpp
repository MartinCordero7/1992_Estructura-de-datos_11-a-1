#include "hash.h"
#include <iostream>

HashString::HashString() {
    tabla = new Nodo*[TAMANO]();
}

HashString::~HashString() {
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

// Nueva función para calcular el número entero basado en la clave
int HashString::calcularNumeroClave(const std::string& clave) {
    int hash = 0;
    for (int i = clave.size() - 1; i >= 0; --i) {
        hash += static_cast<int>(clave[i]);
        if (i != 0) hash <<= 4; // Desplazamiento de 4 bits a la izquierda
    }
    return hash;
}

int HashString::calcularHash(const std::string& clave) {
    return calcularNumeroClave(clave) % TAMANO;
}

int HashString::hash2(const std::string& clave) {
    int numeroClave = calcularNumeroClave(clave); // Ahora se calcula dinámicamente
    return 7 - (numeroClave % 7);
}

void HashString::insertar(const std::string& clave, int metodo) {
    for (char c : clave) {
        if (isdigit(c)) {
            std::cout << "Error: La cadena no debe contener números." << std::endl;
            return;
        }
    }
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

bool HashString::buscar(const std::string& clave, int metodo) {
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

void HashString::eliminar(const std::string& clave, int metodo) {
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

void HashString::mostrar() {
    for(int i = 0; i < TAMANO; ++i) {
        std::cout << "Bucket " << i << ": ";
        if (tabla[i] != nullptr) {
            std::cout << tabla[i]->dato;
        }
        std::cout << std::endl;
    }
}

void HashString::visualizar() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int cellWidth = 120;
    int cellHeight = 40;
    int spacing = 10;
    
    // Calculate cells per row based on screen width
    int cellsPerRow = (screenWidth - 100) / (cellWidth + spacing); // Leave some margin
    int numRows = (TAMANO + cellsPerRow - 1) / cellsPerRow; // Ceiling division
    
    // Calculate total width and height of the table
    int tableWidth = (std::min(cellsPerRow, TAMANO) * (cellWidth + spacing)) - spacing;
    int tableHeight = (numRows * (cellHeight + spacing * 2));
    
    // Calculate margins to center the table
    int marginLeft = (screenWidth - tableWidth) / 2;
    int marginTop = (screenHeight - tableHeight) / 2;

    initwindow(screenWidth, screenHeight, "Tabla HashString", -3, -3); // -3, -3 for fullscreen
    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    for (int i = 0; i < TAMANO; i++) {
        int row = i / cellsPerRow;
        int col = i % cellsPerRow;
        
        int x = marginLeft + col * (cellWidth + spacing);
        int y = marginTop + row * (cellHeight + spacing * 2);
        
        // Draw cell
        rectangle(x, y, x + cellWidth, y + cellHeight);
        
        // Draw index number below cell
        char indexStr[5];
        sprintf(indexStr, "[%d]", i);
        outtextxy(x + cellWidth/2 - textwidth(indexStr)/2, y + cellHeight + 5, indexStr);

        if (tabla[i] != nullptr) {
            char displayStr[21];
            strncpy(displayStr, tabla[i]->dato.c_str(), 20);
            displayStr[20] = '\0';
            
            int textWidth = textwidth(displayStr);
            int textHeight = textheight(displayStr);
            int textX = x + (cellWidth - textWidth)/2;
            int textY = y + (cellHeight - textHeight)/2;
            
            outtextxy(textX, textY, displayStr);
        }
    }

    getch();
    closegraph();
}