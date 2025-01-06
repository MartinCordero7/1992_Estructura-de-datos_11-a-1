/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista doble
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include "Nodo.cpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

class Lista_Doble
{
public:
    Lista_Doble();
    ~Lista_Doble();

    void Insertar(string &N1, string &N2, string &Ape, int count, string &ID);
    void Eliminar(string &N1, string &N2, string &Ape);
    void Buscar(string &N1, string &N2, string &Ape);
    void Comprobar_existencia(string &N1, string &N2, string &Ape, int count, Nodo *nodo, string &ID);
    string crearCorreo(string &N1, string &N2, string &Ape, int count, string dominio = "espe.edu.ec");
    void Mostrar() const;
    void exportarAArchivo(const string &nombreArchivo) const;
    void importarDeArchivo(const string &nombreArchivo);
    void radixSortExterno(const string &archivoEntrada, const string &archivoSalida, int longitudCedula);
    bool validarCedula(string &cedula);
    bool cedulaExistente(const string &cedula);
    void agregarCedula(const string &cedula);

private:
    Nodo *cabeza;
    Nodo *cola;
    set<string> cedulasIngresadas;
};
