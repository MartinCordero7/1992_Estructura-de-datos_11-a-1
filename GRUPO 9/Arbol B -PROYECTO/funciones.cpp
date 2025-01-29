/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo de funciones.cpp                                 *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // Para std::setw y std::left
#include <set> // Include set
#include <algorithm> // Include sort
#include <tuple> // Include tie
#include "ArbolBTree.h"

using namespace std;

// Función para dividir una línea por un delimitador
vector<string> dividir(const std::string& linea, char delimitador) {
    try {
        vector<string> partes;
        stringstream ss(linea);
        string parte;
        while (getline(ss, parte, delimitador)) {
            partes.push_back(parte);
        }
        return partes;
    } catch (const exception& e) {
        cerr << "Error al dividir la linea: " << e.what() << endl;
        return {};
    }
}

// Función para imprimir la cabecera formateada
void imprimirCabecera() {
    try {
        cout << left;
        cout << setw(40) << "Título"
            << setw(25) << "Autor"
            << setw(22) << "ISNI"
            << setw(20) << "ISBN"
            << setw(15) << "Publicación"
            << "Nac. Autor" << endl;

        cout << string(120, '-') << endl; // Línea divisoria
        cout << "\n";
    } catch (const exception& e) {
        cerr << "Error al imprimir la cabecera: " << e.what() << endl;
    }
}

// Función para buscar registros en un rango de años
void buscarPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    try {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        string linea;
        // Lambda para verificar si el año está en el rango
        auto filtrarPorRango = [anioInicio, anioFin](const string& fecha) {
            int anioPublicacion = stoi(fecha.substr(fecha.size() - 4));
            return anioPublicacion >= anioInicio && anioPublicacion <= anioFin;
        };

        bool cabeceraImprimida = false;
        bool librosEncontrados = false;

        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                string titulo = campos[0];
                string autor = campos[1];
                string isni = campos[2];
                string fechaNacimiento = campos[3];
                string isbn = campos[4];
                string fechaPublicacion = campos[5];

                // Usamos la lambda para filtrar
                if (filtrarPorRango(fechaPublicacion)) {
                    if (!cabeceraImprimida) {
                        imprimirCabecera();
                        cabeceraImprimida = true;
                    }

                    // Imprimimos el registro formateado
                    cout << left;
                    cout << setw(40) << titulo
                        << setw(25) << autor
                        << setw(22) << isni
                        << setw(20) << isbn
                        << setw(15) << fechaPublicacion
                        << fechaNacimiento << endl;

                    librosEncontrados = true;
                }
            }
        }

        if (!librosEncontrados) {
            cout << "No existen libros registrados entre " << anioInicio << " y " << anioFin << "." << endl;
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Error al buscar por rango: " << e.what() << endl;
    }
}

