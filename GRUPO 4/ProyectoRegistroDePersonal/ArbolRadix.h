#ifndef ARBOLRADIX_H
#define ARBOLRADIX_H

#include "Empleado.h"
#include <unordered_map>
#include <string>
#include <fstream>

class ArbolRadix
{
public:
    struct Nodo
    {
        std::unordered_map<char, Nodo *> hijos;
        Empleado *empleado;

        Nodo() : empleado(nullptr) {}
    };

    ArbolRadix();
    ~ArbolRadix();

    void insertarEmpleado(Empleado *empleado);
    Empleado *buscarPorCedula(const std::string &cedula);
    void imprimirArbol() const;
    void graficarArbol(const std::string &filename) const;

    Nodo *getRaiz() const;
    void buscarYMostrarEmpleadoPorCedula();
    std::string validarExistenciaCedula(const std::string &cedula);

    Nodo *raiz;
    void destruirRecursivo(Nodo *nodo);
    void imprimirArbolRecursivo(Nodo *nodo, std::string prefijo) const;
    void graficarArbolRecursivo(Nodo *nodo, std::ofstream &archivo, int &contador) const;
};

#endif /* ARBOLRADIX_H */
