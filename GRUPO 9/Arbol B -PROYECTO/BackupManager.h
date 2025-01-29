/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Gestionar Backups                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>
#include "ArbolBTree.h"

class BackupManager {
public:
    // Métodos públicos de la clase
    static void crearCarpetaSiNoExiste(const std::string& ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta);
    static void restaurarBackup(ArbolBTree& arbol);
};

#endif // BACKUPMANAGER_H
