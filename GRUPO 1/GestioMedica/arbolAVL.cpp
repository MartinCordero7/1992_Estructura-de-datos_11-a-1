#include "arbolAVL.h"
#include <fstream>
#include <algorithm>

int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

NodoAVL* ArbolAVL::insertarNodo(NodoAVL* nodo, std::string cedula, std::string nombre, std::string tipo, std::string especialidad) {
    if (nodo == nullptr)
        return new NodoAVL(cedula, nombre, tipo, especialidad);

    if (cedula < nodo->cedula)
        nodo->izquierdo = insertarNodo(nodo->izquierdo, cedula, nombre, tipo, especialidad);
    else if (cedula > nodo->cedula)
        nodo->derecho = insertarNodo(nodo->derecho, cedula, nombre, tipo, especialidad);
    else
        return nodo;

    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    // Casos de rotación
    if (balance > 1 && cedula < nodo->izquierdo->cedula)
        return rotacionDerecha(nodo);

    if (balance < -1 && cedula > nodo->derecho->cedula)
        return rotacionIzquierda(nodo);

    if (balance > 1 && cedula > nodo->izquierdo->cedula) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && cedula < nodo->derecho->cedula) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(std::string cedula, std::string nombre, std::string tipo, std::string especialidad) {
    raiz = insertarNodo(raiz, cedula, nombre, tipo, especialidad);
}

NodoAVL* ArbolAVL::buscarNodo(NodoAVL* nodo, std::string cedula) {
    if (nodo == nullptr || nodo->cedula == cedula)
        return nodo;

    if (cedula < nodo->cedula)
        return buscarNodo(nodo->izquierdo, cedula);

    return buscarNodo(nodo->derecho, cedula);
}

bool ArbolAVL::buscar(std::string cedula, std::string& nombre, std::string& tipo, std::string& especialidad) {
    NodoAVL* resultado = buscarNodo(raiz, cedula);
    if (resultado != nullptr) {
        nombre = resultado->nombre;
        tipo = resultado->tipo;
        especialidad = resultado->especialidad;
        return true;
    }
    return false;
}

void ArbolAVL::inordenRec(NodoAVL* nodo) {
    if (nodo != nullptr) {
        inordenRec(nodo->izquierdo);
        std::cout << "Cédula: " << nodo->cedula << " - Nombre: " << nodo->nombre 
                  << " - Tipo: " << nodo->tipo;
        if (!nodo->especialidad.empty()) {
            std::cout << " - Especialidad: " << nodo->especialidad;
        }
        std::cout << std::endl;
        inordenRec(nodo->derecho);
    }
}

void ArbolAVL::inorden() {
    inordenRec(raiz);
}

void ArbolAVL::cargarDatos() {
    // Cargar pacientes
    std::ifstream archivoPacientes("output/pacientes.txt");
    std::string linea;
    std::string nombre, cedula;
    
    while (getline(archivoPacientes, linea)) {
        if (linea.find("Nombre: ") != std::string::npos) {
            nombre = linea.substr(8);
            if (getline(archivoPacientes, linea) && linea.find("Cédula: ") != std::string::npos) {
                cedula = linea.substr(8);
                insertar(cedula, nombre, "paciente");
            }
        }
    }
    archivoPacientes.close();

    // Cargar doctores
    std::ifstream archivoDoctores("output/doctores.txt");
    std::string especialidad;
    
    while (getline(archivoDoctores, linea)) {
        if (linea.find("Nombre: ") != std::string::npos) {
            nombre = linea.substr(8);
            if (getline(archivoDoctores, linea) && linea.find("Cédula: ") != std::string::npos) {
                cedula = linea.substr(8);
                if (getline(archivoDoctores, linea) && linea.find("Especialidad: ") != std::string::npos) {
                    especialidad = linea.substr(13);
                    insertar(cedula, nombre, "doctor", especialidad);
                }
            }
        }
    }
    archivoDoctores.close();
}
