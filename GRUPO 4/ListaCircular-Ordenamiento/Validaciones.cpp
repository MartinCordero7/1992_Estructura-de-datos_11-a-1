/**
 * @file
 * @description 
 * @author Eric000
 * @date 12/11/2024, 7:28:11 AM
 */

#include "Validaciones.h"
#include "Utilidad.cpp"
#include <limits>
#include <cctype>
#include <windows.h>

using namespace std;

void limpiarUltimaLinea()
{
    std::cout << "\r";                            // Moves the cursor to the beginning of the current line
    std::cout << "                             "; // Overwrites the current line with spaces
    std::cout << "\r";                            // Moves the cursor back to the beginning
}

int leerEntero(const string &mensaje)
{
    int valor;
    while (true)
    {
        cout << mensaje;
        cin >> valor;
        if (cin.fail())
        {
            cin.clear();                                         // Limpia el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            cout << "Entrada invalida. Por favor, ingrese un numero entero.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de la entrada
            return valor;
        }
    }
}

string leerString(const string &mensaje)
{
    string valor;
    while (true)
    {
        cout << mensaje;
        getline(cin, valor);
        if (valor.empty())
        {
            cout << "La entrada no puede estar vacía. Intentelo de nuevo.\n";
        }
        else
        {
            return valor;
        }
    }
}



bool esAnioBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}



Fecha leerFecha(const string &tipoFecha, int anioMaximo) {
    int dia, mes, anio;
    const int anioMinimo = 1900;
    const int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Leer mes
    do {
        cout << "Ingrese el mes (1-12) para la " << tipoFecha << ": ";
        mes = ingresarInt("", 2, '1');

        if (mes >= 1 && mes <= 12) {
            cout<<endl;
            break; // Entrada valida
            
        }

        cout << "\r\033[K" ;
    } while (true);

    // Leer anio
    do {
        cout << "Ingrese el anio (" << anioMinimo << "-" << anioMaximo << ") para la " << tipoFecha << ": ";
        anio = ingresarInt("", 4, '1');

        if (anio >= anioMinimo && anio <= anioMaximo) {
            cout<<endl;

            break; // Entrada valida
        }

        cout << "\r\033[K";
    } while (true);

    // Leer dia
    do {
        cout << "Ingrese el dia (1-31) para la " << tipoFecha << ": ";
        dia = ingresarInt("", 2, '1');

        int diasMaximos = diasEnMes[mes - 1];
        if (mes == 2 && esAnioBisiesto(anio)) {
            diasMaximos = 29;
        }

        if (dia >= 1 && dia <= diasMaximos) {
            break; // Entrada valida
        }

        cout << "\r\033[K" ;
    } while (true);

    return Fecha(dia, mes, anio);
}

bool validarCedulaEcuadoriana(const string &cedula)
{
    int longitud = cedula.length();

    // La cédula debe tener 10 dígitos
    if (longitud != 10)
    {
        return false;
    }

    // Validar que todos los caracteres sean números
    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            return false; // Si algún carácter no es un número, es inválido
        }
    }

    // Validar el primer dígito (provincia) debe estar entre 1 y 24
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24)
    {
        return false; // Provincia no válida
    }

    // Validar el dígito verificador
    int digitoVerificador = cedula[9] - '0'; // El último dígito es el dígito verificador
    int sumaPares = 0, sumaImpares = 0;

    // Recorrer la cédula y aplicar los factores de multiplicación
    for (int i = 0; i < 9; ++i)
    {
        int digito = cedula[i] - '0'; // Convertir el carácter a número
        if (i % 2 == 0)
        {
            // Multiplicar los dígitos en las posiciones pares (0, 2, 4, 6, 8) por 2
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9; // Si el número es mayor a 9, restamos 9
            }
        }
        if (i % 2 == 0)
        {
            sumaPares += digito;
        }
        else
        {
            sumaImpares += digito;
        }
    }

    int sumaTotal = sumaPares + sumaImpares;
    int mod = sumaTotal % 10;
    int digitoCorrecto = (mod == 0) ? 0 : 10 - mod;

    // Comprobar si el dígito verificador es correcto
    return digitoVerificador == digitoCorrecto;
}

Autor ingresarAutor(ListaDobleCircular<Autor> &listaAutores)
{
    string cedula;

    do
    {
        cedula = validarCedula("Ingrese la cedula: ");
        // Verificamos si la cédula ya está en la lista
        if (listaAutores.buscarCedula(cedula) != nullptr)
        {
            std::cout << "\nLa cedula ya existe en la lista. Ingrese una cedula diferente.\n";
        }
    } while (listaAutores.buscarCedula(cedula) != nullptr);

    string nombre = ingresarStringS("Ingrese el nombre del autor: ");
    string apellido = ingresarStringS("\nIngrese el apellido del autor: ");
    string nacionalidad = ingresarStringS("\nIngrese la nacionalidad del autor: ");
    cout << endl;
    Fecha fechaNacimiento = leerFecha("fecha de nacimiento", 2010);
    return Autor(cedula, nombre, apellido, nacionalidad, fechaNacimiento);
}

Libro ingresarLibro(ListaDobleCircular<Autor> &listaAutores,ListaDobleCircular<Libro> &listaLibros)
{
int id;
    do
    {
        id = ingresarInt("Ingrese el ID del libro (numero entero): ", 2, '1');

        // Verificamos si el ID ya está en la lista
        if (listaLibros.buscarId(id) != nullptr)
        {
            std::cout << "\nEl ID ya existe en la lista. Ingrese un ID diferente.\n";
        }
    } while (listaLibros.buscarId(id) != nullptr);

    string nombre = ingresarString("\nIngrese el nombre del libro: ",3);
    // string nombre=leerString("\nIngrese el nombre del libro:");
    string editorial = ingresarStringN("\nIngrese la editorial del libro: ",3);
    string genero = ingresarStringN("\nIngrese el genero del libro: ",3);
    string serie = ingresarString("\nIngrese la serie del libro: ",3);
    cout << endl;
    double rating = ingresarDouble("Ingrese el rating del libro(sobre 5 estrellas): ", 1.00, 5.00);
    cout << endl;
    string cedulaAutor;
    Autor autorBuscado;
    do
    {
        cedulaAutor = validarCedula("Ingrese la cedula del autor: ");
        Nodo<Autor> *nodoAutor = listaAutores.buscar(Autor(cedulaAutor, "", "", Fecha()));
        if (nodoAutor != nullptr)
        {
            autorBuscado = nodoAutor->dato;
            break;
        }
        else
        {
            cout << "Autor no encontrado. Intente nuevamente.\n";
        }
    } while (true);

    Fecha fechaPublicacion = leerFecha("fecha de publicacion", 2024);
    cout << endl;
    return Libro(id, nombre, autorBuscado, editorial, serie, genero, rating, fechaPublicacion);
}
