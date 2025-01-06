#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdbool.h>
#include <cstdlib>
#include <cmath>
using namespace std;

int ingresarInt(const char *);

// Ingresar enteros------------------------------------------------------------------------

int ingresarInt(const char *msj)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (c >= '0' && c <= '9' && i < 9)
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i++] = '\0';
    valor = atoi(cad);
    return valor;
}

int ingresarInt(const char *msj, int t)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (c >= '0' && c <= '9' && i < t)
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i++] = '\0';
    valor = atoi(cad);
    return valor;
}

int ingresarInt(const char *msj, int t, char menorValor)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);

    while ((c = getch()) != 13)
    {
        if (i == 0)
        {
            if (c >= menorValor && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i > 0)
        {
            if (c >= '0' && c <= '9' && i < t)
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8 && i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0';     // Null-terminate the string
    valor = atoi(cad); // Convert to integer
    return valor;
}

int ingresarInt(const char *msj, int t, char menorValor,char mayorValor)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);

    while ((c = getch()) != 13)
    {
        if (i == 0)
        {
            if (c >= menorValor && c <= '9' && c<=mayorValor)
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i > 0)
        {
            if (c >= '0' && c <= '9' && i < t)
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8 && i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0';     // Null-terminate the string
    valor = atoi(cad); // Convert to integer
    return valor;
}

int ingresarIntt(const char *msj, int t, char menorValor, char mayorValor)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);

    while (true)
    {
        c = getch();

        if (c == 13) // Enter key
        {
            if (i > 0) // Allow Enter only if input is not empty
                break;
        }
        else if (i == 0)
        {
            if (c >= menorValor && c <= '9' && c <= mayorValor)
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i > 0)
        {
            if (c >= '0' && c <= '9' && i < t)
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8 && i > 0) // Backspace
            {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0';     // Null-terminate the string
    valor = atoi(cad); // Convert to integer
    return valor;
}


int ingresarIntt(const char *msj, int t, char menorValor)
{
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);

    while (true)
    {
        c = getch();

        if (c == 13) // Enter key
        {
            if (i > 0) // Allow Enter only if input is not empty
                break;
        }
        else if (i == 0)
        {
            if (c >= menorValor && c <= '9' )
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i > 0)
        {
            if (c >= '0' && c <= '9' && i < t)
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8 && i > 0) // Backspace
            {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0';     // Null-terminate the string
    valor = atoi(cad); // Convert to integer
    return valor;
}

int ingresarInt(const string &msj, int t, char menorValor)
{

    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13 && i == 0)
    {
        if (i == 0)
        {
            if (c >= menorValor && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        else if (i > 0)
        {
            if (c >= '0' && c <= '9' && i < t)
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8 && i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }

    cad[i] = '\0';     // Null-terminate the string
    valor = atoi(cad); // Convert to integer
    return valor;
}

// Ingresar una letra-------------------------------------------------------------------------
char ingresarLetra(char *);
char ingresarLetra(char *msj)
{
    char letra = '\0', c;
    int i = 0;
    printf("%s", msj);
    while ((c = getch()) != 13 || i == 0)
    {
        if (isalpha(c) && i == 0 && c != 13)
        {
            printf("%c", c);
            letra = c;
            i = 1;
        }
        else if (c == 8 && i == 1)
        {
            printf("\b \b");
            letra = '\0';
            i = 0;
        }
    }
    return letra;
}

// Ingresar float------------------------------------------------------------------------------

float ingresarFloat(char *);
float ingresarFloat(char *msj)
{
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (c >= '0' && c <= '9')
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else if (c == 46)
        {
            bool aux = false;
            for (int j = 0; cad[j] != '\0'; j++)
            {
                if (cad[j] == 46)
                {
                    aux = true;
                    break;
                }
            }
            if (aux == false)
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
    }
    cad[i++] = '\0';
    for (int j = 0; cad[j] != '\0'; j++)
    {
        valor = atof(cad);
    }
    return valor;
}

// ingresar un string---------------------------------------------------------------------------------------
string ingresarString(const char *);
string ingresarString(const char *msj)
{
    char cad[10];
    char c;
    int i = 0;
    string valor;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (isalpha(c))
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    for (int j = 0; cad[j] != '\0'; j++)
    {
        valor = valor + cad[j];
    }

    return valor;
}
std::string ingresarStringS(const char *msj)
{
    const int limite = 60; // Usamos el límite máximo del tipo std::string
    char c;
    std::string valor;

    printf("%s", msj);
    while ((c = getch()) != 13 || valor.empty())
    { // Enter (ASCII 13)
        if (isalpha(c) && valor.size() < limite)
        { // Solo permite letras y dentro del límite
            printf("%c", c);
            valor += c;
        }
        else if (c == 8 && !valor.empty())
        { // Backspace
            printf("\b \b");
            valor.pop_back();
        }
    }
    return valor;
}

std::string ingresarStringA(const char *msj, int limite)
{
    char cad[limite + 1]; // Más 1 para el carácter nulo
    char c;
    int i = 0;
    std::string valor, valo;
    printf("%s", msj);
    while ((c = getch()) != 13 || valo.empty())
    { // 13 es Enter
        if (isprint(c) && i < limite)
        { // Validar caracteres imprimibles y límite
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8 && i > 0)
        { // Validar Backspace
            printf("\b \b");
            i--;
        }
        valo = cad;
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}

std::string ingresarNumeros(const char *msj, int limite)
{
    char cad[limite + 1]; // Espacio para el carácter nulo
    char c;
    int i = 0;
    std::string valor;

    printf("%s", msj);
    while ((c = getch()) != 13)
    { // 13 es Enter
        if (isdigit(c) && i < limite)
        { // Validar si es número y está dentro del límite
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8 && i > 0)
        { // Backspace
            printf("\b \b");
            i--;
        }
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}

std::string ingresarNumero(const char *msj, int limite)
{
    char cad[limite + 1]; // Espacio para el carácter nulo
    char c;
    int i = 0;
    std::string valor;

    printf("%s", msj);
    while (true)
    {
        c = getch();
        if (isdigit(c) && i < limite)
        { // Validar si es número y está dentro del límite
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8 && i > 0)
        { // Backspace
            printf("\b \b");
            i--;
        }
        else if (c == 13 && i == limite)
        { // Enter presionado con exactamente `limite` dígitos
            break;
        }
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}

// std::string ingresarString(const char *msj, int limiteEspacios)
// {
//     const int limiteInterno = 60; // Límite máximo permitido por std::string
//     char c;
//     int i = 0, espacios = 0;
//     char cad[limiteInterno + 1]; // Espacio para el carácter nulo
//     std::string valor;

//     printf("%s", msj);
//     while ((c = getch()) != 13)
//     { // 13 es Enter
//         if ((isalpha(c) || isdigit(c) || (c == ' ' && espacios < limiteEspacios)) && i < limiteInterno)
//         {
//             if (c == ' ')
//             {
//                 espacios++; // Contar espacios
//             }
//             printf("%c", c);
//             cad[i++] = c;
//         }
//         else if (c == 8 && i > 0)
//         { // Backspace
//             if (cad[i - 1] == ' ')
//             {
//                 espacios--; // Restar espacio al borrar
//             }
//             printf("\b \b");
//             i--;
//         }
//     }
//     cad[i] = '\0';
//     valor = cad;
//     return valor;
// }


std::string ingresarString(const char *msj, int limiteEspacios)
{
    const int limiteInterno = 60; // Límite máximo permitido por std::string
    char c;
    int i = 0, espacios = 0;
    char cad[limiteInterno + 1]; // Espacio para el carácter nulo
    std::string valor;

    printf("%s", msj);
    while (true)
    {
        c = getch();
        if (c == 13 && i > 0) // Enter presionado y al menos un carácter ingresado
        {
            break;
        }
        else if ((isalpha(c) || isdigit(c) || (c == ' ' && espacios < limiteEspacios)) && i < limiteInterno)
        {
            if (c == ' ')
            {
                espacios++; // Contar espacios
            }
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8 && i > 0) // Backspace
        {
            if (cad[i - 1] == ' ')
            {
                espacios--; // Restar espacio al borrar
            }
            printf("\b \b");
            i--;
        }
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}

std::string ingresarStringN(const char *msj, int limiteEspacios)
{
    const int limiteInterno = 60; // Límite máximo permitido por std::string
    char c;
    int i = 0, espacios = 0;
    char cad[limiteInterno + 1]; // Espacio para el carácter nulo
    std::string valor;

    printf("%s", msj);
    while (true)
    {
        c = getch();
        if (c == 13 && i > 0) // Enter presionado y al menos un carácter ingresado
        {
            break;
        }
        else if ((isalpha(c) || (c == ' ' && espacios < limiteEspacios)) && i < limiteInterno)
        {
            if (c == ' ')
            {
                espacios++; // Contar espacios
            }
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8 && i > 0) // Backspace
        {
            if (cad[i - 1] == ' ')
            {
                espacios--; // Restar espacio al borrar
            }
            printf("\b \b");
            i--;
        }
    }
    cad[i] = '\0';
    valor = cad;
    return valor;
}


// Ingresar double------------------------------------------------------------------------------
double ingresarDouble(const char *msj)
{
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    printf("%s", msj);
    bool puntoDecimal = false;
    while ((c = getch()) != 13)
    {
        if (c >= '0' && c <= '9')
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else if (c == '.' && !puntoDecimal)
        {
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

double ingresarDouble(const char *msj, double min, double max)
{
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    bool puntoDecimal = false;
    int digitosDespuesDelPunto = 0;

    printf("%s", msj);

    while ((c = getch()) != 13) // 13 is Enter
    {
        // Allow only digits (0-9)
        if (c >= '0' && c <= '9')
        {
            if (i < 4) // Max 5 characters (including the decimal point)
            {
                printf("%c", c);
                cad[i++] = c;
            }
        }
        // Allow only one decimal point
        else if (c == '.' && !puntoDecimal)
        {
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
        }
        // Allow backspace to delete characters
        else if (c == 8 && i > 0)
        {
            printf("\b \b");
            i--;
            if (puntoDecimal && digitosDespuesDelPunto > 0)
            {
                digitosDespuesDelPunto--;
            }
        }
        // Ignore invalid input
    }

    cad[i] = '\0';
    valor = atof(cad);

    // Check if the value is within the specified range
    if (valor < min || valor > max)
    {
        printf("\r\033[K");                   // Clear previous line
        return ingresarDouble(msj, min, max); // Recurse to ask for input again if out of range
    }

    return valor;
}

double ingresarDouble(const char *msj, double min, double max, int maxDigits, int maxDecimalDigits)
{
    char cad[20]; // Buffer for input
    char c;
    int i = 0;
    double valor = 0;
    bool puntoDecimal = false;
    int digitosDespuesDelPunto = 0;

    printf("%s", msj);

    while (true)
    {
        c = getchar();

        // Allow digits (0-9)
        if (c >= '0' && c <= '9')
        {
            if (i < maxDigits)
            { // Max total digits (including decimal)
                printf("%c", c);
                cad[i++] = c;
                if (puntoDecimal)
                {
                    digitosDespuesDelPunto++;
                }
            }
        }
        // Allow only one decimal point
        else if (c == '.' && !puntoDecimal)
        {
            if (i == 0 || digitosDespuesDelPunto == 0)
            { // Ensure there's at least one digit before the decimal
                continue;
            }
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
        }
        // Handle backspace (delete characters)
        else if (c == 8 && i > 0)
        {
            printf("\b \b");
            i--;
            if (puntoDecimal && digitosDespuesDelPunto > 0)
            {
                digitosDespuesDelPunto--;
            }
        }
        // Handle Enter key to end input
        else if (c == '\n')
        {
            break;
        }
        // Ignore other characters
        else
        {
            continue;
        }
    }

    cad[i] = '\0';
    valor = atof(cad); // Convert the string to double

    // Check if the number of digits after the decimal exceeds the limit
    if (puntoDecimal && digitosDespuesDelPunto > maxDecimalDigits)
    {
        printf("\r\033[K"); // Clear previous line
        cout << "Too many decimal places. Please try again." << endl;
        return ingresarDouble(msj, min, max, maxDigits, maxDecimalDigits); // Recurse to ask for input again
    }

    // Check if the value is within the specified range
    if (valor < min || valor > max)
    {
        printf("\r\033[K"); // Clear previous line
        cout << "Value out of range. Please try again." << endl;
        return ingresarDouble(msj, min, max, maxDigits, maxDecimalDigits); // Recurse if out of range
    }

    return valor;
}

int SumarEnteros(int obj1, int obj2)
{
    int temporal;
    temporal = obj1 + obj2;
    return temporal;
}

float SumarFlotantes(float obj1, float obj2)
{
    ingresarString("Ingrese su nombre: ");
    float temporal;
    temporal = obj1 + obj2;
    return temporal;
}



std::string validarCedula(const char *msj)
{
    while (true)
    {
        printf("%s", msj);
        std::string cedula = ingresarNumero("", 10); // Captura una cédula de 10 dígitos
        cout << endl;

        bool todosIguales = true;
        for (int i = 1; i < 10; ++i)
        {
            if (cedula[i] != cedula[0])
            {
                todosIguales = false;
                break;
            }
        }
        if (todosIguales)
        {
            cout << "\033[A\r\033[K"; // Limpia línea anterior
            continue; // Si todos los dígitos son iguales, no es una cédula válida
        }

        // Verificar que la provincia esté en el rango de 01 a 24
        int provincia = std::stoi(cedula.substr(0, 2)); // Primeros dos dígitos corresponden a la provincia
        if (provincia < 1 || provincia > 24)
        {
            cout << "\033[A\r\033[K"; // ANSI escape code para limpiar la línea anterior
            continue;
        }

        // Validación del dígito de verificación
        int suma = 0;
        for (int i = 0; i < 9; ++i)
        {
            int digito = cedula[i] - '0';
            if (i % 2 == 0)
            {
                digito *= 2;
                if (digito > 9)
                    digito -= 9;
            }
            suma += digito;
        }

        int digitoVerificacion = (10 - (suma % 10)) % 10;
        if (digitoVerificacion != (cedula[9] - '0'))
        {
            cout << "\033[A\r\033[K"; // Limpia línea anterior
            continue;
        }

        return cedula;
    }
}

