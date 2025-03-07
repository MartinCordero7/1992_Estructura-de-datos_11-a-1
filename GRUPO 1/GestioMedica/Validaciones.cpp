#include "validaciones.h"
#include "persona.h"

bool Validaciones::validarFecha(const string& fecha) {
    regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
    if (!regex_match(fecha, formatoFecha)) {
        cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
        return false;
    }

    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d-%d-%d", &dia, &mes, &anio);

    if (!Fecha::esFechaValida(dia, mes, anio)) {
        cout << "Error: Fecha no valida.\n";
        return false;
    }

    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    if (anio < anioActual || (anio == anioActual && mes < mesActual) || (anio == anioActual && mes == mesActual && dia < diaActual)) {
        cout << "Error: La fecha no puede ser menor a la fecha actual.\n";
        return false;
    }

    return true;
}

bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacio o contener solo espacios.\n";
        return false;
    }
    return true;
}

bool Validaciones::validarTexto(const string& texto, const string& campo) {
    regex formatoTexto(R"([a-zA-ZnNaeiouAEIOU\s]+)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacio o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTexto)) {
        cout << "Error: El campo " << campo << " solo debe contener letras, espacios y caracteres validos en espanol.\n";
        return false;
    }
    return true;
}

bool Validaciones::validarNombre(string& nombre) {
    nombre.clear();
    bool primeraLetra = true;
    
    while (true) {
        char ch = _getch();
        if (ch == 13) { // Enter key
            if (!nombre.empty()) {
                break;
            }
        } else if (ch == 8) { // Backspace key
            if (!nombre.empty()) {
                cout << "\b \b";
                nombre.pop_back();
                if (nombre.empty()) {
                    primeraLetra = true;
                }
            }
        } else if (isalpha(ch) || ch == ' ') {
            if (ch == ' ' && (nombre.empty() || nombre.back() == ' ')) {
                continue; // Evitar espacios dobles o al inicio
            }
            
            if (primeraLetra && ch != ' ') {
                ch = toupper(ch);
                primeraLetra = false;
            } else {
                ch = tolower(ch);
            }
            
            if (ch == ' ') {
                primeraLetra = true;
            }
            
            nombre += ch;
            cout << ch;
        }
    }
    cout << endl;
    
    return !nombre.empty();
}

bool Validaciones::validarTelefonoEcuador(const string& telefono) {
    if (telefono.length() != 10) {
        cout << endl;
        cout << "Error: El numero de telefono debe tener 10 digitos.\n";
        return false;
    }
    
    if (telefono.substr(0, 2) != "09") {
        cout << endl;
        cout << "Error: El numero de telefono debe comenzar con '09'.\n";
        return false;
    }
    
    if (!all_of(telefono.begin(), telefono.end(), ::isdigit)) {
        cout << endl;
        cout << "Error: El numero de telefono debe contener solo digitos.\n";
        return false;
    }
    
    return true;
}

bool Validaciones::validarCedulaEcuatoriana(const string& cedula) {
    if (cedula.length() != 10) return false;

    // Validar los dos primeros dígitos (provincia)
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 0 || provincia > 24) return false;

    // Validar el tercer dígito (menor a 6)
    int tercerDigito = cedula[2] - '0';
    if (tercerDigito < 0 || tercerDigito > 5) return false;

    // Calcular el dígito verificador
    int coeficientes[] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int valor = (cedula[i] - '0') * coeficientes[i];
        if (valor > 9) valor -= 9;
        suma += valor;
    }

    int digitoVerificadorCalculado = (10 - (suma % 10)) % 10;
    int digitoVerificadorReal = cedula[9] - '0';

    return digitoVerificadorCalculado == digitoVerificadorReal;
}

bool Validaciones::validarGenero(const string& genero) {
    if (genero.length() != 1) {
        cout << endl;
        cout << "Error: Debe ingresar solo un caracter (M/F).\n";
        return false;
    }
    char g = toupper(genero[0]);
    if (g != 'M' && g != 'F') {
        cout << endl;
        cout << "Error: El genero debe ser M o F.\n";
        return false;
    }
    return true;
}

