/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Backup para restaurar datos                                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>
#include "ListaCircular.h"

class BackupManager {
public:
    // Métodos públicos de la clase
    static void crearCarpetaSiNoExiste(const std::string& ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta);
    static void restaurarBackup(ListaCircular& lista);
};

#endif // BACKUPMANAGER_H
