/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/

#include "Lista_Doble.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

Lista_Doble::Lista_Doble() : cabeza(nullptr), cola(nullptr) {}

Lista_Doble::~Lista_Doble()
{
    while (cabeza != nullptr)
    {
        Nodo *temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}

void Lista_Doble::Insertar(string &N1, string &N2, string &Ape, int count, string &ID)
{
    Nodo *nuevoNodo = new Nodo(N1, N2, Ape, ID);
    if (cabeza == nullptr)
    {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    }
    else
    {
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(cola);
        cola = nuevoNodo;
    }
    Comprobar_existencia(N1, N2, Ape, count, nuevoNodo, ID);
}
bool Lista_Doble::validarCedula(string &cedula)
{
    if (cedula.length() != 10)
    {
        return false;
    }

    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            cout << "Ingrese solo numeros";
            return false;
        }
    }

    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int digito = cedula[i] - '0';
        if (i % 2 == 0)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9;
            }
        }
        suma += digito;
    }

    int digitoVerificador = cedula[9] - '0';
    int resultado = 10 - (suma % 10);
    if (resultado == 10)
    {
        resultado = 0;
    }

    return digitoVerificador == resultado;
}

void Lista_Doble::Comprobar_existencia(string &N1, string &N2, string &Ape, int count, Nodo *nodo, string &ID)
{
    count = -1;
    Nodo *actual = cabeza;

    while (actual != nullptr)
    {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape)
        {
            count++;
        }
        actual = actual->getSiguiente();
    }
    if (cedulaExistente(ID))
    {
        cout << "La cédula ya ha sido ingresada anteriormente." << endl;
        cin >> ID;
    }
    else
    {

        agregarCedula(ID);
    }

    string correo = crearCorreo(N1, N2, Ape, count, "espe.edu.ec");
    nodo->setCorreo(correo);
}
bool Lista_Doble::cedulaExistente(const string &cedula)
{
    return cedulasIngresadas.find(cedula) != cedulasIngresadas.end();
}

void Lista_Doble::agregarCedula(const string &cedula)
{
    cedulasIngresadas.insert(cedula);
}
string Lista_Doble::crearCorreo(string &N1, string &N2, string &Ape, int count, string dominio)
{
    if (N1.empty() || N2.empty() || Ape.empty())
    {
        std::cerr << "Error: Los nombres y el apellido no deben estar vacíos" << std::endl;
    }

    char inicialN1 = tolower(N1[0]);
    char inicialN2 = tolower(N2[0]);

    std::string apellidoMinusculas = Ape;
    transform(apellidoMinusculas.begin(), apellidoMinusculas.end(), apellidoMinusculas.begin(), ::tolower);
    std::string correo;
    if (count <= 0)
    {
        correo = std::string(1, inicialN1) + std::string(1, inicialN2) + apellidoMinusculas + "@" + dominio;
    }
    else
    {
        correo = std::string(1, inicialN1) + std::string(1, inicialN2) + apellidoMinusculas + std::to_string(count) + "@" + dominio;
    }

    return correo;
}
char *ingresarLetras(const char *msj)
{
    static char dato[25];
    char c;
    int i = 0;
    cout << msj << ": ";

    while ((c = _getch()) != 13)
    {
        if (isalpha(c))
        {
            dato[i++] = c;
            cout << c;
        }
    }

    dato[i] = '\0';
    cout << endl;
    return dato;
}
char *ingresarNumeros(const char *msj)
{
    static char dato[25];
    char c;
    int i = 0;
    cout << msj << ": ";
    while ((c = _getch()) != 13)
    {
        if (c >= '0' && c <= '9')
        {
            dato[i++] = c;
            cout << c;
        }
    }
    dato[i] = '\0';
    cout << endl;
    return dato;
}
string cifradoCesar(const string &texto, int desplazamiento)
{
    string resultado = texto;

    for (char &c : resultado)
    {
        if (isalpha(c))
        {
            char limite = isupper(c) ? 'A' : 'a';
            int nuevaPosicion = c - limite + desplazamiento;

            if (nuevaPosicion >= 26)
            {
                nuevaPosicion -= 26;
            }
            else if (nuevaPosicion < 0)
            {
                nuevaPosicion += 26;
            }

            c = limite + nuevaPosicion;
        }
    }

    return resultado;
}

