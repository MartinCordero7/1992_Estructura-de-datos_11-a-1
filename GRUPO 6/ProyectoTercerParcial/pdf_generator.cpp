/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * Proposito:          Crear PDFs a partir de un archivo .txt de entregas
 * Autor:              Abner Arboleda, Christian Acuña, Christian Bonifaz
 * Fecha de creacion:  01/12/2024
 * Fecha de modificacion: 08/11/2024
 * Materia:            Estructura de datos
 * NRC :               1992
 ********************************************************************************************/

#include "pdf_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "hpdf.h"

using namespace std;

// Función para dividir una línea por el delimitador ';'
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void createPDF(const std::string& inputFile) {
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        cerr << "Error al crear el PDF" << endl;
        return;
    } 

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 10);

    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        HPDF_Free(pdf);
        return;
    }

    float yPosition = 750;
    float xPosition = 50;

    // Actualizar títulos de columnas para incluir celular
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, xPosition, yPosition, "Cliente");
    HPDF_Page_TextOut(page, xPosition + 120, yPosition, "Cedula");
    HPDF_Page_TextOut(page, xPosition + 200, yPosition, "Celular");  // Nueva columna
    HPDF_Page_TextOut(page, xPosition + 300, yPosition, "Zona");
    HPDF_Page_EndText(page);

    yPosition -= 20;
    HPDF_Page_MoveTo(page, xPosition, yPosition);
    HPDF_Page_LineTo(page, xPosition + 500, yPosition);
    HPDF_Page_Stroke(page);

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (line.empty()) continue;

        vector<string> fields = split(line, ';');

        // Escribir campos incluyendo el celular
        yPosition -= 20;
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, xPosition, yPosition, fields.size() > 0 ? fields[0].c_str() : "");
        HPDF_Page_TextOut(page, xPosition + 120, yPosition, fields.size() > 1 ? fields[1].c_str() : "");
        HPDF_Page_TextOut(page, xPosition + 200, yPosition, fields.size() > 2 ? fields[2].c_str() : ""); // Celular
        HPDF_Page_TextOut(page, xPosition + 300, yPosition, fields.size() > 3 ? fields[3].c_str() : ""); // Zona
        HPDF_Page_EndText(page);

        if (yPosition < 100) {
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 10);
            yPosition = 750;
        }
    }

    file.close();
    HPDF_SaveToFile(pdf, "entregas.pdf");
    HPDF_Free(pdf);
    
    cout << "PDF generado correctamente como 'entregas.pdf'" << endl;
}