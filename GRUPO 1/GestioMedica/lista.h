#ifndef LISTA_H
#define LISTA_H

#include <string>

class Nodo {
public:
    std::string texto;
    int id;
    Nodo* siguiente;
    Nodo* anterior;
    
    Nodo(std::string texto, int id);
};

class Lista {
private:
    Nodo* actual;
    int size;

public:
    Lista();
    ~Lista();
    
    void insertarOpcion(std::string texto, int id);
    void siguiente();
    void anterior();
    Nodo* getActual() const;
    bool estaVacia() const;
    void limpiar();
    int getSize() const;
};

#endif // LISTA_H
