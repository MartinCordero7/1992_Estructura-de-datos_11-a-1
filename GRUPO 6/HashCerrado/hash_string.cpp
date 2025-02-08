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

int HashString::calcularHash(const std::string& clave) {
    int hash = 0;
    for(int i = clave.size() - 1; i >= 0; --i) {
        hash += static_cast<int>(clave[i]);
        if(i != 0) hash <<= 4;
    }
    return hash % TAMANO;
}

int HashString::hash2(const std::string& clave) {
    int hash = 0;
    for(char c : clave) {
        hash += static_cast<int>(c);
    }
    return 5 - (hash % 5); // Función hash secundaria para Double Hashing
}

void HashString::insertar(const std::string& clave, int metodo) {
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
    int marginLeft = 50;
    int marginTop = 50;
    int cellWidth = 120;
    int cellHeight = 15;
    int labelWidth = 50;
    int rowSpacing = 10;
    int windowWidth = marginLeft + labelWidth + 10 + (cellWidth + 10) * 4;
    int windowHeight = marginTop + TAMANO * (cellHeight + rowSpacing) + 50;

    initwindow(windowWidth, windowHeight, "Tabla HashString");

    for (int i = 0; i < TAMANO; i++) {
        int rowY = marginTop + i * (cellHeight + rowSpacing);
        rectangle(marginLeft, rowY, marginLeft + labelWidth, rowY + cellHeight);
        char bucketLabel[10];
        sprintf(bucketLabel, "%d", i);
        outtextxy(marginLeft + 15, rowY + 8, bucketLabel);

        if (tabla[i] != nullptr) {
            int cellX = marginLeft + labelWidth + 10;
            rectangle(cellX, rowY, cellX + cellWidth, rowY + cellHeight);
            char displayStr[21];
            strncpy(displayStr, tabla[i]->dato.c_str(), 20);
            displayStr[20] = '\0';
            outtextxy(cellX + 5, rowY + 8, displayStr);
        }
    }

    getch();
    closegraph();
}