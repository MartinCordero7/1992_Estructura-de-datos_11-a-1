#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <string>
#include <iostream>

struct NodoAVL {
    std::string cedula;
    std::string nombre;
    std::string tipo; // "paciente" o "doctor"
    std::string especialidad; // solo para doctores
    int altura;
    NodoAVL* izquierdo;
    NodoAVL* derecho;

    NodoAVL(std::string ced, std::string nom, std::string t, std::string esp = "") : 
        cedula(ced), nombre(nom), tipo(t), especialidad(esp), 
        altura(1), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolAVL {
private:
    NodoAVL* raiz;

    int obtenerAltura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* insertarNodo(NodoAVL* nodo, std::string cedula, std::string nombre, std::string tipo, std::string especialidad);
    NodoAVL* buscarNodo(NodoAVL* nodo, std::string cedula);
    void inordenRec(NodoAVL* nodo);

public:
    ArbolAVL() : raiz(nullptr) {}
    void insertar(std::string cedula, std::string nombre, std::string tipo, std::string especialidad = "");
    bool buscar(std::string cedula, std::string& nombre, std::string& tipo, std::string& especialidad);
    void inorden();
    void cargarDatos();
};

#endif
