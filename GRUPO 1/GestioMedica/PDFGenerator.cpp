#include "PDFGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <locale>
#include <codecvt>

// Error handler for Haru PDF
static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << "ERROR: error_no=" << (unsigned int)error_no << 
                 ", detail_no=" << (unsigned int)detail_no << std::endl;
    throw std::runtime_error("Error al generar PDF");
}

// Helper function to remove accent marks from strings
static std::string quitarAcentos(const std::string& texto) {
    std::string resultado = texto;
    
    // Create simple replacement map for accented characters
    const char* caracteresConAcento = "áéíóúÁÉÍÓÚüÜñÑ";
    const char* caracteresSinAcento = "aeiouAEIOUuUnN";
    
    for (size_t i = 0; i < resultado.length(); i++) {
        // Check if the character is outside ASCII range
        if ((unsigned char)resultado[i] > 127) {
            for (size_t j = 0; caracteresConAcento[j]; j++) {
                if (resultado[i] == caracteresConAcento[j]) {
                    resultado[i] = caracteresSinAcento[j];
                    break;
                }
            }
        }
    }
    
    return resultado;
}

// Mock implementation that doesn't require LibHaru
std::vector<PDFGenerator::CitaInfo> PDFGenerator::cargarCitasAceptadas() {
    std::vector<CitaInfo> citas;
    std::ifstream archivo("output/citas_aceptadas.txt");
    
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de citas aceptadas." << std::endl;
        return citas;
    }
    
    std::string linea;
    bool enCita = false;
    CitaInfo citaActual;
    
    while (std::getline(archivo, linea)) {
        if (linea.find("=== RESUMEN DE LA CITA ===") != std::string::npos) {
            if (enCita) {
                citas.push_back(citaActual);
            }
            citaActual = CitaInfo();
            enCita = true;
        } else if (enCita) {
            if (linea.find("Nombre Paciente: ") != std::string::npos) {
                citaActual.nombrePaciente = linea.substr(17);
            } else if (linea.find("Cedula: ") != std::string::npos) {
                citaActual.cedulaPaciente = linea.substr(8);
            } else if (linea.find("Celular: ") != std::string::npos) {
                citaActual.celular = linea.substr(9);
            } else if (linea.find("Genero: ") != std::string::npos) {
                citaActual.genero = linea.substr(8);
            } else if (linea.find("Fecha de Nacimiento: ") != std::string::npos) {
                citaActual.fechaNacimiento = linea.substr(21);
            } else if (linea.find("Tipo de atencion: ") != std::string::npos) {
                citaActual.tipoAtencion = linea.substr(18);
            } else if (linea.find("Especialidad: ") != std::string::npos) {
                citaActual.especialidad = linea.substr(13);
            } else if (linea.find("Fecha de Cita: ") != std::string::npos) {
                citaActual.fechaCita = linea.substr(14);
            } else if (linea.find("Hora de Cita: ") != std::string::npos) {
                citaActual.horaCita = linea.substr(13);
            } else if (linea.find("Doctor Asignado: ") != std::string::npos) {
                citaActual.nombreDoctor = linea.substr(17);
            } else if (linea.find("Cédula Doctor: ") != std::string::npos) {
                citaActual.cedulaDoctor = linea.substr(15);
            } else if (linea.find("Especialidad Doctor: ") != std::string::npos) {
                citaActual.especialidadDoctor = linea.substr(21);
            } else if (linea == "-------------------------") {
                enCita = false;
                citas.push_back(citaActual);
            }
        }
    }
    
    if (enCita) {
        citas.push_back(citaActual);
    }
    
    archivo.close();
    return citas;
}