string Validaciones::obtenerGenero(const string& prompt) {
    string genero;
    cout << prompt;
    while (true) {
        char ch = _getch();
        if (ch == 13) { // Enter key
            if (!genero.empty() && validarGenero(genero)) {
                cout << endl;
                break;
            } else {
                cout << endl;
                cout << prompt;
                genero.clear();
            }
        } else if (ch == 8) { // Backspace key
            if (!genero.empty()) {
                genero.pop_back();
                cout << "\b \b";
            }
        } else {
            char upperCh = toupper(ch);
            if (upperCh == 'M' || 'F') {
                if (genero.empty()) {
                    genero = upperCh;
                    cout << upperCh;
                }
            }
        }
    }
    return genero;
}

bool Validaciones::validarFechaNacimiento(const string& fechaStr) {
    regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
    if (!regex_match(fechaStr, formatoFecha)) {
        cout <<endl;
        cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
        return false;
    }

    int dia, mes, anio;
    sscanf(fechaStr.c_str(), "%d-%d-%d", &dia, &mes, &anio); // Corregido: agregados los operadores &

    if (!Fecha::esFechaValida(dia, mes, anio)) {
        cout <<endl;
        cout << "Error: Fecha no valida.\n";
        return false;
    }

    // Obtener la fecha actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    // Verificar que la fecha de nacimiento sea anterior a la fecha actual
    if (anio > anioActual || (anio == anioActual && mes > mesActual) || (anio == anioActual && mes == mesActual && dia > diaActual)) {
        cout <<endl;    
        cout << "Error: La fecha de nacimiento no puede ser mayor a la fecha actual.\n";
        return false;
    }

    // Verificar que la fecha de nacimiento no sea mayor a 100 anos
    if (anioActual - anio > 100) {
        cout <<endl;
        cout << "Error: La fecha de nacimiento no puede ser mayor a 100 anos.\n";
        return false;
    }

    // Verificar que el paciente tenga al menos 18 anos
    if (anioActual - anio < 18 || (anioActual - anio == 18 && mesActual < mes) || (anioActual - anio == 18 && mesActual == mes && diaActual < dia)) {
        cout <<endl;
        cout << "Error: El paciente debe tener al menos 18 anos.\n";
        return false;
    }

    return true;
}

bool Validaciones::verificarCitaDuplicada(const vector<Persona>& citas, const string& doctorCedula, const Fecha& fecha, const string& req) {
    for (const auto& cita : citas) {
        if (cita.getCedula() == doctorCedula &&
            cita.getCita().getDia() != 0 &&  // Asumiendo que una fecha válida indica que la cita fue agendada
            cita.getCita().mostrar() == fecha.mostrar() &&  // O bien implementas un operador "==" para Fecha
            cita.getRequerimiento() == req &&
            cita.isCitaAceptada()) {
            return true;  // Ya existe una cita aceptada con los mismos parámetros
        }
    }
    return false;
}

void Validaciones::mostrarCitasDisponibles(const vector<Persona>& citas, const string& doctorCedula) {
    int disponibles = 0;
    for (const auto& cita : citas) {
        // Se asume que la cédula en la cita corresponde al doctor a quien se le asignó la cita.
        if (cita.getCedula() == doctorCedula && !cita.isCitaAceptada()) {
            cout << "Fecha y hora: " << cita.getCita().mostrar() 
                << " | Requerimiento: " << cita.getRequerimiento() << endl;
            disponibles++;
        }
    }
    if (disponibles == 0) {
        cout << "Cero citas disponibles" << endl;
    } else {
        cout << "Total citas disponibles: " << disponibles << endl;
    }
}

