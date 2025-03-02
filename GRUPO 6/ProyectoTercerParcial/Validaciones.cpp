/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Validaciones de entrada de datos                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "Validaciones.h"


bool Validaciones::validarNombreCliente(const string& nombre) {
    // Regex para validar nombre: primera letra mayúscula, resto minúsculas, sin números ni espacios
    regex formatoNombre("^[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+$");
    
    if (nombre.empty()) {
        cout << "Error: El nombre no puede estar vacío.\n";
        return false;
    }
    
    if (!regex_match(nombre, formatoNombre)) {
        cout << "Error: El nombre debe comenzar con mayúscula y el resto en minúsculas, sin números ni espacios.\n";
        return false;
    }
    
    return true;
}

bool Validaciones::validarCedulaEcuatoriana(const string& cedula) {
    // Verificar longitud
    if (cedula.length() != 10) {
        cout << "Error: La cédula debe tener 10 dígitos.\n";
        return false;
    }
    
    // Verificar que sean solo números
    if (!all_of(cedula.begin(), cedula.end(), ::isdigit)) {
        cout << "Error: La cédula solo debe contener números.\n";
        return false;
    }
    
    // Verificar provincia (primeros dos dígitos)
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) {
        cout << "Error: Código de provincia inválido.\n";
        return false;
    }
    
    // Verificar tercer dígito
    int tercerDigito = cedula[2] - '0';
    if (tercerDigito < 0 || tercerDigito > 5) {
        cout << "Error: Tercer dígito inválido.\n";
        return false;
    }
    
    return verificarDigitoVerificadorCedula(cedula);
}

bool Validaciones::verificarDigitoVerificadorCedula(const string& cedula) {
    int suma = 0;
    int digitoVerificador = cedula[9] - '0';
    
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }
    
    int verificador = (10 - (suma % 10)) % 10;
    
    if (verificador != digitoVerificador) {
        cout << "Error: Dígito verificador inválido.\n";
        return false;
    }
    
    return true;
}

bool Validaciones::validarNumeroCelular(const string& celular) {
    // Regex para validar número celular ecuatoriano
    regex formatoCelular("^(09)[0-9]{8}$");
    
    if (celular.empty()) {
        cout << "Error: El número de celular no puede estar vacío.\n";
        return false;
    }
    
    if (!regex_match(celular, formatoCelular)) {
        cout << "Error: El número debe comenzar con '09' y tener 10 dígitos en total.\n";
        return false;
    }
    
    return true;
}