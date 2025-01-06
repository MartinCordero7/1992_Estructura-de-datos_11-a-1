/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista doble
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include "Lista_Doble.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

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

void Lista_Doble::exportarAArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::out | ios::trunc);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para exportar" << endl;
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->getCedula() << "," 
                << actual->getNombre1() << "," 
                << actual->getNombre2() << "," 
                << actual->getApellido() << "\n";
        actual = actual->getSiguiente();
    }

    archivo.close();
}

void Lista_Doble::radixSortExterno(const string& archivoEntrada, const string& archivoSalida, int longitudCedula) {
    vector<string> buckets[10];
    string linea;

    // Iterar por cada dígito de menor a mayor significancia
    for (int pos = longitudCedula - 1; pos >= 0; --pos) {
        ifstream archivo(archivoEntrada);
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo de entrada" << endl;
            return;
        }

        // Colocar cada línea en el bucket correspondiente
        while (getline(archivo, linea)) {
            string cedula = linea.substr(0, linea.find(','));
            int digito = cedula[pos] - '0';
            buckets[digito].push_back(linea);
        }
        archivo.close();

        // Escribir los buckets nuevamente en el archivo de entrada
        ofstream archivoTemp(archivoEntrada, ios::out | ios::trunc);
        if (!archivoTemp.is_open()) {
            cerr << "Error al abrir el archivo temporal" << endl;
            return;
        }

        for (int i = 0; i < 10; ++i) {
            for (const string& registro : buckets[i]) {
                archivoTemp << registro << "\n";
            }
            buckets[i].clear();
        }
        archivoTemp.close();
    }

    // Renombrar el archivo ordenado final
    rename(archivoEntrada.c_str(), archivoSalida.c_str());
}


void Lista_Doble::importarDeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para importar" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);

        string cedula = linea.substr(0, pos1);
        string nombre1 = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string nombre2 = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        string apellido = linea.substr(pos3 + 1);

        int count = 0;
        Insertar(nombre1, nombre2, apellido, count, cedula);
    }

    archivo.close();
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
