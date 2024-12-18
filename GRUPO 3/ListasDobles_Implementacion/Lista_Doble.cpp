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

void Passord(string &N1, string &N2, string &Ape)
{
    char ultimaLetraApe = tolower(Ape.back());
    char primeraLetraN1 = tolower(N1.front());
    char ultimaLetraN2 = tolower(N2.back());
    string apellidoInverso = Ape.substr(0, Ape.length() - 1);
    reverse(apellidoInverso.begin(), apellidoInverso.end());
    string concatenacion = string(1, ultimaLetraApe) + primeraLetraN1 + ultimaLetraN2 + apellidoInverso;
    cout << concatenacion << endl;
    int desplazamiento = 2;
    string password = cifradoCesar(concatenacion, desplazamiento);

    cout << "Contraseña generada: " << password << endl;
}
void Lista_Doble::Eliminar(string &N1, string &N2, string &Ape)
{
    Nodo *actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape)
        {
            if (actual->getAnterior() != nullptr)
            {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
            }
            else
            {
                cabeza = actual->getSiguiente();
            }
            if (actual->getSiguiente() != nullptr)
            {
                actual->getSiguiente()->setAnterior(actual->getAnterior());
            }
            else
            {
                cola = actual->getAnterior();
            }
            delete actual;
            cout << "Nodo eliminado" << endl;
            cout << "Correo del nodo eliminado: " << endl;
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Nodo no encontrado para eliminar" << endl;
}

void Lista_Doble ::Buscar(string &N1, string &N2, string &Ape)
{
    Nodo *actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->getNombre1() == N1 && actual->getNombre2() == N2 && actual->getApellido() == Ape)
        {
            cout << "Nodo encontrado:\n"
                 << "N1 = " << actual->getNombre1()
                 << ", \nNombre2 = " << actual->getNombre2()
                 << ", \nApellido = " << actual->getApellido()
                 << ", Correo = " << actual->getCorreo()
                 << endl;
            return;
        }
        actual = actual->getSiguiente();
    }
    cout << "Nodo no encontrado" << endl;
}

void Lista_Doble::Mostrar() const
{
    Nodo *actual = cabeza;
    while (actual != nullptr)
    {
        cout << "Nombre1: " << actual->getNombre1()
             << ", Nombre2: " << actual->getNombre2()
             << ", Apellido: " << actual->getApellido()
             << " -> <- ";
        actual = actual->getSiguiente();
    }
    cout << "nullptr" << endl;
}
void Lista_Doble::Shellsort() {
    if (!cabeza || !cabeza->getSiguiente()) {
        return; // Si la lista está vacía o tiene solo un nodo, no es necesario ordenar
    }

    // Determinamos el tamaño de la lista
    int n = 0;
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        n++;
        temp = temp->getSiguiente();
    }

    // Usamos el algoritmo de Shellsort, con intervalos decrecientes
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Empezamos con el primer nodo y comparamos con el nodo "gap" posiciones adelante
        for (int i = gap; i < n; i++) {
            Nodo* actual = cabeza;
            Nodo* siguiente = cabeza;
            // Avanzamos hasta el nodo i
            for (int j = 0; j < i; j++) {
                siguiente = siguiente->getSiguiente();
            }

            // Comparamos el nodo actual con el nodo `gap` posiciones adelante
            for (int j = i; j >= gap; j -= gap) {
                Nodo* anterior = cabeza;
                for (int k = 0; k < j - gap; k++) {
                    anterior = anterior->getSiguiente();
                }

                // Comparar los nodos actual y anterior, intercambiarlos si es necesario
                if (anterior->getNombre1() + anterior->getNombre2() + anterior->getApellido() >
                    siguiente->getNombre1() + siguiente->getNombre2() + siguiente->getApellido()) {
                    // Realizar intercambio de valores
                    string tmpN1 = anterior->getNombre1();
                    string tmpN2 = anterior->getNombre2();
                    string tmpApe = anterior->getApellido();
                    string tmpCorreo = anterior->getCorreo();

                    anterior->setNombre1(siguiente->getNombre1());
                    anterior->setNombre2(siguiente->getNombre2());
                    anterior->setApellido(siguiente->getApellido());
                    anterior->setCorreo(siguiente->getCorreo());

                    siguiente->setNombre1(tmpN1);
                    siguiente->setNombre2(tmpN2);
                    siguiente->setApellido(tmpApe);
                    siguiente->setCorreo(tmpCorreo);
                }
                siguiente = siguiente->getSiguiente();
            }
        }
    }
}
