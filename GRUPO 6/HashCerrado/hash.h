#ifndef HASH_H
#define HASH_H

#include <string>
#include <graphics.h> // Incluir graphics.h

class HashString {
private:
    static const int TAMANO = 29;
    struct Nodo {
        std::string dato;
        Nodo* siguiente;
        Nodo(std::string d) : dato(d), siguiente(nullptr) {}
    };
    Nodo** tabla;

    int calcularHash(const std::string& clave);
    int hash2(const std::string& clave); // Función hash secundaria para Double Hashing

public:
    HashString();
    ~HashString();
    void insertar(const std::string& clave, int metodo);
    bool buscar(const std::string& clave, int metodo);
    void eliminar(const std::string& clave, int metodo);
    void mostrar();
    void visualizar(); // Nuevo método
};

class HashInt {
private:
    static const int TAMANO = 29;
    struct Nodo {
        int dato;
        Nodo* siguiente;
        Nodo(int d) : dato(d), siguiente(nullptr) {}
    };
    Nodo** tabla;

    int calcularHash(int clave);
    int hash2(int clave); // Función hash secundaria para Double Hashing

public:
    HashInt();
    ~HashInt();
    void insertar(int clave, int metodo);
    bool buscar(int clave, int metodo);
    void eliminar(int clave, int metodo);
    void mostrar();
    void visualizar(); // Nuevo método
};

#endif