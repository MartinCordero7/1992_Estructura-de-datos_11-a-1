#ifndef EXTRAS_H
#define EXTRAS_H
#include <string> 

void createFile();
void createBackup();
void createBackupRegistro();
void createPdfFromText(const std::string& text, const std::string& outputFilePath);
std::string leerArchivoComoString(const std::string& nombreArchivo);

bool cedulaYaRegistradaHoy(const std::string& cedula, bool esSalida);
void registrarHora(const std::string& cedula);

void entradaPersonal();
void salidaPersonal();

#endif // EXTRAS_H