#include "extras.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <sstream>
#include <string>
#include <chrono>
#include "validaciones.h"

void createBackupFolder(const std::string& folderName) {
    if (mkdir(folderName.c_str()) == 0) {
        std::cout << "Carpeta '" << folderName << "' creada exitosamente.\n";
    } else {
        std::cout << "La carpeta'" << folderName << "' ya existe\n";
    }
}

void createBackup() {
    // Obtener la fecha actual del sistema
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);

    // Crear una cadena con el formato de la fecha para usar como nombre del archivo de respaldo
    char nombreBackup[100];
    std::strftime(nombreBackup, sizeof(nombreBackup), "%Y-%m-%d_%H-%M-%S", fechaActual);

    // Crear la carpeta de respaldo
    createBackupFolder("backup");

    // Copiar el archivo a la carpeta de respaldo con el nombre de la fecha del sistema
    std::ifstream srcFile("personas.txt", std::ios::binary);
    std::ofstream dstFile("backup/" + std::string(nombreBackup) + ".txt", std::ios::binary);
    dstFile << srcFile.rdbuf();

    std::cout << "Se realizo una copia de seguridad en la carpeta 'backup'.\n";
}


void createBackupRegistro() {
    // Obtener la fecha actual del sistema
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);

       // Obtener el tiempo actual
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Aumentar un segundo
    now_time++;

    // Convertir el tiempo incrementado a struct tm
    struct std::tm *incremented_time = std::localtime(&now_time);

    // Crear una cadena con el formato de fecha deseado
    char nombreBackup[100];
    std::strftime(nombreBackup, sizeof(nombreBackup), "%Y-%m-%d_%H-%M-%S", incremented_time);


    // Crear la carpeta de respaldo
    createBackupFolder("backup");

    // Copiar el archivo a la carpeta de respaldo con el nombre de la fecha del sistema
    std::ifstream srcFile("registro.txt", std::ios::binary);
    std::ofstream dstFile("backup/" + std::string(nombreBackup) + ".txt", std::ios::binary);
    dstFile << srcFile.rdbuf();

    std::cout << "Se realizo una copia de seguridad en la carpeta 'backup'.\n";
}


void createPdfFromText(const std::string& text, const std::string& outputFilePath) {
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    // Encabezado del PDF
    outputFile << "%PDF-1.4\n%\xC2\xB5\xC3\xB4\n";

    // Contenido del PDF
    outputFile << "1 0 obj\n"
               << "<< /Type /Catalog\n"
               << "/Pages 2 0 R\n"
               << ">>\n"
               << "endobj\n"
               << "2 0 obj\n"
               << "<< /Type /Pages\n"
               << "/Kids [3 0 R]\n"
               << "/Count 1\n"
               << ">>\n"
               << "endobj\n"
               << "3 0 obj\n"
               << "<< /Type /Page\n"
               << "/Parent 2 0 R\n"
               << "/Resources\n"
               << "<< /Font\n"
               << "<< /F1\n"
               << "<< /Type /Font\n"
               << "/Subtype /Type1\n"
               << "/BaseFont /Helvetica\n"
               << ">>\n"
               << ">>\n"
               << ">>\n"
               << "/MediaBox [0 0 612 792]\n"
               << "/Contents 4 0 R\n"
               << ">>\n"
               << "endobj\n"
               << "4 0 obj\n"
               << "<< /Length 59 >>\n"
               << "stream\n"
               << "BT\n"
               << "/F1 12 Tf\n"
               << "72 720 Td\n"
               << "(" << text << ") Tj\n"
               << "ET\n"
               << "endstream\n"
               << "endobj\n"
               << "xref\n"
               << "0 5\n"
               << "0000000000 65535 f \n"
               << "0000000018 00000 n \n"
               << "0000000077 00000 n \n"
               << "0000000178 00000 n \n"
               << "0000000272 00000 n \n"
               << "trailer\n"
               << "<<\n"
               << "/Size 5\n"
               << "/Root 1 0 R\n"
               << ">>\n"
               << "startxref\n"
               << "398\n"
               << "%%EOF\n";

    outputFile.close();
}

