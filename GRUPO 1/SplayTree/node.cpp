/*********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNOS: Xavier Altamirano, Martin Cordero, Isaac Oña
 * FECHA CREACION: Viernes, 31 de Enero de 2025
 * FECHA MODIFICACION: Lunes, 03 de Febrero de 2025
 * Enunciado del problema: Splaytree
 * Nivel: TERCERO     NRC: 1992
 *********/
#include <iostream>
#include <iomanip>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};