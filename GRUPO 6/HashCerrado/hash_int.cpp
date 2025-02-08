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
    int marginLeft = 50;
    int marginTop = 50;
    int cellWidth = 70;
    int cellHeight = 30;
    int labelWidth = 50;
    int rowSpacing = 10;
    int windowWidth = marginLeft + labelWidth + 10 + (cellWidth + 10) * 4;
    int windowHeight = marginTop + TAMANO * (cellHeight + rowSpacing) + 50;

    initwindow(windowWidth, windowHeight, "Tabla HashInt");

    for (int i = 0; i < TAMANO; i++) {
        int rowY = marginTop + i * (cellHeight + rowSpacing);
        rectangle(marginLeft, rowY, marginLeft + labelWidth, rowY + cellHeight);
        char bucketLabel[10];
        sprintf(bucketLabel, "%d", i);
        outtextxy(marginLeft + 15, rowY + 8, bucketLabel);

        if (tabla[i] != nullptr) {
            int cellX = marginLeft + labelWidth + 10;
            rectangle(cellX, rowY, cellX + cellWidth, rowY + cellHeight);
            char datoStr[10];
            sprintf(datoStr, "%d", tabla[i]->dato);
            outtextxy(cellX + 5, rowY + 8, datoStr);
        }
    }

    getch();
    closegraph();
}