#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>
#include <vector>
#include "LibPDF/hpdf.h"

class PDFGenerator {
private:
    struct CitaInfo {
        std::string nombrePaciente;
        std::string cedulaPaciente;
        std::string celular;
        std::string genero;
        std::string fechaNacimiento;
        std::string fechaCita;
        std::string horaCita;
        std::string tipoAtencion;
        std::string especialidad;
        std::string nombreDoctor;
        std::string cedulaDoctor;
        std::string especialidadDoctor;
    };

    static std::vector<CitaInfo> cargarCitasAceptadas();

public:
    static bool generarPDFCitas(const std::string& nombreArchivo);
};

#endif // PDF_GENERATOR_H