void Lista_Doble::Eliminar(string &id)
{
    Nodo *actual = cabeza;
    Nodo *anterior = nullptr;

    while (actual != nullptr)
    {
        if (actual->getCedula() == id)  // Compara la cédula
        {
            // Nodo encontrado, procedemos a eliminar
            if (actual == cabeza) {
                cabeza = actual->getSiguiente();
                if (cabeza != nullptr) {
                    cabeza->setAnterior(nullptr);
                }
            } else if (actual == cola) {
                cola = anterior;
                if (cola != nullptr) {
                    cola->setSiguiente(nullptr);
                }
            } else {
                anterior->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(anterior);
            }
            
            delete actual;
            cout << "Persona con cedula " << id << " eliminada correctamente......" << endl;
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    
    cout << "Persona con cedula " << id << " no encontrada......" << endl;
}

void Lista_Doble ::Buscar(string &id)
{
    Nodo *actual = cabeza;  // Se asume que 'cabeza' es el puntero al primer nodo de la lista
    while (actual != nullptr)
    {
        if (actual->getCedula() == id)  // Compara la cédula
        {
            cout << "Persona encontrada:\n"
                 << "Nombre_1 = " << actual->getNombre1()
                 << ", \nNombre_2 = " << actual->getNombre2()
                 << ", \nApellido = " << actual->getApellido()
                 << ", \nCédula = " << actual->getCedula()
                 << ", \nCorreo = " << actual->getCorreo()
                 << endl;
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Persona no encontrado" << endl;
}

void Lista_Doble::Mostrar() const
{
    Nodo *actual = cabeza;
    if (actual == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    while (actual != nullptr)
    {
        // Ahora también imprimimos la cédula junto con los demás datos
        cout << "Nombre_1: " << actual->getNombre1() 
             << ", Nombre_2: " << actual->getNombre2() 
             << ", Apellido: " << actual->getApellido() 
             << ", Cedula: " << actual->getCedula() 
             << ", Correo: " << actual->getCorreo() 
             << endl;
             
        actual = actual->getSiguiente();
    }
}

// Función para dividir la lista en dos mitades
Nodo* Lista_Doble::dividir(Nodo* cabeza) {
    if (cabeza == nullptr || cabeza->getSiguiente() == nullptr) {
        return cabeza;
    }
    
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza->getSiguiente();

    while (rapido != nullptr && rapido->getSiguiente() != nullptr) {
        lento = lento->getSiguiente();
        rapido = rapido->getSiguiente()->getSiguiente();
    }

    Nodo* mitad = lento->getSiguiente();
    lento->setSiguiente(nullptr);  // Divide la lista en dos mitades

    return mitad;
}

// Función para fusionar dos listas de forma ordenada según el criterio seleccionado
Nodo* Lista_Doble::fusionar(Nodo* izquierda, Nodo* derecha, int criterio)
{
    Nodo* resultado = nullptr;

    if (!izquierda)
        return derecha;
    if (!derecha)
        return izquierda;

    // Comparación según el criterio seleccionado
    if (criterio == 1) {  // Ordenar por primer nombre
        if (izquierda->getNombre1() <= derecha->getNombre1()) {
            resultado = izquierda;
            resultado->setSiguiente(fusionar(izquierda->getSiguiente(), derecha, criterio));
        } else {
            resultado = derecha;
            resultado->setSiguiente(fusionar(izquierda, derecha->getSiguiente(), criterio));
        }
    } else if (criterio == 2) {  // Ordenar por apellido
        if (izquierda->getApellido() <= derecha->getApellido()) {
            resultado = izquierda;
            resultado->setSiguiente(fusionar(izquierda->getSiguiente(), derecha, criterio));
        } else {
            resultado = derecha;
            resultado->setSiguiente(fusionar(izquierda, derecha->getSiguiente(), criterio));
        }
    } else if (criterio == 3) {  // Ordenar por cédula de menor a mayor
        if (izquierda->getCedula() >= derecha->getCedula()) {  // Cambiado a >= para ordenar de menor a mayor
            resultado = derecha;
            resultado->setSiguiente(fusionar(izquierda, derecha->getSiguiente(), criterio));
        } else {
            resultado = izquierda;
            resultado->setSiguiente(fusionar(izquierda->getSiguiente(), derecha, criterio));
        }
    }

    return resultado;
}

// Función recursiva para ordenar la lista usando Merge Sort
Nodo* Lista_Doble::mezclaDirecta(Nodo* cabeza, int criterio) {
    if (!cabeza || !cabeza->getSiguiente()) {
        return cabeza;
    }

    Nodo* mitad = dividir(cabeza);
    Nodo* izquierda = mezclaDirecta(cabeza, criterio);
    Nodo* derecha = mezclaDirecta(mitad, criterio);

    return fusionar(izquierda, derecha, criterio);
}

void Lista_Doble::ordenarLista(int opcionOrden) {
    // Ordenar la lista con el criterio seleccionado
    cabeza = mezclaDirecta(cabeza, opcionOrden);

    cout << "\nLista ordenada correctamente.\n";
}

// Cambiar el tipo de retorno de void a bool
bool Lista_Doble::guardarEnArchivo(const string &filename) {
    ofstream archivo(filename, ios::out | ios::trunc);  // Esto crea el archivo si no existe
    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
        return false;  // Retornar false si no se pudo abrir el archivo
    }

    Nodo *actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->getCedula() << ","
                << actual->getNombre1() << ","
                << actual->getNombre2() << ","
                << actual->getApellido() << ","
                << actual->getCorreo() << endl;
        actual = actual->getSiguiente();
    }

    archivo.close();
    return true;  // Retornar true si el archivo se guardó correctamente
}




bool Lista_Doble::cargarDesdeArchivo(const string &filename) {
    ifstream archivo(filename, ios::in);
    if (!archivo) {
        // Si el archivo no existe, lo indicamos y no intentamos cargar nada
        cout << "El archivo no existe. Se creará un archivo nuevo al guardar los datos." << endl;
        return false;
    }

    string cedula, nombre1, nombre2, apellido, correo;
    while (getline(archivo, cedula, ',') && 
           getline(archivo, nombre1, ',') && 
           getline(archivo, nombre2, ',') && 
           getline(archivo, apellido, ',') && 
           getline(archivo, correo)) {

        Nodo *nuevoNodo = new Nodo(nombre1, nombre2, apellido, cedula);
        nuevoNodo->setCorreo(correo);

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->setSiguiente(nuevoNodo);
            nuevoNodo->setAnterior(cola);
            cola = nuevoNodo;
        }
    }

    archivo.close();
    return true;
}



// Cambiar el tipo de retorno de void a bool
bool Lista_Doble::guardarListaOrdenada(const string &filename, int opcionOrden) {
    ofstream archivo(filename, ios::out | ios::trunc);  // Esto crea el archivo si no existe
    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar los datos ordenados." << endl;
        return false;  // Retornar false si no se pudo abrir el archivo
    }

    Nodo *actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->getCedula() << ","
                << actual->getNombre1() << ","
                << actual->getNombre2() << ","
                << actual->getApellido() << ","
                << actual->getCorreo() << endl;
        actual = actual->getSiguiente();
    }

    archivo.close();
    return true;  // Retornar true si los datos ordenados se guardaron correctamente
}


