/****
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Viernes,  7 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: Hashing
 * Nivel: TERCERO     NRC: 1992
 *****/
#ifndef HASH_H
#define HASH_H

#include <string>
#include <graphics.h> // Incluir graphics.h

class HashString {
private:
    static const int TAMANO = 13;
    struct Nodo {
        std::string dato;
        Nodo* siguiente;
        Nodo(std::string d) : dato(d), siguiente(nullptr) {}
    };
    Nodo** tabla;

    int calcularHash(const std::string& clave);

public:
    HashString();
    ~HashString();
    void insertar(const std::string& clave);
    bool buscar(const std::string& clave);
    void eliminar(const std::string& clave);
    void mostrar();
    void visualizar(); // Nuevo método
};

class HashInt {
private:
    static const int TAMANO = 13;
    struct Nodo {
        int dato;
        Nodo* siguiente;
        Nodo(int d) : dato(d), siguiente(nullptr) {}
    };
    Nodo** tabla;

    int calcularHash(int clave);

public:
    HashInt();
    ~HashInt();
    void insertar(int clave);
    bool buscar(int clave);
    void eliminar(int clave);
    void mostrar();
    void visualizar(); // Nuevo método
};

#endif