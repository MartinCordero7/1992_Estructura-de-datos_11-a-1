#include "validaciones.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <cctype>
#include <fstream>

std::string Validacion::validarCedula(const std::string& newCedula) {
    std::string cedula;
    char cedulaPares[5];
    char cedulaImpares[5];

    int cedulaParte1[5];
    int cedulaParte2[5];

    int sumaPares = 0;
    int sumaImpares = 0;
    int sumaTotal = 0;
    int digitoVerificador = 0;
    cedula = newCedula;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            cedulaPares[i] = newCedula[i];
            cedulaParte1[i] = std::atoi(&cedulaPares[i]);
            cedulaParte1[i] = cedulaParte1[i] * 2;
            if (cedulaParte1[i] > 9) {
                cedulaParte1[i] = cedulaParte1[i] - 9;
            }
            sumaPares = sumaPares + cedulaParte1[i];
        } else if (i % 2 != 0) {
            cedulaImpares[i] = newCedula[i];
            cedulaParte2[i] = std::atoi(&cedulaImpares[i]);

            if (i != 9) {
                sumaImpares = sumaImpares + cedulaParte2[i];
            }
        }

        if (i == 9) {
            sumaTotal = sumaPares + sumaImpares;
            digitoVerificador = sumaTotal % 10;

            if (digitoVerificador != 0) {
                digitoVerificador = 10 - digitoVerificador;
            }
        }
    }

    if (digitoVerificador == std::atoi(&(newCedula[9]))) {
        std::cout << "\nCedula Valida" << std::endl;
        return cedula;
    } else if (digitoVerificador != std::atoi(&(newCedula[9]))) {
        std::cout << "\nCedula Invalida" << std::endl;
        cedula = "0";
        return cedula;
    }
    
}

std::string Validacion::ingresoCedula() {
    Validacion miValidador;
    std::string cedula;
    
    do {
        cedula = ""; // Limpiamos la cédula al inicio de cada iteración.
        std::cout << "Ingrese el numero de cedula: ";
        char ch;
        while ((ch = getch()) != 13) {
            if (isdigit(ch)) { 
                std::cout << ch;
                cedula += ch;
            } else if (ch == 8 && !cedula.empty()) { 
                std::cout << "\b \b";
                cedula.pop_back(); 
            }
        }
        
        // Si la cédula está vacía, la consideramos inválida inmediatamente.
        if (cedula.empty()) {
            std::cout << "\nCedula Invalida" << std::endl;
            cedula = "0";
        } else {
            // Validamos la cédula.
            cedula = miValidador.validarCedula(cedula);
            if (cedula == "0") {    
            }
        }

        system("pause");
        system("cls");  
    } while (cedula == "0");
    
    return cedula;
}

std::string Validacion::ingresoNombre(){
    std::string nombre = "";
    do {
        std::cout << "Ingrese el nombre: ";
        char chr;
        while ((chr = getch()) != 13) {
            if (isalpha(chr)) {
                chr = std::toupper(chr); 
                std::cout << chr;
                nombre += chr;
            }else if (chr == 8 && !nombre.empty()) { 
                std::cout << "\b \b";
                nombre.pop_back(); 
            }
        }
            
        if (nombre==""){
            nombre = "0";
            std::cout << "\nNombre Invalido" << std::endl;
            
        }
        std::cout << "\n"; 
        system("pause");
        system("cls");  
    } while (nombre == "0");
        
    return nombre;	
}

std::string Validacion::ingresoApellido(){
	std::string apellido = "";
    do {
        std::cout << "Ingrese el apellido: ";
        char cha;
        while ((cha = getch()) != 13) {
            if (isalpha(cha)) { 
                cha = std::toupper(cha); 
                std::cout << cha;
                apellido += cha;
            }else if (cha == 8 && !apellido.empty()) { 
                std::cout << "\b \b";
                apellido.pop_back(); 
            }
        } std::cout << "\n"; 
        
        if (apellido==""){
            apellido = "0";
            std::cout << "\nApellido Invalido" << std::endl;
            
        }
        std::cout << "\n"; 
        system("pause");
        system("cls");  
    } while (apellido == "0");
        
    return apellido;	
}

std::string Validacion::ingresoDia(){
    std::string entero;
    int x;
    
    std::cout << "\nIngrese el dia de nacimiento: ";  
    entero = "";
        char ch;
            while ((ch = getch()) != 13) {
        if (isdigit(ch)) { 
            std::cout << ch;
            entero += ch;
        } else if (ch == 8 && !entero.empty()) { 
            std::cout << "\b \b";
            entero.pop_back(); 
        }
    } 
	x = atoi(entero.c_str());      	
    while (x < 1 || x > 31 ){
        std::cout << "\n||ERROR||Ingrese el dia de nacimiento: ";
        entero = "";
        char ch;
            while ((ch = getch()) != 13) {
        if (isdigit(ch)) { 
            std::cout << ch;
            entero += ch;
        } else if (ch == 8 && !entero.empty()) { 
            std::cout << "\b \b";
            entero.pop_back(); 
        }
    }
    x = atoi(entero.c_str());
}    
    return entero;
}

std::string Validacion::ingresoMes(){
    std::string mes;
    int z;
    std::cout << "\nIngrese el mes de nacimiento: ";  
    mes = "";
        char ca;
            while ((ca = getch()) != 13) {
        if (isdigit(ca)) { 
            std::cout << ca;
            mes += ca;
        } else if (ca == 8 && !mes.empty()) { 
            std::cout << "\b \b";
            mes.pop_back(); 
        }    
    } 
	z = atoi(mes.c_str()); 
	     	
    while (z < 1 || z > 12 ){
    	mes = "";
        std::cout << "\n||ERROR||Ingrese el mes de nacimiento: ";
            while ((ca = getch()) != 13) {
        if (isdigit(ca)) { 
            std::cout << ca;
            mes += ca;
        } else if (ca == 8 && !mes.empty()) { 
            std::cout << "\b \b";
            mes.pop_back(); 
        }
    }
    z = atoi(mes.c_str());}  
	  
    return mes;
}

std::string Validacion::ingresoAnio(){
    std::string anio;
    int y;
    std::cout << "\nIngrese el anio de nacimiento: ";  
    anio = "";
        char c;
            while ((c = getch()) != 13) {
        if (isdigit(c)) { 
            std::cout << c;
            anio += c;
        } else if (c == 8 && !anio.empty()) { 
            std::cout << "\b \b";
            anio.pop_back(); 
        }    
    } 
	y = atoi(anio.c_str());
	      	
    while (y < 1950 || y > 2023 ){
    	anio = "";
        std::cout << "\n||ERROR||Ingrese el anio de nacimiento: ";
            while ((c = getch()) != 13) {
        if (isdigit(c)) { 
            std::cout << c;
            anio += c;
        } else if (c == 8 && !anio.empty()) { 
            std::cout << "\b \b";
            anio.pop_back(); 
        }
    }
    y = atoi(anio.c_str());}   
	 
    return anio;
}

int Validacion::buscarCedula(const std::string& cedulaBuscar) {
    std::ifstream archivoEntrada("personas.txt");
    std::string cedulaArchivo, nombre, apellido, fechaNacimiento, cargo, salario;

    while (archivoEntrada >> cedulaArchivo >> nombre >> apellido >> fechaNacimiento >> cargo >> salario) {
        if (cedulaArchivo == cedulaBuscar) {
        	std::cout << "\n||ERROR||Cedula existente\n";
            archivoEntrada.close();
            return 0; 
        }
    }

    archivoEntrada.close();
    return 1;
}
