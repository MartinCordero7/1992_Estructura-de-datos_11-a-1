/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Hash abierto en modo grafico                             *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/05/2025                                               *
 * Fecha de modificacion:          03/05/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
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
        if(i != 0) hash <<= 4; // Desplazamiento de 4 bits
    }
    return hash % TAMANO;
}

void HashString::insertar(const std::string& clave) {
    int indice = calcularHash(clave);
    Nodo* nuevo = new Nodo(clave);
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
}

bool HashString::buscar(const std::string& clave) {
    int indice = calcularHash(clave);
    Nodo* actual = tabla[indice];
    while(actual) {
        if(actual->dato == clave) return true;
        actual = actual->siguiente;
    }
    return false;
}

void HashString::eliminar(const std::string& clave) {
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

void HashString::mostrar() {
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

// Implementación para HashString::visualizar() (versión tabla completa)
void HashString::visualizar() {
    // Parámetros de la tabla
    int marginLeft = 50;      // margen izquierdo
    int marginTop = 50;       // margen superior
    int cellWidth = 120;      // ancho de cada celda para los elementos
    int cellHeight = 30;      // alto de cada celda
    int labelWidth = 50;      // ancho de la celda de la etiqueta (bucket)
    int rowSpacing = 10;      // espacio vertical entre filas

    // Calcular dimensiones necesarias para la ventana
    int windowWidth = marginLeft + labelWidth + 10 + (cellWidth + 10) * 4; // se asume que en cada bucket habrá hasta 4 elementos (ajusta según tus necesidades)
    int windowHeight = marginTop + TAMANO * (cellHeight + rowSpacing) + 50;  // 50 píxeles extra en la parte inferior

    // Inicializar la ventana con las dimensiones calculadas
    initwindow(windowWidth, windowHeight, "Tabla HashString");

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

            // Preparar y dibujar el texto (limitamos a 20 caracteres)
            char displayStr[21];
            strncpy(displayStr, actual->dato.c_str(), 20);
            displayStr[20] = '\0';
            outtextxy(cellX + 5, rowY + 8, displayStr);

            // Moverse a la siguiente celda (separación de 10 píxeles entre celdas)
            cellX += cellWidth + 10;
            actual = actual->siguiente;
        }
    }

    getch();
    closegraph();
}
