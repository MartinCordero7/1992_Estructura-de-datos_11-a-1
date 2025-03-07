#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
class Validacion {
public:
    static std::string validarCedula(const std::string& newCedula);
    std::string ingresoCedula();
    int buscarCedula(const std::string& cedulaBuscar);
    std::string ingresoNombre();
    std::string ingresoApellido();
    std::string ingresoDia();
    std::string ingresoMes();
    std::string ingresoAnio();
    
};

#endif // VALIDACION_H
