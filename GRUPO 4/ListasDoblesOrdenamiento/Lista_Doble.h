/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
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
    void Eliminar(string &id);
    void Buscar(string &id);
    void Comprobar_existencia(string &N1, string &N2, string &Ape, int count, Nodo *nodo, string &ID);
    string crearCorreo(string &N1, string &N2, string &Ape, int count, string dominio = "espe.edu.ec");
    void Mostrar() const;
    bool validarCedula(string &cedula);
    bool cedulaExistente(const string &cedula);
    void agregarCedula(const string &cedula);

    // Nuevas funciones para Mezcla Directa
    void ordenarLista(int opcionOrden);               // Ordena la lista según el criterio seleccionado
    Nodo* dividir(Nodo* cabeza);       // Divide la lista en dos mitades
    Nodo* fusionar(Nodo* izquierda, Nodo* derecha, int criterio);  // Funde dos listas
    Nodo* mezclaDirecta(Nodo* cabeza, int criterio);  // Método recursivo de Mezcla Directa

    bool guardarEnArchivo(const string& archivo);      // Guarda la lista en un archivo
    bool cargarDesdeArchivo(const string& archivo); 
    bool guardarListaOrdenada(const string& archivo, int opcionOrden);


private:
    Nodo *cabeza;
    Nodo *cola;
    set<string> cedulasIngresadas;
};