void distribuirDatos(const string& archivoEntrada) {
    try {
        ifstream archivo(archivoEntrada);
        if (!archivo.is_open() || archivo.peek() == ifstream::traits_type::eof()) {
            cerr << "No existe datos en " << archivoEntrada << " o el archivo no existe." << endl;
            // Eliminar o vaciar el archivo libros_ordenados.txt
            ofstream archivoOrdenado("libros_ordenados.txt", ofstream::trunc);
            archivoOrdenado.close();

            // Eliminar las cubetas si existen
            for (int i = 0; i < 26; ++i) {
                string nombreArchivo = "cubeta_" + string(1, 'A' + i) + ".txt";
                if (remove(nombreArchivo.c_str()) != 0 && errno != ENOENT) {
                    cerr << "Error al eliminar el archivo " << nombreArchivo << endl;
                }
            }
            return;
        }

        vector<string> archivosCubetas(26);
        for (int i = 0; i < 26; ++i) {
            archivosCubetas[i] = "cubeta_" + string(1, 'A' + i) + ".txt";
            if (remove(archivosCubetas[i].c_str()) != 0 && errno != ENOENT) {
                cerr << "Error al eliminar el archivo " << archivosCubetas[i] << endl;
            }
        }

        string linea;
        set<string> datosUnicos;
        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                string titulo = campos[0];
                if (datosUnicos.insert(linea).second) {
                    int indice = toupper(titulo[0]) - 'A';
                    ofstream cubeta(archivosCubetas[indice], ios::app);
                    if (cubeta.is_open()) {
                        cubeta << linea << endl;
                    }
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error al distribuir datos: " << e.what() << endl;
    }
}

void ordenarArchivo(const string& nombreArchivo) {
    try {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) return;

        vector<string> lineas;
        string linea;
        while (getline(archivo, linea)) {
            lineas.push_back(linea);
        }
        archivo.close();

        sort(lineas.begin(), lineas.end(), [](const string& a, const string& b) {
            vector<string> camposA = dividir(a, ';');
            vector<string> camposB = dividir(b, ';');
            return tie(camposA[0], camposA[4]) < tie(camposB[0], camposB[4]);
        });

        ofstream archivoOrdenado(nombreArchivo);
        for (const auto& linea : lineas) {
            archivoOrdenado << linea << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al ordenar archivo: " << e.what() << endl;
    }
}

void fusionarArchivos(const string& archivoSalida) {
    try {
        ofstream archivo(archivoSalida);
        if (!archivo.is_open()) return;

        for (char i = 'A'; i <= 'Z'; ++i) {
            string nombreArchivo = "cubeta_" + string(1, i) + ".txt";
            ifstream cubeta(nombreArchivo);
            if (cubeta.is_open()) {
                string linea;
                while (getline(cubeta, linea)) {
                    archivo << linea << endl;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error al fusionar archivos: " << e.what() << endl;
    }
}

void mostrarArchivo(const string& nombreArchivo) {
    try {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "El archivo " << nombreArchivo << " no existe." << endl;
            return;
        }

        if (archivo.peek() == ifstream::traits_type::eof()) {
            cerr << "No hay datos en " << nombreArchivo << "." << endl;
            return;
        }

        cout << std::left << std::setw(41) << "Título"
             << std::setw(25) << "Autor"
             << std::setw(25) << "ISNI"
             << std::setw(20) << "ISBN"
             << std::setw(15) << "Publicación"
             << std::setw(15) << "Nac. Autor" << std::endl;
        cout << std::string(140, '-') << std::endl;

        string linea;
        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                cout << std::left << std::setw(40) << campos[0]
                     << std::setw(25) << campos[1]
                     << std::setw(25) << campos[2]
                     << std::setw(20) << campos[4]
                     << std::setw(15) << campos[5]
                     << std::setw(15) << campos[3] << std::endl;
            }
        }
    } catch (const exception& e) {
        cerr << "Error al mostrar archivo: " << e.what() << endl;
    }
}

void eliminarDeCubeta(const string& titulo) {
    try {
        char primeraLetra = toupper(titulo[0]);
        string nombreCubeta = "cubeta_" + string(1, primeraLetra) + ".txt";
        ifstream cubeta(nombreCubeta);
        if (cubeta.is_open()) {
            vector<string> lineas;
            string linea;
            while (getline(cubeta, linea)) {
                if (linea.find(titulo) == string::npos) {
                    lineas.push_back(linea);
                }
            }
            cubeta.close();

            if (lineas.empty()) {
                remove(nombreCubeta.c_str());
            } else {
                ofstream cubeta(nombreCubeta, ofstream::trunc);
                for (const auto& l : lineas) {
                    cubeta << l << endl;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error al eliminar del archivo de cubeta: " << e.what() << endl;
    }
}

void buscarAutoresPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    try {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        vector<tuple<string, string, string, string, string, string>> registros;
        string linea;
        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                registros.emplace_back(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5]);
            }
        }
        archivo.close();

        sort(registros.begin(), registros.end(), [](const auto& a, const auto& b) {
            return get<3>(a) < get<3>(b); // Ordenar por fecha de nacimiento
        });

        auto itInicio = lower_bound(registros.begin(), registros.end(), anioInicio, [](const auto& registro, int anio) {
            return stoi(get<3>(registro).substr(get<3>(registro).size() - 4)) < anio;
        });

        auto itFin = lower_bound(registros.begin(), registros.end(), anioFin + 1, [](const auto& registro, int anio) {
            return stoi(get<3>(registro).substr(get<3>(registro).size() - 4)) < anio;
        });

        if (itInicio == registros.end() || itInicio == itFin) {
            cout << "No existen autores nacidos entre " << anioInicio << " y " << anioFin << "." << endl;
            return;
        }

        imprimirCabecera();
        for (auto it = itInicio; it != itFin; ++it) {
            cout << left;
            cout << setw(40) << get<0>(*it)
                << setw(25) << get<1>(*it)
                << setw(22) << get<2>(*it)
                << setw(20) << get<4>(*it)
                << setw(15) << get<5>(*it)
                << get<3>(*it) << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al buscar autores por rango: " << e.what() << endl;
    }
}

void buscarPorTitulo(const string& rutaArchivo, const string& titulo) {
    try {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        vector<tuple<string, string, string, string, string, string>> registros;
        string linea;
        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                registros.emplace_back(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5]);
            }
        }
        archivo.close();

        sort(registros.begin(), registros.end(), [](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b); // Ordenar por título
        });

        auto it = lower_bound(registros.begin(), registros.end(), titulo, [](const auto& registro, const string& titulo) {
            return get<0>(registro) < titulo;
        });

        if (it == registros.end() || get<0>(*it) != titulo) {
            cout << "No se encontraron libros con el título: " << titulo << "." << endl;
            return;
        }

        imprimirCabecera();
        for (auto it2 = it; it2 != registros.end() && get<0>(*it2) == titulo; ++it2) {
            cout << left;
            cout << setw(40) << get<0>(*it2)
                << setw(25) << get<1>(*it2)
                << setw(22) << get<2>(*it2)
                << setw(20) << get<4>(*it2)
                << setw(15) << get<5>(*it2)
                << get<3>(*it2) << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al buscar por título: " << e.what() << endl;
    }
}

void buscarAutoresPorCaracter(const std::string& rutaArchivo, char caracter) {
    try {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        vector<tuple<string, string, string, string, string, string>> registros;
        string linea;
        while (getline(archivo, linea)) {
            vector<string> campos = dividir(linea, ';');
            if (campos.size() >= 6) {
                registros.emplace_back(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5]);
            }
        }
        archivo.close();

        sort(registros.begin(), registros.end(), [](const auto& a, const auto& b) {
            return get<1>(a) < get<1>(b); // Ordenar por nombre del autor
        });

        caracter = toupper(caracter); // Convertir el carácter a mayúscula

        auto it = lower_bound(registros.begin(), registros.end(), caracter, [](const auto& registro, char caracter) {
            return toupper(get<1>(registro)[0]) < caracter;
        });

        if (it == registros.end() || toupper(get<1>(*it)[0]) != caracter) {
            cout << "No se encontraron autores que comiencen con la letra: " << caracter << "." << endl;
            return;
        }

        imprimirCabecera();
        for (auto it2 = it; it2 != registros.end() && toupper(get<1>(*it2)[0]) == caracter; ++it2) {
            cout << left;
            cout << setw(40) << get<0>(*it2)
                << setw(25) << get<1>(*it2)
                << setw(22) << get<2>(*it2)
                << setw(20) << get<4>(*it2)
                << setw(15) << get<5>(*it2)
                << get<3>(*it2) << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al buscar autores por caracter: " << e.what() << endl;
    }
}