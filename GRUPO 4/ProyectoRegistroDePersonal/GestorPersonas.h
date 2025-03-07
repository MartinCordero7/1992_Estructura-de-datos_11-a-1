#ifndef GESTORPERSONAS_H
#define GESTORPERSONAS_H

#include "ListaCircularDoble.h"
#include "Empleado.h"
#include <vector>
#include <string>

class GestorPersonas {
private:
    ListaCircularDoble listaPersonas;
    void quickSort(std::vector<std::string>& cedulas, int bajo, int alto);
    int particion(std::vector<std::string>& cedulas, int bajo, int alto);
public:
    Empleado* buscarPersona();
    void imprimirPersona();
    Empleado* buscarPersona(const std::string& cedula);
    Empleado* ingresarPersona();
    //void ingresarPersona(ListaCircularDoble& lista);
    void buscarPersona(ListaCircularDoble& lista);
    void eliminarPersona(ListaCircularDoble& lista);
    void ordenamientoQuickSort();
};

#endif
