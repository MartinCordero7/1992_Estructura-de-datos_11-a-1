#include "GestorPersonas.h"
#include "Empleado.h"
#include "Fecha.h"
#include "MenuEmpleado.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <cctype>

Empleado* GestorPersonas::ingresarPersona() {
	Validacion miValidador;
	ArbolRadix arbol;
	
    std::string cedula, nombre, apellido, dia, mes, anio, cargo, salario;
    int comprobar;
    comprobar = 1;
	  
	do{
        cedula=miValidador.ingresoCedula();	
        comprobar =	miValidador.buscarCedula(cedula);
	} while (comprobar==0);
	
    nombre=miValidador.ingresoNombre();
    apellido=miValidador.ingresoApellido();
    std::cout <<"\nIngrese los datos de su fecha de Nacimiento:";

    bool fechaValida = false;
    
    while (!fechaValida) {
        dia = miValidador.ingresoDia();
        mes = miValidador.ingresoMes();
        anio = miValidador.ingresoAnio();

        int dias = stoi(dia);
        int mess = stoi(mes);
        int anos = stoi(anio);

        if (mess < 1 || mess > 12) {
            std::cout << "\nFECHA incorrecto. Ingrese nuevamente.";
        } else if (mess == 2) {
            bool esBisiesto = (anos % 4 == 0 && anos % 100 != 0) || (anos % 400 == 0);
            if (dias < 1 || (esBisiesto && dias > 29) || (!esBisiesto && dias > 28))
            {
            std::cout << "\nFECHA incorrecto. Ingrese nuevamente.";
            }
            else
            {
                fechaValida = true;
            }
        } else if ((mess == 4 || mess == 6 || mess == 9 || mess == 11) && (dias < 1 || dias > 30)) {
            std::cout << "\nFECHA incorrecto. Ingrese nuevamente.";
        } else if (dias < 1 || dias > 31) {
            std::cout << "\nFECHA incorrecto. Ingrese nuevamente.";
        } else {
            fechaValida = true;
        }
    }

    Fecha fechaNacimiento;
    fechaNacimiento.setDia(dia);
    fechaNacimiento.setMes(mes);
    fechaNacimiento.setAnio(anio);
    
    MenuEmpleado menuEmpleado(5);
    int opcionSeleccionada = menuEmpleado.operarMenuEmpleado();

    switch (opcionSeleccionada) {
        case 1:
            cargo = "Rector";
            salario = "5000$";
            break;
        case 2:
            cargo = "Vicerrector";
            salario = "4000$";
            break;
        case 3:
            cargo = "Director_de_departamento";
            salario = "3000$";
            break;
        case 4:
            cargo = "Profesor";
            salario = "2500$";
            break;
        case 5:
            cargo = "Personal_administrativo";
            salario = "2000$";
            break;
    }
    system("cls");

    Empleado* empleado = new Empleado(cedula, nombre, apellido, fechaNacimiento, cargo, salario);

    std::ofstream archivo("personas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << cedula << " ";
        archivo << nombre << " ";
        archivo << apellido << " ";
        archivo << dia << "/" << mes << "/" << anio << " ";
        archivo << cargo << " ";
        archivo << salario << "\n";

        archivo.close();
        std::cout << "Persona registrada exitosamente en el archivo personas.txt\n";
    } else {
        std::cerr << "No se pudo abrir el archivo personas.txt para escribir\n";
    }
    return empleado;
}

void GestorPersonas::eliminarPersona(ListaCircularDoble& lista) {
	Validacion miValidador;
    std::string cedula;
    cedula = miValidador.ingresoCedula();

    Empleado* persona = lista.buscarPersona(cedula);
    if (persona == nullptr) {
        std::cout << "Persona no encontrada en la lista.\n";
        return;
    }

    lista.eliminarPersona(persona);

    // Abrir el archivo original en modo lectura
    std::ifstream archivoEntrada("personas.txt");
    if (!archivoEntrada) {
        std::cerr << "No se pudo abrir el archivo personas.txt para leer\n";
        return;
    }

    // Crear un nuevo archivo temporal en modo escritura
    std::ofstream archivoTemp("personas_temp.txt");
    if (!archivoTemp) {
        std::cerr << "No se pudo abrir el archivo personas_temp.txt para escribir\n";
        archivoEntrada.close(); // Cerrar el archivo original antes de salir
        return;
    }

    std::string cedulaArchivo, nombre, apellido, fechaNacimiento, cargo, salario;
    bool eliminado = false;
    while (archivoEntrada >> cedulaArchivo >> nombre >> apellido >> fechaNacimiento >> cargo >> salario) {
        if (cedulaArchivo == persona->getCedula()) {
            eliminado = true; 
        } else {
            archivoTemp << cedulaArchivo << " ";
            archivoTemp << nombre << " ";
            archivoTemp << apellido << " ";
            archivoTemp << fechaNacimiento << " ";
            archivoTemp << cargo << " ";
            archivoTemp << salario << "\n";
        }
    }

    archivoEntrada.close(); // Cerrar el archivo original
    archivoTemp.close(); // Cerrar el archivo temporal

    if (!eliminado) {
        std::cout << "Persona no encontrada en el archivo personas.txt\n";
        // Eliminar el archivo temporal, ya que no se produjo ningún cambio
        std::remove("personas_temp.txt");
        return;
    }

    // Eliminar el archivo original
    if (std::remove("personas.txt") != 0) {
        std::cerr << "Error al eliminar el archivo personas.txt\n";
        return;
    }

    // Renombrar el archivo temporal a personas.txt para reflejar los cambios
    if (std::rename("personas_temp.txt", "personas.txt") != 0) {
        std::cerr << "Error al renombrar el archivo personas_temp.txt a personas.txt\n";
        return;
    }

    std::cout << "Persona eliminada correctamente de la lista y del archivo 'personas.txt'\n";
}

void GestorPersonas::ordenamientoQuickSort() {
    // Leer el archivo de texto
    std::ifstream inputFile("personas.txt");
    std::vector<std::string> cedulas;
    std::string cedula;

    while (std::getline(inputFile, cedula)) {
        cedulas.push_back(cedula);
    }

    // Ordenar las cédulas usando quicksort
    quickSort(cedulas, 0, cedulas.size() - 1);

    // Mostrar las cédulas ordenadas
    std::cout << "Cedulas ordenadas:" << std::endl;
    for (const std::string& cedula : cedulas) {
        std::cout << cedula << std::endl;
    }

    // Cerrar el archivo
    inputFile.close();
}

void GestorPersonas::quickSort(std::vector<std::string>& cedulas, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(cedulas, bajo, alto);
        quickSort(cedulas, bajo, pi - 1);
        quickSort(cedulas, pi + 1, alto);
    }
}

int GestorPersonas::particion(std::vector<std::string>& cedulas, int bajo, int alto) {
    std::string pivote = cedulas[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        if (cedulas[j] < pivote) {
            i++;
            std::swap(cedulas[i], cedulas[j]);
        }
    }
    std::swap(cedulas[i + 1], cedulas[alto]);
    return (i + 1);
}