bool Validaciones::verificarDoctorRegistrado(const string& cedula) {
    ifstream archivo("output/doctores.txt");
    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Cédula: " + cedula) != string::npos) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

bool Validaciones::verificarCedulaPaciente(const string& cedula) {
    ifstream archivo("output/pacientes.txt");
    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Cédula: " + cedula) != string::npos) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void Validaciones::mostrarCitas(const vector<Fecha>& citas) {
    system("cls");
    cout << "=== MOSTRAR CITAS ===" << endl;
    if (citas.empty()) {
        cout << "No hay citas registradas." << endl;
    } else {
        for (const auto& cita : citas) {
            cout << "Fecha de la cita: " << cita.mostrar() << endl;
        }
    }
    system("pause");
}

void Validaciones::guardarCitas(const vector<Fecha>& citas) {
    system("mkdir output 2> nul");

    // Primero vamos a leer el archivo existente para obtener toda la información de las citas
    ifstream archivoLectura("output/cita.txt");
    vector<string> citasInfo;
    string linea;
    string citaActual;

    if (archivoLectura.is_open()) {
        while (getline(archivoLectura, linea)) {
            if (linea.find("=== RESUMEN DE LA CITA ===") != string::npos) {
                if (!citaActual.empty()) {
                    citasInfo.push_back(citaActual);
                }
                citaActual = linea + "\n";
            } else if (!linea.empty()) {
                citaActual += linea + "\n";
            }
        }
        if (!citaActual.empty()) {
            citasInfo.push_back(citaActual);
        }
        archivoLectura.close();
    }

    // Ahora escribimos la información actualizada
    ofstream archivo("output/cita.txt", ios::trunc);
    if (archivo.is_open()) {
        for (const auto& citaInfo : citasInfo) {
            archivo << citaInfo;
        }
        archivo.close();
        cout << "Citas guardadas correctamente en output/cita.txt" << endl;
    } else {
        cout << "Error al abrir el archivo para guardar las citas." << endl;
    }
    system("pause");
}

string Validaciones::formatearNombre(const string& nombre) {
    if (nombre.empty()) return nombre;
    
    string nombreFormateado = nombre;
    // Primera letra en mayúscula
    nombreFormateado[0] = toupper(nombreFormateado[0]);
    
    // Resto en minúsculas, excepto después de un espacio
    for (size_t i = 1; i < nombreFormateado.length(); i++) {
        if (nombreFormateado[i - 1] == ' ') {
            nombreFormateado[i] = toupper(nombreFormateado[i]);
        } else {
            nombreFormateado[i] = tolower(nombreFormateado[i]);
        }
    }
    
    return nombreFormateado;
}

void Validaciones::guardarPaciente(const string& nombre, const string& cedula, const string& fechaNacimiento, const string& genero, const string& celular) {
    system("mkdir output 2> nul");
    ofstream archivo("output/pacientes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Cédula: " << cedula << endl;
        archivo << "Nombre: " << formatearNombre(nombre) << endl;
        archivo << "Fecha de Nacimiento: " << fechaNacimiento << endl;
        archivo << "Género: " << genero << endl;
        archivo << "Celular: " << celular << endl;
        archivo << "-------------------------" << endl;
        archivo.close();
    }
}

void Validaciones::eliminarCita(vector<Fecha>& citas, string& fechaStr) {
    system("cls");
    cout << "=== ELIMINAR CITA ===" << endl;
    cout << "Ingrese la fecha de la cita a eliminar (DD-MM-YYYY): ";
    cin >> fechaStr;

    // Eliminar de la lista en memoria
    auto it = remove_if(citas.begin(), citas.end(), [&](const Fecha& cita) {
        return cita.mostrar() == fechaStr;
    });

    bool citaEncontrada = (it != citas.end());
    if (citaEncontrada) {
        citas.erase(it, citas.end());
    }

    // También eliminar del archivo
    ifstream archivoEntrada("output/cita.txt");
    ofstream archivoTemporal("output/cita_temp.txt");
    string linea;
    bool eliminando = false;
    
    while (getline(archivoEntrada, linea)) {
        if (linea.find("Fecha de Cita: " + fechaStr) != string::npos) {
            eliminando = true;
            citaEncontrada = true;
            continue;
        }
        
        if (eliminando && linea == "-------------------------") {
            eliminando = false;
            continue; // No escribir la línea de separación
        }
        
        if (!eliminando) {
            archivoTemporal << linea << endl;
        }
    }
    
    archivoEntrada.close();
    archivoTemporal.close();
    
    remove("output/cita.txt");
    rename("output/cita_temp.txt", "output/cita.txt");

    if (citaEncontrada) {
        cout << "Cita eliminada correctamente." << endl;
    } else {
        cout << "No se encontro una cita con esa fecha." << endl;
    }
    system("pause");
}

void Validaciones::mostrarHorariosMatriz(const vector<pair<int, int>>& horarios, int opcionSeleccionada, const string& fechaStr, const vector<pair<int, pair<int, int>>>& horariosOcupados) {
    system("cls");
    cout << "=== HORARIOS DISPONIBLES ===" << endl;
    cout << "Use las flechas para navegar y Enter para seleccionar" << endl << endl;

    const int COLUMNAS = 4;  // Número de columnas para mostrar
    int totalHorarios = horarios.size();
    int filas = (totalHorarios + COLUMNAS - 1) / COLUMNAS;  // Redondeo hacia arriba

    // Cabecera
    cout << "     ";
    for (int i = 0; i < COLUMNAS; i++) {
        cout << "        ";
    }
    cout << endl;

    // Calcular hash de la fecha actual
    hash<string> hasher;
    int fechaHash = hasher(fechaStr);

    // Contenido en formato matriz
    for (int fila = 0; fila < filas; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            int indice = fila * COLUMNAS + col;
            if (indice < totalHorarios) {
                // Verificar si el horario está ocupado
                bool horarioOcupado = false;
                for (const auto& ocupado : horariosOcupados) {
                    if (ocupado.first == fechaHash && 
                        ocupado.second.first == horarios[indice].first && 
                        ocupado.second.second == horarios[indice].second) {
                        horarioOcupado = true;
                        break;
                    }
                }

                string horario;
                if (horarioOcupado) {
                    horario = "   --:--  "; // Horario ocupado
                } else {
                    horario = string(indice == opcionSeleccionada ? "> " : "  ") + 
                            (horarios[indice].first < 10 ? "0" : "") + 
                            to_string(horarios[indice].first) + ":" +
                            (horarios[indice].second < 10 ? "0" : "") + 
                            to_string(horarios[indice].second);
                }
                cout << setw(8) << left << horario << "  ";
            }
        }
        cout << endl;
    }
}

