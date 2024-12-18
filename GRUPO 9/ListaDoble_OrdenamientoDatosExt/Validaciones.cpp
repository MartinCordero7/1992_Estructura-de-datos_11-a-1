/***********************************************************************
 * Module:  Validaciones.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Validaciones.h"
#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <fstream>
#include <conio.h>
#include <limits>

using namespace std;

// Conjunto para almacenar las cedulas unicas
set<string> cedulasRegistradas;

bool validarCedulaReal(const string& cedula) {
    if (cedula.length() != 10) {
        cout << "Error: La cedula debe contener exactamente 10 digitos.\n";
        return false;
    }

    for (char c : cedula) {
        if (!isdigit(c)) {
            cout << "Error: La cedula debe contener solo n�meros.\n";
            return false;
        }
    }

    // Algoritmo de validaci�n ecuatoriano
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) {
        cout << "Error: La cedula tiene un codigo de provincia invalido.\n";
        return false;
    }

    int digitoVerificador = cedula[9] - '0';
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) { // Posiciones impares
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int decenaSuperior = (suma + 9) / 10 * 10;
    int calculado = decenaSuperior - suma;

    if (calculado != digitoVerificador) {
       // cout << "Error: La cedula no es valida.\n";
        return false;
    }

    return true;
}

bool validarCedulaUnica(const string& cedula) {
    ifstream archivo("personas.txt"); // Abre el archivo en modo lectura
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo personas.txt.\n";
        return false; // Consideramos que no es única si no se puede abrir
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t comaPos = linea.find(','); // Busca la posición de la coma
        if (comaPos != string::npos) {
            string cedulaExistente = linea.substr(0, comaPos); // Extrae la cédula
            if (cedulaExistente == cedula) {
                archivo.close();
                return false; // La cédula ya existe
            }
        }
    }
    archivo.close();
    return true; // La cédula no existe
}


void registrarCedula(const string& cedula) {
    cedulasRegistradas.insert(cedula);
}

void eliminarCedula(const string& cedula) {
    cedulasRegistradas.erase(cedula);
}

bool validarSoloLetras(const string& texto) {
    for (char c : texto) {
        if (!isalpha(c) && c != ' ') {
            //cout << "Error: El texto debe contener solo letras.\n";
            return false;
        }
    }
    return true;
}

bool existeCedula(const string& cedula) {
    return cedulasRegistradas.find(cedula) != cedulasRegistradas.end();
}


int capturarSoloNumeros()
{
    string entrada; // Almacena los números ingresados
    char tecla;

    cout << "Seleccione una opcion: ";
    while (true)
    {
        tecla = _getch(); // Captura la tecla presionada (no se muestra en consola automáticamente)

        if (isdigit(tecla)) // Si es un número
        {
            entrada += tecla; // Agregar el número a la entrada
            cout << tecla;    // Mostrar el número en consola
        }
        else if (tecla == '\r') // Si se presiona Enter
        {
            if (!entrada.empty()) // Verificar que no esté vacío
            {
                cout << endl; // Salto de línea
                break;
            }
            else
            {
                cout << "\nError: Debe ingresar al menos un numero. Intente de nuevo.\n";
                cout << "Seleccione una opcion: ";
            }
        }
        else if (tecla == '\b' && !entrada.empty()) // Si se presiona Retroceso (Backspace) y no está vacío
        {
            entrada.pop_back(); // Eliminar el último carácter de la cadena
            cout << "\b \b";    // Borra el carácter mostrado en la consola
        }
        else
        {
            // Ignorar otras teclas no válidas
        }
    }

    return stoi(entrada); // Convertir la entrada a un número entero y devolverlo
}



std::string capturarSoloLetras()
{
    std::string entrada;
    char tecla;
    while (true)
    {
        tecla = _getch(); // Captura un carácter sin mostrarlo directamente en pantalla

        if (isalpha(tecla)) // Si es una letra
        {
            entrada += tecla; // Lo agrega a la entrada
            cout << tecla;    // Lo muestra en pantalla
        }
        else if (tecla == '\r') // Enter (fin de la entrada)
        {
            if (!entrada.empty()) // Verificar que no esté vacío
            {
                cout << endl; // Salto de línea
                break;
            }
            else
            {
                cout << "\nError: Debe ingresar al menos una letra. Intente nuevamente.\n";
                cout << "Ingrese texto: ";
            }
        }
        else if (tecla == '\b' && !entrada.empty()) // Retroceso y que la entrada no esté vacía
        {
            entrada.pop_back(); // Elimina el último carácter de la cadena
            cout << "\b \b";    // Borra el carácter mostrado en la consola
        }
        else
        {
            // Ignorar otras teclas no válidas
        }
    }

    return entrada;
}
std::string normalizarNombre(const std::string& nombre)
{
    if (nombre.empty())
        return ""; // Si está vacío, devolver una cadena vacía

    std::string resultado = nombre;
    resultado[0] = toupper(resultado[0]); // Convertir la primera letra a mayúscula
    for (size_t i = 1; i < resultado.length(); ++i)
    {
        resultado[i] = tolower(resultado[i]); // Convertir las demás letras a minúscula
    }

    return resultado;
}

std::string capturarCedula()
{
    std::string entrada;
    char tecla;
    while (true)
    {
        tecla = _getch(); // Captura un carácter sin mostrarlo directamente en pantalla

        if (isdigit(tecla)) // Si es un número
        {
            entrada += tecla; // Lo agrega a la entrada
            cout << tecla;    // Lo muestra en pantalla
        }
        else if (tecla == '\r') // Enter (fin de la entrada)
        {
            if (!entrada.empty()) // Verificar que no esté vacío
            {
                cout << endl; // Salto de línea
                break;
            }
            else
            {
                cout << "\nError: Debe ingresar al menos un numero. Intente nuevamente.\n";
                cout << "Ingrese cedula: ";
            }
        }
        else if (tecla == '\b' && !entrada.empty()) // Retroceso y que la entrada no esté vacía
        {
            entrada.pop_back(); // Elimina el último carácter de la cadena
            cout << "\b \b";    // Borra el carácter mostrado en la consola
        }
        else
        {
            // Ignorar otras teclas no válidas
        }
    }

    return entrada;
}

char capturarUnaLetra()
{
    char entrada;
    bool letraIngresada = false;  // Indica si ya se ingresó una letra

    while (true)
    {
        entrada = _getch();  // Captura un solo carácter (sin mostrarlo en consola)

        // Si es una letra (mayúscula o minúscula)
        if (isalpha(entrada) && !letraIngresada)
        {
            cout << entrada;  // Muestra la letra en consola
            letraIngresada = true;  // Marca que se ha ingresado una letra
            break;  // Salir del ciclo de captura después de ingresar una letra
        }
        // Si presiona retroceso (Backspace), permite borrar la letra ingresada
        else if (entrada == '\b' && letraIngresada)
        {
            cout << "\b \b";  // Borra el carácter de la consola
            letraIngresada = false;  // Marca que no hay una letra válida
        }
        // Si presiona Enter, ignora pero sigue esperando un carácter válido
        else if (entrada == '\r')
        {
            if (letraIngresada)
            {
                return entrada;   // Devuelve la letra ingresada
            }
            else
            {
                cout << "\nError: Debe ingresar una letra antes de presionar Enter.\n";
                cout << "Ingrese una letra (presione Enter para confirmar): ";
            }
        }
        else
        {
            // Ignora otras teclas (números, símbolos, etc.)
            // No hace nada en el ciclo y sigue esperando una letra
        }
    }

    return entrada;
}


int validarNumero1a25()
{
    string entrada; // Almacena los números ingresados
    char tecla;
    int numero;

    while (true)
    {
        tecla = _getch(); // Captura la tecla presionada (sin mostrarla en consola)

        // Si es un número, se agrega a la entrada
        if (isdigit(tecla))
        {
            entrada += tecla;
            cout << tecla;  // Muestra el número en consola
        }
        // Si presiona retroceso (Backspace), elimina el último número
        else if (tecla == '\b' && !entrada.empty())
        {
            cout << "\b \b";  // Borra el carácter de la consola
            entrada.pop_back();
        }
        // Si presiona Enter, termina el ciclo de entrada
        else if (tecla == '\r')
        {
            if (entrada.empty()) // Si no se ha ingresado nada
            {
                cout << "\nError: Debe ingresar al menos un numero.\n";
                cout << "Ingrese un numero entre 1 y 25: ";
            }
            else
            {
                numero = stoi(entrada); // Convierte la entrada en un número
                if (numero >= 1 && numero <= 25)
                {
                    cout << endl;
                    return numero;  // Si es un número válido, lo retornamos
                }
                else
                {
                    cout << "\nError: Debe ingresar un numero entre 1 y 25.\n";
                    cout << "Ingrese un numero entre 1 y 25: ";
                    entrada.clear(); // Limpiamos la entrada para que ingrese de nuevo
                }
            }
        }
        // Ignorar cualquier otra tecla
    }
}