bool PDFGenerator::generarPDFCitas(const std::string& nombreArchivo) {
    std::vector<CitaInfo> citas = cargarCitasAceptadas();
    
    if (citas.empty()) {
        std::cout << "No hay citas aceptadas para generar el PDF." << std::endl;
        return false;
    }

    try {
        // Inicializar documento PDF
        HPDF_Doc pdf = HPDF_New(error_handler, NULL);
        if (!pdf) {
            std::cerr << "Error al crear el documento PDF." << std::endl;
            return false;
        }

        // Configuración inicial
        HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
        HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE);

        // Obtener fuentes
        HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
        HPDF_Font fontBold = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
        
        // Agregar página de título
        HPDF_Page portada = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(portada, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        HPDF_Page_SetFontAndSize(portada, fontBold, 24);
        
        float height = HPDF_Page_GetHeight(portada);
        float width = HPDF_Page_GetWidth(portada);
        
        // Título central
        HPDF_Page_BeginText(portada);
        const char* titulo = "Informe de Citas Medicas";  // Remove accent mark
        float tw = HPDF_Page_TextWidth(portada, titulo);
        HPDF_Page_TextOut(portada, (width - tw) / 2, height - 100, titulo);
        
        // Subtítulo con fecha actual
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char fechaActual[80];
        strftime(fechaActual, sizeof(fechaActual), "Generado el %d/%m/%Y", now);
        
        HPDF_Page_SetFontAndSize(portada, font, 12);
        tw = HPDF_Page_TextWidth(portada, fechaActual);
        HPDF_Page_TextOut(portada, (width - tw) / 2, height - 130, fechaActual);
        HPDF_Page_EndText(portada);

        // Logo o imagen (simulado con un rectángulo)
        HPDF_Page_SetRGBFill(portada, 0.0, 0.3, 0.6);
        HPDF_Page_Rectangle(portada, (width - 100) / 2, height - 250, 100, 80);
        HPDF_Page_Fill(portada);
        
        // Agregar una página por cada cita
        int numeroCita = 1;
        for (const auto& cita : citas) {
            HPDF_Page page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            
            // Títulos y contenido
            HPDF_Page_SetFontAndSize(page, fontBold, 16);
            std::string tituloCita = "Cita #" + std::to_string(numeroCita++);
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, 50, height - 70, tituloCita.c_str());
            
            // Información de la cita
            HPDF_Page_SetFontAndSize(page, fontBold, 12);
            HPDF_Page_TextOut(page, 50, height - 120, "Informacion del Paciente:"); // Remove accent mark
            HPDF_Page_EndText(page);
            
            // Detalles del paciente
            HPDF_Page_BeginText(page);
            HPDF_Page_SetFontAndSize(page, font, 11);
            
            HPDF_Page_TextOut(page, 70, height - 150, ("Nombre: " + quitarAcentos(cita.nombrePaciente)).c_str());
            HPDF_Page_TextOut(page, 70, height - 170, ("Cedula: " + quitarAcentos(cita.cedulaPaciente)).c_str());
            HPDF_Page_TextOut(page, 70, height - 190, ("Telefono: " + quitarAcentos(cita.celular)).c_str()); // Remove accent mark
            HPDF_Page_TextOut(page, 70, height - 210, ("Genero: " + quitarAcentos(cita.genero)).c_str()); // Remove accent mark
            HPDF_Page_TextOut(page, 70, height - 230, ("Fecha de Nacimiento: " + quitarAcentos(cita.fechaNacimiento)).c_str());
            
            // Detalles de la cita
            HPDF_Page_SetFontAndSize(page, fontBold, 12);
            HPDF_Page_TextOut(page, 50, height - 270, "Detalles de la Cita:");
            HPDF_Page_SetFontAndSize(page, font, 11);
            
            HPDF_Page_TextOut(page, 70, height - 300, ("Tipo de Atencion: " + quitarAcentos(cita.tipoAtencion)).c_str()); // Remove accent mark
            HPDF_Page_TextOut(page, 70, height - 320, ("Especialidad: " + quitarAcentos(cita.especialidad)).c_str());
            HPDF_Page_TextOut(page, 70, height - 340, ("Fecha: " + quitarAcentos(cita.fechaCita)).c_str());
            HPDF_Page_TextOut(page, 70, height - 360, ("Hora: " + quitarAcentos(cita.horaCita)).c_str());
            
            // Detalles del doctor
            HPDF_Page_SetFontAndSize(page, fontBold, 12);
            HPDF_Page_TextOut(page, 50, height - 400, "Medico Asignado:"); // Remove accent mark
            HPDF_Page_SetFontAndSize(page, font, 11);
            
            HPDF_Page_TextOut(page, 70, height - 430, ("Nombre: " + quitarAcentos(cita.nombreDoctor)).c_str());
            HPDF_Page_TextOut(page, 70, height - 450, ("Cedula: " + quitarAcentos(cita.cedulaDoctor)).c_str());
            HPDF_Page_TextOut(page, 70, height - 470, ("Especialidad: " + quitarAcentos(cita.especialidadDoctor)).c_str());
            
            // Pie de página con información adicional
            HPDF_Page_SetFontAndSize(page, font, 8);
            HPDF_Page_TextOut(page, 50, 50, "GestioMedica - Sistema de Gestion de Citas Medicas"); // Remove accent marks
            HPDF_Page_TextOut(page, width - 150, 50, fechaActual);
            
            HPDF_Page_EndText(page);
            
            // Agregar algunos elementos gráficos para mejorar la presentación
            HPDF_Page_SetLineWidth(page, 1);
            HPDF_Page_SetRGBStroke(page, 0.0, 0.3, 0.6);
            HPDF_Page_MoveTo(page, 50, height - 90);
            HPDF_Page_LineTo(page, width - 50, height - 90);
            HPDF_Page_Stroke(page);
            
            // Línea separadora en pie de página
            HPDF_Page_MoveTo(page, 50, 70);
            HPDF_Page_LineTo(page, width - 50, 70);
            HPDF_Page_Stroke(page);
        }

        // Guardar el documento
        std::string rutaCompleta = "output/" + nombreArchivo;
        HPDF_SaveToFile(pdf, rutaCompleta.c_str());
        HPDF_Free(pdf);
        
        std::cout << "PDF generado exitosamente: " << rutaCompleta << std::endl;
        return true;
        
    } catch (std::exception& e) {
        std::cerr << "Error al generar el PDF: " << e.what() << std::endl;
        return false;
    }
}
