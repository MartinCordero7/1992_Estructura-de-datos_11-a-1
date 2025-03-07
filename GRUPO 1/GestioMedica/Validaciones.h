#pragma once
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <ctime>
#include <cctype>
#include <sstream>
#include <vector>
#include "fecha.h"
#include "persona.h"

using namespace std;

class Validaciones {
public:
    static bool validarFecha(const string& fecha);
    static bool validarTextoNoVacio(const string& texto, const string& campo);
    static bool validarTexto(const string& texto, const string& campo);
    static bool validarNombre(string& nombre);
    static bool validarTelefonoEcuador(const string& telefono);
    static bool verificarTelefonoDuplicado(const string& telefono); // New function
    static bool validarCedulaEcuatoriana(const string& cedula);
    static bool validarGenero(const string& genero);
    static bool validarFechaNacimiento(const string& fechaStr);
    static bool verificarCitaDuplicada(const vector<Persona>& citas, const string& doctorCedula, const Fecha& fecha, const string& req);
    static void mostrarCitasDisponibles(const vector<Persona>& citas, const string& doctorCedula);
    static bool verificarDoctorRegistrado(const string& cedula);
    static bool verificarCedulaPaciente(const string& cedula);
    static void mostrarCitas(const vector<Fecha>& citas);
    static void guardarCitas(const vector<Fecha>& citas); // Revertir a vector<Fecha>
    static void eliminarCita(vector<Fecha>& citas, string& fechaStr);
    static void mostrarHorariosMatriz(const vector<pair<int, int>>& horarios, int opcionSeleccionada, const string& fechaStr, const vector<pair<int, pair<int, int>>>& horariosOcupados);
    static string obtenerGenero(const string& prompt);
    static void guardarPaciente(const string& nombre, const string& cedula, const string& fechaNacimiento, const string& genero, const string& celular);
    static void guardarResumenCita(const string& nombrePaciente, const string& cedula, const string& celular, const string& genero, const string& fechaNacimiento, const string& tipoAtencion, const string& especialidad, const Fecha& fechaCita);
    static string formatearNombre(const string& nombre);
};

#endif // VALIDACIONES_H

#include "validaciones.h"