void Validaciones::guardarResumenCita(const string& nombrePaciente, const string& cedula, const string& celular, const string& genero, const string& fechaNacimiento, const string& tipoAtencion, const string& especialidad, const Fecha& fechaCita) {
    system("mkdir output 2> nul");
    ofstream archivo("output/cita.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "=== RESUMEN DE LA CITA ===" << endl;
        archivo << "Nombre Paciente: " << formatearNombre(nombrePaciente) << endl;
        archivo << "Cedula: " << cedula << endl;
        archivo << "Celular: " << celular << endl;
        archivo << "Genero: " << genero << endl;
        archivo << "Fecha de Nacimiento: " << fechaNacimiento << endl;
        archivo << "Tipo de atencion: " << tipoAtencion << endl;
        if (!especialidad.empty()) {
            archivo << "Especialidad: " << especialidad << endl;
        }
        archivo << "Fecha de Cita: " << fechaCita.getDia() << "-" << fechaCita.getMes() << "-" << fechaCita.getAnio() << endl;
        archivo << "Hora de Cita: " << setw(2) << setfill('0') << fechaCita.getHora() << ":" 
               << setw(2) << setfill('0') << fechaCita.getMinuto() << endl;
        archivo << "Estado: Pendiente" << endl;  // Siempre guardar como Pendiente inicialmente
        archivo << "-------------------------" << endl;
        archivo.close();
        cout << "Cita guardada correctamente en output/cita.txt" << endl;
    } else {
        cout << "Error al guardar la cita." << endl;
    }
}

bool Validaciones::verificarTelefonoDuplicado(const string& telefono) {
    // Check in patients file
    ifstream archivoPacientes("output/pacientes.txt");
    if (archivoPacientes.is_open()) {
        string linea;
        while (getline(archivoPacientes, linea)) {
            if (linea.find("Celular: " + telefono) != string::npos) {
                archivoPacientes.close();
                cout << endl << "Error: Este número de celular ya está registrado por otro paciente." << endl;
                return true;
            }
        }
        archivoPacientes.close();
    }
    
    // Check in doctors file - assuming doctors have phone numbers stored too
    ifstream archivoDoctores("output/doctores.txt");
    if (archivoDoctores.is_open()) {
        string linea;
        while (getline(archivoDoctores, linea)) {
            if (linea.find("Celular: " + telefono) != string::npos) {
                archivoDoctores.close();
                cout << endl << "Error: Este número de celular ya está registrado por otro doctor." << endl;
                return true;
            }
        }
        archivoDoctores.close();
    }
    
    return false; // Phone number not found, it's not duplicated
}