std::string leerArchivoComoString(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::stringstream contenido;

    if (archivo.is_open()) {
        contenido << archivo.rdbuf(); 
        archivo.close();
        return contenido.str(); 
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para leer\n";
        return "";
    }
}




bool cedulaYaRegistradaHoy(const std::string& cedula, bool esSalida) {
    std::ifstream registro("registro.txt");
    if (registro.is_open()) {
        std::string linea;
        while (std::getline(registro, linea)) {
            if (linea.find(cedula) != std::string::npos) {
                time_t now = time(0);
                tm* timeinfo = localtime(&now);
                char fechaActual[11];
                strftime(fechaActual, sizeof(fechaActual), "%Y-%m-%d", timeinfo);
                if (linea.find(fechaActual) != std::string::npos) {
                    if ((esSalida && linea.find("Hora de salida") != std::string::npos) ||
                        (!esSalida && linea.find("Hora de registro") != std::string::npos)) {
                        return true;
                    }
                }
            }
        }
        registro.close();
    }
    return false;
}

void registrarHora(const std::string& cedula) {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    std::ofstream registro("registro.txt", std::ios::app);
    if (registro.is_open()) {
        registro << "Cédula: " << cedula << ", Hora de registro: " << buffer << std::endl;
        std::cout << "Registro de hora exitoso.\n";
        registro.close();
    } else {
        std::cerr << "Error al abrir el archivo de registro.\n";
    }
}

std::string leerCedulaDesdeArchivo() {
    std::string cedula;
    std::ifstream personasFile("personas.txt");
    if (personasFile.is_open()) {
        std::getline(personasFile, cedula);
        personasFile.close();
    } else {
        std::cerr << "Error al abrir el archivo de personas.\n";
    }
    return cedula;
}


void entradaPersonal() {
    Validacion miValidador;
    std::cout << "====== ENTRADA ======\n";
    std::string cedula;
    cedula = miValidador.ingresoCedula();

    std::ifstream personasFile("personas.txt");
    bool cedulaEncontrada = false;
    if (personasFile.is_open()) {
        std::string linea;
        while (std::getline(personasFile, linea)) {
            if (linea.find(cedula) != std::string::npos) {
                cedulaEncontrada = true;
                break;
            }
        }
        personasFile.close();
    } else {
        std::cerr << "Error al abrir el archivo de personas.\n";
        return;
    }

    if (cedulaEncontrada) {
        if (cedulaYaRegistradaHoy(cedula, false)) {
            std::cout << "La cedula ya ha registrado la hora de entrada hoy.\n";
        } else {
            registrarHora(cedula);
        }
    } else {
        std::cerr << "La cedula ingresada no se encuentra en el archivo 'personas.txt'.\n";
    }
   
}

void salidaPersonal() {
    Validacion miValidador;
    std::cout << "====== SALIDA ======\n";
    std::string cedula;
    cedula = miValidador.ingresoCedula();

    std::ifstream personasFile("personas.txt");
    bool cedulaEncontrada = false;
    if (personasFile.is_open()) {
        std::string linea;
        while (std::getline(personasFile, linea)) {
            if (linea.find(cedula) != std::string::npos) {
                cedulaEncontrada = true;
                break;
            }
        }
        personasFile.close();
    } else {
        std::cerr << "Error al abrir el archivo de personas.\n";
        return;
    }

    if (cedulaEncontrada) {
        if (cedulaYaRegistradaHoy(cedula, true)) {
            std::cout << "La cedula ya ha registrado la hora de salida hoy.\n";
        } else {
            if (!cedulaYaRegistradaHoy(cedula, false)) {
                std::cout << "Primero debe registrar la hora de entrada antes de registrar la hora de salida.\n";
            } else {
                registrarHora(cedula + " - Hora de salida");
            }
        }
    } else {
        std::cerr << "La cedula ingresada no se encuentra en el archivo 'personas.txt'.\n";
    }
   
}


