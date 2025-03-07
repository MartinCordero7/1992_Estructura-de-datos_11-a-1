/****
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Viernes,  7 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: Hashing
 * Nivel: TERCERO     NRC: 1992
 *****/
#include "hash.h"
#include <iostream>
#include <sstream>
#include <cstring>

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

void HashInt::insertar(int clave) {
    int indice = calcularHash(clave);
    Nodo* nuevo = new Nodo(clave);
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
}

bool HashInt::buscar(int clave) {
    int indice = calcularHash(clave);
    Nodo* actual = tabla[indice];
    while(actual) {
        if(actual->dato == clave) return true;
        actual = actual->siguiente;
    }
    return false;
}

void HashInt::eliminar(int clave) {
    int indice = calcularHash(clave);
    Nodo* actual = tabla[indice];
    Nodo* previo = nullptr;
    while(actual) {
        if(actual->dato == clave) {
            if(previo) previo->siguiente = actual->siguiente;
            else tabla[indice] = actual->siguiente;
            delete actual;
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }
}

void HashInt::mostrar() {
    for(int i = 0; i < TAMANO; ++i) {
        std::cout << "Bucket " << i << ": ";
        Nodo* actual = tabla[i];
        while(actual) {
            std::cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        std::cout << "null" << std::endl;
    }
}

// Implementación para HashInt::visualizar() (versión tabla completa)
void HashInt::visualizar() {
    // Parámetros de la tabla
    int marginLeft = 50;      // margen izquierdo
    int marginTop = 50;       // margen superior
    int cellWidth = 70;       // ancho de cada celda para los elementos
    int cellHeight = 30;      // alto de cada celda
    int labelWidth = 50;      // ancho de la celda de la etiqueta (bucket)
    int rowSpacing = 10;      // espacio vertical entre filas

    // Calcular dimensiones necesarias para la ventana
    int windowWidth = marginLeft + labelWidth + 10 + (cellWidth + 10) * 4; // se asume hasta 4 elementos por bucket
    int windowHeight = marginTop + TAMANO * (cellHeight + rowSpacing) + 50;  // 50 píxeles extra en la parte inferior

    // Inicializar la ventana con las dimensiones calculadas
    initwindow(windowWidth, windowHeight, "Tabla HashInt");

    // Dibujar cada fila (bucket)
    for (int i = 0; i < TAMANO; i++) {
        // Coordenada Y de la fila actual
        int rowY = marginTop + i * (cellHeight + rowSpacing);
        
        // Dibujar el recuadro de la etiqueta del bucket
        rectangle(marginLeft, rowY, marginLeft + labelWidth, rowY + cellHeight);
        char bucketLabel[10];
        sprintf(bucketLabel, "%d", i);
        outtextxy(marginLeft + 15, rowY + 8, bucketLabel);

        // Dibujar los elementos del bucket en celdas
        Nodo* actual = tabla[i];
        int cellX = marginLeft + labelWidth + 10; // espacio entre la etiqueta y la primera celda
        while (actual != nullptr) {
            // Dibujar el recuadro de la celda
            rectangle(cellX, rowY, cellX + cellWidth, rowY + cellHeight);

            // Dibujar el dato en la celda
            char datoStr[10];
            sprintf(datoStr, "%d", actual->dato);
            outtextxy(cellX + 5, rowY + 8, datoStr);

            // Moverse a la siguiente celda
            cellX += cellWidth + 10;
            actual = actual->siguiente;
        }
    }

    getch();
    closegraph();
}

