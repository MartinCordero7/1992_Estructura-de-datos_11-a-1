/***********************************************************************
 * Module:  Validaciones.cpp
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Validaciones.h"
#include <iostream>
#include <regex>
#include <conio.h>
#include <stdio.h>
#define dim 10

bool validarCedula(const std::string& cedula) {
    return std::regex_match(cedula, std::regex("\\d{10}")); // Comprueba que tenga exactamente 10 dígitos.
}

bool validarSoloLetras(const std::string& texto) {
    return std::regex_match(texto, std::regex("[A-Za-z ]+")); // Solo permite letras y espacios.
}

long int ingresarCedulaNumerica() {
    long int cedula;
    printf("Ingrese su cedula (numerica): ");
    scanf("%ld", &cedula);
    return cedula;
}

bool validarCedulaReal(long int x) {
    int i, A[dim], res, sumapares = 0, sumaimpares = 0, s, mul, sumatotal = 0;
    long int coc;

    for (i = 9; i >= 0; i--) {
        coc = x / 10;
        res = x % 10;
        A[i] = res;
        x = coc;
    }

    for (i = 0; i < 9; i += 2) {
        mul = A[i] * 2;
        if (mul > 9) {
            mul -= 9;
        }
        sumapares += mul;
    }

    for (i = 1; i < 9; i += 2) {
        sumaimpares += A[i];
    }

    sumatotal = sumapares + sumaimpares;
    res = sumatotal % 10;
    s = 10 - res;
    if (s == 10) {
        s = 0;
    }
    return (s == A[9]);
}

void imprimirResultadoCedula(bool valido) {
    if (valido) {
        printf("Cedula valida.\n");
    } else {
        printf("Cedula no valida.\n");
    }
}


bool validarNombre(const std::string& nombre) {
    std::regex regexNombre("^[A-Za-z]+$");

    // Verificar si el nombre está vacío o tiene solo espacios
    if (nombre.empty() || nombre.find_first_not_of(' ') == std::string::npos) {
        std::cout << "Error: El nombre no puede estar vacio o contener solo espacios.\n";
        return false;
    }

    // Verificar que el nombre cumpla con el patrón
    if (!std::regex_match(nombre, regexNombre)) {
        std::cout << "Error: El nombre solo debe contener letras y sin espacios adicionales.\n";
        return false;
    }

    return true;
}

std::string leerSoloNumeros() {
    std::string input;
    char ch;
    while (true) {
        ch = _getch(); // Captura el carácter ingresado
        if (isdigit(ch)) { // Solo números
            std::cout << ch; // Muestra el carácter en pantalla
            input += ch;     // Lo agrega al string
        } else if (ch == '\r') { // Enter
            std::cout << std::endl;
            break;
        } else if (ch == '\b' && !input.empty()) { // Backspace
            std::cout << "\b \b"; // Borra el último carácter en la consola
            input.pop_back();     // Borra el último carácter del string
        }
    }
    return input;
}
