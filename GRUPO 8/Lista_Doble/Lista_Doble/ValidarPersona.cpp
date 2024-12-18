/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//ValidarPersona.cpp

#include "ValidarPersona.h"
#include <iostream>
#include <cctype>
#include <conio.h>
#include <string>

Persona persona;

void ValidarPersona::ingresar_cedula(const char* mensaje,Persona& persona) {
    char c;
    std::string cedula;
    cedula.clear(); 
    std::cout << mensaje;

    while (true) {
        c = getch(); // Leer un carácter
        if (c >= '0' && c <= '9') { 
            if (cedula.size() < 10) { // valida q no se ingrese mas de 10 digitos
                std::cout << c; 
                cedula += c; 
            }
        } else if (c == 8 && !cedula.empty()) { //permite retroceder
            std::cout << "\b \b"; 
            cedula.pop_back();   
        } else if (c == 13 && cedula.size() == 10) { // valida q no se ingrese menos de 10 digitos
            std::cout << std::endl;
            break; 
        }
    }

    persona.set_cedula(cedula); 
}

void ValidarPersona::ingresar_nombre(const char* mensaje,Persona& persona) {
    char c; 
    std::string nombre;
    nombre.clear();
    std::cout << mensaje;

    while (true) {
        c = getch();
        if (isalpha(c)) {
            std::cout << c; 
            nombre += c;  
        } else if (c == 8 && !nombre.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            nombre.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (!nombre.empty()) {
                std::cout << std::endl;
                break; // Salir del bucle si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula
    if (!nombre.empty()) {
        nombre[0] = toupper(nombre[0]);
    }

    persona.set_nombre(nombre);
}

void ValidarPersona::ingresar_apellido(const char* mensaje,Persona& persona) {
    char c; 
    std::string apellido;
    apellido.clear();
    std::cout << mensaje;

    while (true) {
        c = getch();
        if (isalpha(c)) {
            std::cout << c; 
            apellido += c;  
        } else if (c == 8 && !apellido.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            apellido.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (!apellido.empty()) {
                std::cout << std::endl;
                break; // Salir del bucle si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula
    if (!apellido.empty()) {
        apellido[0] = toupper(apellido[0]);
    }

    persona.set_apellido(apellido);
}

std::string ValidarPersona::ingresar_cedula_sin_persona() {
    std::string cedula;
    char c;
    cedula.clear(); 

    while (true) {
        c = getch(); // Leer un carácter
        if (c >= '0' && c <= '9') { 
            if (cedula.size() < 10) { // valida q no se ingrese mas de 10 digitos
                std::cout << c; 
                cedula += c; 
            }
        } else if (c == 8 && !cedula.empty()) { //permite retroceder
            std::cout << "\b \b"; 
            cedula.pop_back();   
        } else if (c == 13 && cedula.size() == 10) { // valida q no se ingrese menos de 10 digitos
            std::cout << std::endl;
            break; 
        }
    }
    return cedula;
    
}

std::string ValidarPersona::ingresar_nombre_sin_persona(){
    std::string nombre;
    char c; 
    nombre.clear();

    while (true) {
        c = getch();
        if (isalpha(c)) {
            std::cout << c; 
            nombre += c;  
        } else if (c == 8 && !nombre.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            nombre.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (!nombre.empty()) {
                std::cout << std::endl;
                break; // Salir del bucle si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula
    if (!nombre.empty()) {
        nombre[0] = toupper(nombre[0]);
    }

    return nombre;
}

std::string ValidarPersona::ingresar_apellido_sin_persona(){
    std::string apellido;
    char c; 
    apellido.clear();

    while (true) {
        c = getch();
        if (isalpha(c)) {
            std::cout << c; 
            apellido += c;  
        } else if (c == 8 && !apellido.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            apellido.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (!apellido.empty()) {
                std::cout << std::endl;
                break; // Salir del bucle si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula
    if (!apellido.empty()) {
        apellido[0] = toupper(apellido[0]);
    }

    return apellido;
}

int ValidarPersona::ingresar_entero(char numero){
    char c;
    while (true) {
        c = getch(); 
        
        if (c >= '1' && c <= numero) {
            std::cout << c << std::endl; // Mostrar el número
            return c - '0'; // Convertir de char a int y retornar
        } 
        else if (c == 13) {
        }
    }
}

int ValidarPersona::ingresar_desplazamiento(int maximo) {
        std::string entrada = ""; // Almacena el número como cadena
        char c;
        while (true) {
            c = getch(); // Leer un carácter sin mostrar en pantalla
            
            // Si es un número, agregarlo a la entrada
            if (c >= '0' && c <= '9') {
                std::cout << c; // Mostrar el número ingresado
                entrada += c;
            } 
            // Si se presiona Enter (código ASCII 13), validar y retornar
            else if (c == 13) {
                std::cout << std::endl; // Salto de línea
                int valor = std::stoi(entrada); // Convertir cadena a entero
                if (valor <= maximo) {
                    return valor; // Retornar si está dentro del rango
                } else {
                    std::cout << "El número excede el máximo permitido (" << maximo << "). Intente de nuevo.\n";
                    entrada = ""; // Reiniciar la entrada
                }
            }
            // Si se presiona una tecla no válida, ignorar
            else {
                std::cout << "\nEntrada no válida. Intente de nuevo.\n";
                entrada = ""; // Reiniciar la entrada
            }
        }
}


char ValidarPersona::leerLetra() {
    char c; // Carácter ingresado
    while (true) {
        c = getch(); // Captura el carácter sin mostrarlo directamente

        // Validar si es una letra (mayúscula o minúscula)
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
            putchar(c); // Mostrar el carácter ingresado
            putchar('\n'); // Simular que el usuario presionó Enter después de la letra
            return c; // Retornar el carácter ingresado
        }

        // Validar si se presionó retroceso
        if (c == '\b' || c == 127) {
            putchar('\b'); // Mover cursor atrás
            putchar(' ');  // Sobrescribir el carácter anterior con un espacio
            putchar('\b'); // Mover el cursor nuevamente atrás
        }

        // Ignorar otros caracteres y continuar esperando entrada
    }
}
