#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include "fecha.cpp"
#include "validaciones.cpp"
#include "persona.cpp"
#include "lista.cpp"
#include "arbolAVL.cpp"
#include "PDFGenerator.h" // Add the new header


using namespace std;

class Menu {
    
private:
    int opcionSeleccionada;
    vector<Fecha> citas;
    const vector<string> especialidades = {
        "General", "Pediatria", "Geriatria", "Medicina Interna", "Cardiologia", "Neumologia",
        "Gastroenterologia", "Neurologia", "Ginecologia y Obstetricia", "Neonatologia",
        "Medicina Materno-Fetal", "Otorrinolaringologia", "Oftalmologia", "Audiologia",
        "Radiologia", "Patologia Clinica", "Medicina Nuclear", "Anatomia Patologica",
        "Psiquiatria", "Psicologia", "Neuropsiquiatria", "Medicina Fisica y Rehabilitacion",
        "Terapia del Dolor", "Fisioterapia", "Dermatologia", "Medicina Estetica",
        "Odontologia General", "Ortodoncia", "Endodoncia", "Periodoncia", "Implantologia"
    };

    // Agregar un nuevo atributo para almacenar horarios ocupados
    vector<pair<int, pair<int, int>>> horariosOcupados; // {fecha_str_hash, {hora, minuto}}

    // Nueva estructura para rastrear horarios ocupados por especialidad
    struct HorarioOcupado {
        string especialidad;
        int fechaHash;
        int hora;
        int minuto;
    };
    vector<HorarioOcupado> horariosOcupadosEspecialidad;

    // Eliminar el vector de doctoresRegistrados y agregar funciones para manejar archivo
    
    void guardarDoctor(const Persona& doctor) {
        system("mkdir output 2> nul");
        ofstream archivo("output/doctores.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Nombre: " << doctor.getNombre() << endl;
            archivo << "Cédula: " << doctor.getCedula() << endl;
            archivo << "Especialidad: " << doctor.getRequerimiento() << endl;
            archivo << "Celular: " << doctor.getCelular() << endl; // Add this line
            archivo << "-------------------------" << endl;
            archivo.close();
            cout << "Doctor registrado correctamente en el archivo." << endl;
        } else {
            cout << "Error al abrir el archivo de doctores." << endl;
        }
    }

    string obtenerEspecialidadDoctor(const string& cedula) {
        ifstream archivo("output/doctores.txt");
        if (!archivo.is_open()) {
            return "";
        }

        string linea;
        bool encontrado = false;
        while (getline(archivo, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                continue;
            }
            if (encontrado && linea.find("Especialidad: ") != string::npos) {
                archivo.close();
                return linea.substr(13); // Extraer solo la especialidad
            }
        }
        archivo.close();
        return "";
    }

    // Funcion para colorear el texto (opcional)
    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    // Funcion para mostrar el menu principal
    void mostrarMenuPrincipal() {
        system("cls");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Administrador" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Doctor" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Paciente" << endl;
        cout << (opcionSeleccionada == 3 ? "> " : "  ") << "4. Salir" << endl;
    }

    // Funcion para mostrar el menu del administrador
    void mostrarMenuAdministrador() {
        system("cls");
        cout << "=== MENU ADMINISTRADOR ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Eliminar informacion" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Modificar informacion" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Generar respaldo" << endl;
        cout << (opcionSeleccionada == 3 ? "> " : "  ") << "4. Restaurar respaldo" << endl;
        cout << (opcionSeleccionada == 4 ? "> " : "  ") << "5. Buscar informacion" << endl;
        cout << (opcionSeleccionada == 5 ? "> " : "  ") << "6. Generar PDF" << endl;
        cout << (opcionSeleccionada == 6 ? "> " : "  ") << "7. Volver al menu principal" << endl;
    }

    // Funcion para mostrar el menu del paciente
    void mostrarMenuPaciente() {
        system("cls");
        cout << "=== MENU PACIENTE ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Agendar cita" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Volver al menu principal" << endl;
    }

    // Nueva función para mostrar el menú de opciones del doctor
    void mostrarMenuOpcionesDoctor() {
        system("cls");
        cout << "=== MENU DOCTOR ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Acceso Doctor" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Registro Doctor" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Volver al menu principal" << endl;
    }

    // Function to validate name input
    string obtenerNombreValido(const string& prompt) {
        string nombre;
        bool nombreValido = false;
        while (!nombreValido) {
            nombre.clear();
            cout << prompt;
            while (true) {
                char ch = _getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8) { // Backspace key
                    if (!nombre.empty()) {
                        nombre.pop_back();
                        cout << "\b \b";
                    }
                } else if (isalpha(ch) || ch == ' ') {
                    nombre += ch;
                    cout << ch;
                }
            }
            cout << endl;
            if (!nombre.empty() && nombre.find_first_not_of(' ') != string::npos) {
                nombreValido = true;
            } else {
                cout << "Error: El nombre no puede estar vacío o contener solo espacios." << endl;
            }
        }
        return nombre;
    }

    // Modificar la función registrarDoctor para usar el archivo
    void registrarDoctor() {
        system("cls");
        cout << "=== REGISTRO DE DOCTOR ===" << endl;
        
        // Nombre del doctor
        string nombreDoctor = obtenerNombreValido("Ingrese el nombre del doctor: ");
        
        // Cédula del doctor (reutilizando la validación de teclado)
        string cedula;
        bool cedulaValida = false;
        do {
            cedula.clear();
            cout << "Ingrese la cédula del doctor: ";
            while (true) {
                char ch = _getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8) { // Backspace key
                    if (!cedula.empty()) {
                        cedula.pop_back();
                        cout << "\b \b";
                    }
                } else if (ch >= '0' && ch <= '9' && cedula.length() < 10) {
                    cedula += ch;
                    cout << ch;
                }
            }
            cout << endl;

            if (Validaciones::validarCedulaEcuatoriana(cedula)) {
                if (Validaciones::verificarDoctorRegistrado(cedula)) {
                    cout << "Error: Esta cedula ya esta registrada como doctor." << endl;
                } else if (Validaciones::verificarCedulaPaciente(cedula)) {
                    cout << "Error: Esta cedula ya esta registrada como paciente." << endl;
                } else {
                    cedulaValida = true;
                }
            }
        } while (!cedulaValida);

        // Teléfono (reutilizando la validación de teclado)
        string telefono;
        bool telefonoValido = false;
        do {
            telefono.clear();
            cout << "Ingrese el numero de telefono: ";
            while (true) {
                char ch = _getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8) { // Backspace key
                    if (!telefono.empty()) {
                        telefono.pop_back();
                        cout << "\b \b";
                    }
                } else if (ch >= '0' && ch <= '9' && telefono.length() < 10) {
                    telefono += ch;
                    cout << ch;
                }
            }
            cout << endl;
            
            // Check if phone number is valid and not duplicated
            if (!Validaciones::validarTelefonoEcuador(telefono)) {
                telefonoValido = false;
            } else if (Validaciones::verificarTelefonoDuplicado(telefono)) {
                telefonoValido = false;
            } else {
                telefonoValido = true;
            }
            
        } while (!telefonoValido);

        // Fecha de nacimiento (reutilizando la validación de teclado)
        string fechaNacStr;
        Fecha fechaNac;
        bool fechaNacimientoValida = false;
        while (!fechaNacimientoValida) {
            fechaNacStr.clear();
            cout << "Ingrese la fecha de nacimiento (DD-MM-YYYY): ";
            while (true) {
                char ch = _getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8) { // Backspace key
                    if (!fechaNacStr.empty()) {
                        fechaNacStr.pop_back();
                        cout << "\b \b";
                    }
                } else if ((ch >= '0' && ch <= '9') || ch == '-') {
                    fechaNacStr += ch;
                    cout << ch;
                }
            }
            cout << endl;
            if (Validaciones::validarFechaNacimiento(fechaNacStr)) {
                fechaNac = Fecha::crearDesdeCadena(fechaNacStr);
                fechaNacimientoValida = true;
            }
        }

        // Solicitar el género del doctor
        string genero = Validaciones::obtenerGenero("Ingrese el genero del doctor (M/F): ");

        system("cls");
        int opcionEsp = 0;
        bool seleccionEsp = false;
        string especialidadSeleccionada;

        while (!seleccionEsp) {
            mostrarEspecialidadesMatriz(opcionEsp);
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();

            switch (key) {
                case 72: // Arriba
                    if (opcionEsp >= 3) opcionEsp -= 3;
                    break;
                case 80: // Abajo
                    if (opcionEsp + 3 < especialidades.size()) opcionEsp += 3;
                    break;
                case 75: // Izquierda
                    if (opcionEsp % 3 > 0) opcionEsp--;
                    break;
                case 77: // Derecha
                    if (opcionEsp % 3 < 2 && opcionEsp + 1 < especialidades.size()) opcionEsp++;
                    break;
                case 13: // Enter
                    especialidadSeleccionada = especialidades[opcionEsp];
                    seleccionEsp = true;
                    break;
            }
        }

        // Crear y guardar el nuevo doctor
        Persona nuevoDoctor(nombreDoctor, fechaNac, cedula);
        nuevoDoctor.setRequerimiento(especialidadSeleccionada); // Usamos requerimiento para almacenar la especialidad
        guardarDoctor(nuevoDoctor);
        system("pause");
    }

    // Funcion para mostrar las citas almacenadas
    void mostrarCitas() {
        Validaciones::mostrarCitas(citas);
    }

    // Funcion para guardar las citas en un archivo sin duplicados
    void guardarCitas() {
        Validaciones::guardarCitas(citas);
    }

    // Funcion para eliminar una cita por fecha
    void eliminarCita() {
        system("cls");
        cout << "=== ELIMINAR CITA ===" << endl;
        string fechaStr;
        cout << "Ingrese la fecha de la cita a eliminar (DD-MM-YYYY): ";
        cin >> fechaStr;

        Validaciones::eliminarCita(citas, fechaStr);
    }

    // Funcion para mostrar el menu de complicaciones
    void mostrarMenuComplicaciones(int& opcionComplicacion) {
        bool seleccionComplicacion = false;
        while (!seleccionComplicacion) {
            system("cls");
            cout << "=== SELECCIONAR COMPLICACION ===" << endl;
            cout << (opcionComplicacion == 0 ? "> " : "  ") << "1. Especialidad" << endl;
            cout << (opcionComplicacion == 1 ? "> " : "  ") << "2. Volver al menu principal" << endl;

            int key = _getch();
            if (key == 0 || key == 224) key = _getch();

            switch (key) {
                case 72: // Arriba
                    opcionComplicacion = (opcionComplicacion - 1 + 2) % 2;
                    break;
                case 80: // Abajo
                    opcionComplicacion = (opcionComplicacion + 1) % 2;
                    break;
                case 13: // Enter
                    seleccionComplicacion = true;
                    break;
            }
        }
    }

    // Funcion para mostrar el menu de especialidades
    void mostrarMenuEspecialidades(int& opcionEspecialidad) {
        system("cls");
        cout << "=== SELECCIONAR ESPECIALIDAD ===" << endl;
        for (int i = 0; i < especialidades.size(); ++i) {
            cout << (opcionEspecialidad == i ? "> " : "  ") << especialidades[i] << endl;
        }
    }

    // Agregar esta nueva función para generar horarios
    vector<pair<int, int>> generarHorarios() {
        vector<pair<int, int>> horarios;
        int hora = 10;
        int minuto = 30;
        
        while (hora < 24) {
            horarios.push_back({hora, minuto});
            minuto += 30;
            if (minuto >= 60) {
                hora++;
                minuto = 0;
            }
        }
        return horarios;
    }

    // Nueva función auxiliar para mostrar horarios en formato matriz
    void mostrarHorariosMatriz(const vector<pair<int, int>>& horarios, int opcionSeleccionada, 
                              const string& fechaStr, const string& especialidad = "") {
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
                    for (const auto& ocupado : horariosOcupadosEspecialidad) {
                        if (ocupado.fechaHash == fechaHash && 
                            ocupado.hora == horarios[indice].first && 
                            ocupado.minuto == horarios[indice].second &&
                            (ocupado.especialidad == especialidad || especialidad.empty())) {
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

    // Nueva función para mostrar especialidades en formato matriz
    void mostrarEspecialidadesMatriz(int opcionSeleccionada) {
        system("cls");
        cout << "=== ESPECIALIDADES DISPONIBLES ===" << endl;
        cout << "Use las flechas para navegar y Enter para seleccionar" << endl << endl;

        const int COLUMNAS = 3;  // Número de columnas para mostrar
        int totalEspecialidades = especialidades.size();
        int filas = (totalEspecialidades + COLUMNAS - 1) / COLUMNAS;

        // Contenido en formato matriz
        for (int fila = 0; fila < filas; fila++) {
            for (int col = 0; col < COLUMNAS; col++) {
                int indice = fila * COLUMNAS + col;
                if (indice < totalEspecialidades) {
                    string especialidad = (indice == opcionSeleccionada ? "> " : "  ") + 
                                       especialidades[indice];
                    cout << setw(35) << left << especialidad;
                }
            }
            cout << endl;
        }
    }

    // Modificar la función agendarCita para incluir la verificación adicional
    void agendarCita() {
        system("cls");
        cout << "=== AGENDAR CITA ===" << endl;
        
        // 1. Solicitar cédula
        string cedula;
        bool cedulaValida = false;
        string nombrePaciente, fechaNacimientoStr, genero, celular;
        bool pacienteRegistrado = false;
        
        do {
            cedula.clear();
            cout << "Ingrese el numero de cedula: ";
            while (true) {
                char ch = _getch();
                if (ch == 13) break;
                else if (ch == 8) {
                    if (!cedula.empty()) {
                        cedula.pop_back();
                        cout << "\b \b";
                    }
                } else if (ch >= '0' && ch <= '9' && cedula.length() < 10) {
                    cedula += ch;
                    cout << ch;
                }
            }
            cout << endl;

            if (Validaciones::validarCedulaEcuatoriana(cedula)) {
                if (Validaciones::verificarDoctorRegistrado(cedula)) {
                    cout << "Error: Esta cedula pertenece a un doctor registrado." << endl;
                } else {
                    // Verificar si el paciente ya está registrado y recuperar todos sus datos
                    ifstream archivo("output/pacientes.txt");
                    string linea;
                    string tempLinea;
                    while (getline(archivo, linea)) {
                        if (linea.find("Cédula: " + cedula) != string::npos) {
                            pacienteRegistrado = true;
                            
                            getline(archivo, linea); // Línea del nombre
                            nombrePaciente = linea.substr(linea.find(": ") + 2);
                            
                            getline(archivo, linea); // Línea de la fecha de nacimiento
                            fechaNacimientoStr = linea.substr(linea.find(": ") + 2);
                            
                            getline(archivo, linea); // Línea del género
                            genero = linea.substr(linea.find(": ") + 2);
                            
                            getline(archivo, linea); // Línea del celular
                            celular = linea.substr(linea.find(": ") + 2);
                            break;
                        }
                    }
                    archivo.close();
                    cedulaValida = true;
                }
            }
        } while (!cedulaValida);

        if (!pacienteRegistrado) {
            // Si el paciente no está registrado, solicitar sus datos
            nombrePaciente = obtenerNombreValido("Ingrese el nombre del paciente: ");
            genero = Validaciones::obtenerGenero("Ingrese el genero del paciente (M/F): ");

            // Solicitar fecha de nacimiento
            bool fechaNacimientoValida = false;
            while (!fechaNacimientoValida) {
                fechaNacimientoStr.clear();
                cout << "Ingrese la fecha de nacimiento (DD-MM-YYYY): ";
                while (true) {
                    char ch = _getch();
                    if (ch == 13) break;
                    else if (ch == 8) {
                        if (!fechaNacimientoStr.empty()) {
                            fechaNacimientoStr.pop_back();
                            cout << "\b \b";
                        }
                    } else if ((ch >= '0' && ch <= '9') || ch == '-') {
                        fechaNacimientoStr += ch;
                        cout << ch;
                    }
                }
                cout << endl;
                if (Validaciones::validarFechaNacimiento(fechaNacimientoStr)) {
                    fechaNacimientoValida = true;
                }
            }

            // Solicitar número de celular solo para nuevos pacientes
            celular.clear();
            bool telefonoValido = false;
            do {
                cout << "Ingrese el numero de celular: ";
                while (true) {
                    char ch = _getch();
                    if (ch == 13) break;
                    else if (ch == 8) {
                        if (!celular.empty()) {
                            celular.pop_back();
                            cout << "\b \b";
                        }
                    } else if (ch >= '0' && ch <= '9' && celular.length() < 10) {
                        celular += ch;
                        cout << ch;
                    }
                }
                cout << endl;
                
                // Check if phone number is valid and not duplicated
                if (!Validaciones::validarTelefonoEcuador(celular)) {
                    telefonoValido = false;
                } else if (Validaciones::verificarTelefonoDuplicado(celular)) {
                    telefonoValido = false;
                } else {
                    telefonoValido = true;
                }
                
            } while (!telefonoValido);

            // Guardar la información del nuevo paciente
            Validaciones::guardarPaciente(nombrePaciente, cedula, fechaNacimientoStr, genero, celular);
        } else {
            cout << "\nPaciente encontrado:" << endl;
            cout << "Nombre: " << nombrePaciente << endl;
            cout << "Fecha de nacimiento: " << fechaNacimientoStr << endl;
            cout << "Genero: " << genero << endl;
            cout << "Celular: " << celular << endl;
            system("pause");
        }

        // 5. Seleccionar tipo de atención
        int opcionComplicacion = 0;
        bool seleccionComplicacion = false;
        string especialidadSeleccionada;

        while (!seleccionComplicacion) {
            mostrarMenuComplicaciones(opcionComplicacion);
            if (opcionComplicacion == 1) {
                return; // Volver al menú principal
            }
            if (opcionComplicacion == 0) {
                system("cls");
                int opcionEsp = 0;
                bool seleccionEsp = false;
                const int COLUMNAS = 3;

                while (!seleccionEsp) {
                    mostrarEspecialidadesMatriz(opcionEsp);

                    int key = _getch();
                    if (key == 0 || key == 224) key = _getch();

                    switch (key) {
                        case 72: // Arriba
                            if (opcionEsp >= COLUMNAS) 
                                opcionEsp -= COLUMNAS;
                            break;
                        case 80: // Abajo
                            if (opcionEsp + COLUMNAS < especialidades.size()) 
                                opcionEsp += COLUMNAS;
                            break;
                        case 75: // Izquierda
                            if (opcionEsp % COLUMNAS > 0)
                                opcionEsp--;
                            break;
                        case 77: // Derecha
                            if (opcionEsp % COLUMNAS < COLUMNAS - 1 && opcionEsp + 1 < especialidades.size())
                                opcionEsp++;
                            break;
                        case 13: // Enter
                            especialidadSeleccionada = especialidades[opcionEsp];
                            seleccionEsp = true;
                            break;
                    }
                }
            }
            seleccionComplicacion = true;
        }

        // 6. Seleccionar horario
        system("cls");
        vector<pair<int, int>> horarios = generarHorarios();
        int opcionHorario = 0;
        bool seleccionHorario = false;
        const int COLUMNAS = 4;

        // Crear la cita con los datos seleccionados
        string fechaStr;
        bool fechaValida = false;
        while (!fechaValida) {
            fechaStr.clear();
            cout << "\nIngrese la fecha para la cita (DD-MM-YYYY): ";
            while (true) {
                char ch = _getch();
                if (ch == 13) { // Enter key
                    break;
                } else if (ch == 8) { // Backspace key
                    if (!fechaStr.empty()) {
                        fechaStr.pop_back();
                        cout << "\b \b";
                    }
                } else if ((ch >= '0' && ch <= '9') || ch == '-') {
                    fechaStr += ch;
                    cout << ch;
                }
            }
            cout << endl;
            if (Validaciones::validarFecha(fechaStr)) {
                fechaValida = true;
            }
        }

        while (!seleccionHorario) {
            mostrarHorariosMatriz(horarios, opcionHorario, fechaStr, especialidadSeleccionada);

            int key = _getch();
            if (key == 0 || key == 224) key = _getch();

            switch (key) {
                case 72: // Arriba
                    if (opcionHorario >= COLUMNAS) 
                        opcionHorario -= COLUMNAS;
                    break;
                case 80: // Abajo
                    if (opcionHorario + COLUMNAS < horarios.size()) 
                        opcionHorario += COLUMNAS;
                    break;
                case 75: // Izquierda
                    if (opcionHorario % COLUMNAS > 0)
                        opcionHorario--;
                    break;
                case 77: // Derecha
                    if (opcionHorario % COLUMNAS < COLUMNAS - 1 && opcionHorario + 1 < horarios.size())
                        opcionHorario++;
                    break;
                case 13: // Enter
                    // Verificar si el horario está disponible
                    hash<string> hasher;
                    int fechaHash = hasher(fechaStr);
                    bool horarioOcupado = false;
                    
                    for (const auto& ocupado : horariosOcupadosEspecialidad) {
                        if (ocupado.fechaHash == fechaHash && 
                            ocupado.hora == horarios[opcionHorario].first && 
                            ocupado.minuto == horarios[opcionHorario].second &&
                            (ocupado.especialidad == especialidadSeleccionada || especialidadSeleccionada.empty())) {
                            horarioOcupado = true;
                            break;
                        }
                    }

                    if (!horarioOcupado) {
                        // Guardar el horario como ocupado
                        horariosOcupadosEspecialidad.push_back({
                            especialidadSeleccionada,
                            fechaHash,
                            horarios[opcionHorario].first,
                            horarios[opcionHorario].second
                        });
                        seleccionHorario = true;
                    }
                    break;
            }
        }

        // Guardar el horario como ocupado
        hash<string> hasher;
        int fechaHash = hasher(fechaStr);
        horariosOcupados.push_back({fechaHash, {horarios[opcionHorario].first, horarios[opcionHorario].second}});

        Fecha nuevaCita = Fecha::crearDesdeCadena(fechaStr);
        nuevaCita.setHora(horarios[opcionHorario].first);
        nuevaCita.setMinuto(horarios[opcionHorario].second);
        citas.push_back(nuevaCita);

        // Mostrar resumen de la cita
        system("cls");
        cout << "=== RESUMEN DE LA CITA ===" << endl;
        cout << "Paciente: " << nombrePaciente << endl;
        cout << "Cedula: " << cedula << endl;
        cout << "Celular: " << celular << endl;
        cout << "Genero: " << genero << endl;
        cout << "Fecha de Nacimiento: " << fechaNacimientoStr << endl;
        cout << "Tipo de atencion: " << "Especialidad" << endl;
        cout << "Especialidad: " << especialidadSeleccionada << endl;
        cout << "Fecha y hora: " << nuevaCita.mostrar() << endl;
        cout << "\nCita agendada exitosamente." << endl;

        // Guardar resumen de la cita en cita.txt
        Validaciones::guardarResumenCita(nombrePaciente, cedula, celular, genero, fechaNacimientoStr, "Especialidad", especialidadSeleccionada, nuevaCita);

        // Guardar las citas automáticamente
        guardarCitas();
        
        system("pause");
    }

    // Nueva función para guardar pacientes
    void guardarPaciente(const string& nombre, const string& cedula, const string& fechaNacimiento) {
        system("mkdir output 2> nul");
        ofstream archivo("output/pacientes.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Nombre: " << nombre << endl;
            archivo << "Cédula: " << cedula << endl;
            archivo << "Fecha de Nacimiento: " << fechaNacimiento << endl;
            archivo << "-------------------------" << endl;
            archivo.close();
        }
    }

    void backupCitas();
    void abrirBackup();

    // Funcion para generar el archivo txt y mostrar las citas
    void generarYMostrarCitas() {
        guardarCitas();
        mostrarCitas();
    }

    // Renombrar la función original a accesoDoctor
    void accesoDoctor() {
        system("cls");
        cout << "=== ACCESO DOCTOR ===" << endl;
        
        doctorActualCedula.clear(); // Limpiar la cédula anterior
        cout << "Ingrese la cedula del doctor: ";
        
        char ch;
        while (true) {
            ch = _getch();
            if (ch == 13) { // Enter key
                break;
            } else if (ch == 8) { // Backspace key
                if (!doctorActualCedula.empty()) {
                    doctorActualCedula.pop_back();
                    cout << "\b \b";
                }
            } else if (ch >= '0' && ch <= '9') {
                doctorActualCedula += ch;
                cout << ch;
            }
        }

        if (!Validaciones::verificarDoctorRegistrado(doctorActualCedula)) {
            cout << "\nError: Doctor no registrado en el sistema." << endl;
            system("pause");
            return;
        }

        string especialidad = obtenerEspecialidadDoctor(doctorActualCedula);
        cout << "\nBienvenido Dr./Dra. - Especialidad: " << especialidad << endl;
        system("pause");
        seleccionarCita();
    }

    void mostrarRequerimientoCita() {
        system("cls");
        cout << "=== REQUERIMIENTO DE CITA ===" << endl;
        if (citas.empty()) {
            cout << "No hay citas registradas." << endl;
        } else {
            for (const auto& cita : citas) {
                cout << "Fecha de la cita: " << cita.mostrar() << endl;
                // Aquí se pueden agregar más detalles del paciente si están disponibles
            }
        }
        cout << endl;
        cout << "Desea aceptar la cita? (Use las flechas para seleccionar y Enter para confirmar)" << endl;
        cout << "> Si" << endl;
        cout << "  No" << endl;
    }

    void manejarRequerimientoCita() {
        mostrarRequerimientoCita();
        int opcion = 0;
        bool seleccion = false;
        while (!seleccion) {
            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
            }

            switch (key) {
                case 72: // Flecha arriba
                    if (opcion > 0) opcion--;
                    break;
                case 80: // Flecha abajo
                    if (opcion < 1) opcion++;
                    break;
                case 13: // Tecla Enter
                    seleccion = true;
                    break;
            }

            system("cls");
            cout << "=== REQUERIMIENTO DE CITA ===" << endl;
            if (citas.empty()) {
                cout << "No hay citas registradas." << endl;
            } else {
                for (const auto& cita : citas) {
                    cout << "Fecha de la cita: " << cita.mostrar() << endl;
                    // Aquí se pueden agregar más detalles del paciente si están disponibles
                }
            }
            cout << endl;
            cout << "Desea aceptar la cita? (Use las flechas para seleccionar y Enter para confirmar)" << endl;
            cout << (opcion == 0 ? "> Si" : "  Si") << endl;
            cout << (opcion == 1 ? "> No" : "  No") << endl;
        }

        if (opcion == 0) {
            system("cls");
            cout << "=== DETALLES DE LA CITA ===" << endl;
            if (citas.empty()) {
                cout << "No hay citas registradas." << endl;
            } else {
                for (const auto& cita : citas) {
                    cout << "Fecha de la cita: " << cita.mostrar() << endl;
                }
            }
            system("pause");
        } else {
            cout << "Tenga un buen dia." << endl;
            system("pause");
        }
    }

    void seleccionarCita() {
        // Obtener información del doctor actual
        string doctorEspecialidad = obtenerEspecialidadDoctor(doctorActualCedula);
        string nombreDoctor;
        
        // Obtener el nombre del doctor - CORREGIDO
        ifstream archivoDoctores("output/doctores.txt");
        string linea;
        string nombreTemp;
        
        while (getline(archivoDoctores, linea)) {
            if (linea.find("Nombre: ") != string::npos) {
                nombreTemp = linea.substr(linea.find(": ") + 2);
                
                // Leer la siguiente línea que debería tener la cédula
                if (getline(archivoDoctores, linea) && linea.find("Cédula: " + doctorActualCedula) != string::npos) {
                    nombreDoctor = nombreTemp; // Encontramos la coincidencia
                    break;
                }
            }
        }
        archivoDoctores.close();
        
        if (nombreDoctor.empty()) {
            cout << "Error: No se pudo encontrar el nombre del doctor." << endl;
            system("pause");
            return;
        }

        vector<pair<Fecha, string>> citasConEspecialidad;
        vector<string> todasLasCitas;
        string citaActual = "";
        string especialidadCita = "";
        string fechaCita = "";
        string horaCita = "";
        string estadoCita = "";
        bool citaEnProceso = false;
        bool esCitaPendiente = false;

        // Leer todo el archivo primero
        ifstream archivo("output/cita.txt");
        
        while (getline(archivo, linea)) {
            if (linea.find("=== RESUMEN DE LA CITA ===") != string::npos) {
                if (!citaActual.empty()) {
                    todasLasCitas.push_back(citaActual);
                    // Solo agregar a citasConEspecialidad si está pendiente
                    if (esCitaPendiente && estadoCita == "Pendiente") {
                        if (especialidadCita == doctorEspecialidad || 
                            (doctorEspecialidad == "General" && especialidadCita == "General")) {
                            Fecha fecha = Fecha::crearDesdeCadena(fechaCita);
                            if (!horaCita.empty()) {
                                size_t pos = horaCita.find(":");
                                if (pos != string::npos) {
                                    int hora = stoi(horaCita.substr(0, pos));
                                    int minuto = stoi(horaCita.substr(pos + 1));
                                    fecha.setHora(hora);
                                    fecha.setMinuto(minuto);
                                }
                            }
                            citasConEspecialidad.push_back({fecha, citaActual});
                        }
                    }
                }
                citaActual = linea + "\n";
                especialidadCita = "";
                fechaCita = "";
                horaCita = "";
                estadoCita = "";
                esCitaPendiente = false;
                citaEnProceso = true;
                continue;
            }

            citaActual += linea + "\n";
            
            if (citaEnProceso) {
                if (linea.find("Especialidad: " + especialidadCita) != string::npos) {
                    especialidadCita = linea.substr(13);
                    esCitaPendiente = true;
                } else if (linea.find("Fecha de Cita: " + fechaCita) != string::npos) {
                    fechaCita = linea.substr(14);
                } else if (linea.find("Hora de Cita: " + horaCita) != string::npos) {
                    horaCita = linea.substr(13);
                } else if (linea.find("Estado: " + estadoCita) != string::npos) {
                    estadoCita = linea.substr(8);
                    // Si el estado no es pendiente, desactivar esCitaPendiente
                    if (estadoCita.find("Pendiente") == string::npos) {
                        esCitaPendiente = false;
                    }
                }
            }
        }

        // No olvidar procesar la última cita
        if (!citaActual.empty()) {
            todasLasCitas.push_back(citaActual);
            if (esCitaPendiente && (especialidadCita == doctorEspecialidad || 
                (doctorEspecialidad == "General" && especialidadCita == "General"))) {
                Fecha fecha = Fecha::crearDesdeCadena(fechaCita);
                if (!horaCita.empty()) {
                    size_t pos = horaCita.find(":");
                    if (pos != string::npos) {
                        int hora = stoi(horaCita.substr(0, pos));
                        int minuto = stoi(horaCita.substr(pos + 1));
                        fecha.setHora(hora);
                        fecha.setMinuto(minuto);
                    }
                }
                citasConEspecialidad.push_back({fecha, citaActual});
            }
        }
        archivo.close();

        if (citasConEspecialidad.empty()) {
            cout << "No hay citas pendientes para su especialidad (" << doctorEspecialidad << ")." << endl;
            system("pause");
            return;
        }

        int citaSeleccionada = 0;
        bool seleccion = false;

        while (!seleccion) {
            system("cls");
            cout << "=== CITAS PENDIENTES - " << doctorEspecialidad << " ===" << endl;
            cout << "Use las flechas para seleccionar una cita y Enter para confirmar" << endl << endl;

            for (size_t i = 0; i < citasConEspecialidad.size(); i++) {
                cout << (i == citaSeleccionada ? "> " : "  ") 
                     << citasConEspecialidad[i].second;
            }

            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                    case 72: // Flecha arriba
                        if (citaSeleccionada > 0) citaSeleccionada--;
                        break;
                    case 80: // Flecha abajo
                        if (citaSeleccionada < citasConEspecialidad.size() - 1) citaSeleccionada++;
                        break;
                }
            } else if (key == 13) { // Enter
                // Mostrar detalles de la cita y confirmar
                system("cls");
                cout << "=== CONFIRMAR CITA ===" << endl;
                cout << citasConEspecialidad[citaSeleccionada].second << endl;
                cout << "¿Desea aceptar esta cita?" << endl;
                cout << "> Sí" << endl;
                cout << "  No" << endl;

                bool confirmacion = true;
                bool decidido = false;

                while (!decidido) {
                    key = _getch();
                    if (key == 0 || key == 224) {
                        key = _getch();
                        switch (key) {
                            case 72: // Flecha arriba
                            case 80: // Flecha abajo
                                confirmacion = !confirmacion;
                                system("cls");
                                cout << "=== CONFIRMAR CITA ===" << endl;
                                cout << citasConEspecialidad[citaSeleccionada].second << endl;
                                cout << "¿Desea aceptar esta cita?" << endl;
                                cout << (confirmacion ? "> " : "  ") << "Sí" << endl;
                                cout << (confirmacion ? "  " : "> ") << "No" << endl;
                                break;
                        }
                    } else if (key == 13) { // Enter
                        if (confirmacion) {
                            // 1. Guardar la cita en citas_aceptadas.txt
                            ofstream archivoAceptadas("output/citas_aceptadas.txt", ios::app);
                            string citaAceptada = citasConEspecialidad[citaSeleccionada].second;
                            
                            // Buscar y reemplazar el estado y agregar información del doctor
                            size_t pos = citaAceptada.find("Estado: Pendiente");
                            if (pos != string::npos) {
                                citaAceptada.replace(pos, string("Estado: Pendiente").length(), "Estado: Aceptada");
                                pos = citaAceptada.find("-------------------------");
                                if (pos != string::npos) {
                                    // Usar nombreDoctor en lugar de doctorEspecialidad
                                    string infoDoctor = "Doctor Asignado: " + nombreDoctor + "\n";
                                    infoDoctor += "Cédula Doctor: " + doctorActualCedula + "\n";
                                    infoDoctor += "Especialidad Doctor: " + doctorEspecialidad + "\n";
                                    citaAceptada.insert(pos, infoDoctor);
                                }
                            }
                            
                            archivoAceptadas << citaAceptada;
                            archivoAceptadas.close();

                            // 2. Reescribir cita.txt sin la cita aceptada
                            ofstream archivoEscritura("output/cita.txt", ios::trunc);
                            for (const auto& cita : todasLasCitas) {
                                if (cita != citasConEspecialidad[citaSeleccionada].second) {
                                    archivoEscritura << cita;
                                }
                            }
                            archivoEscritura.close();

                            cout << "\nCita aceptada exitosamente." << endl;
                            system("pause");
                            seleccionarCita(); // Recargar el menú para mostrar las citas actualizadas
                            return;
                        } else {
                            cout << "\nCita rechazada." << endl;
                            system("pause");
                        }
                        decidido = true;
                        seleccion = true;
                    }
                }
            }
        }
    }

    // Add new methods for deleting patients, deleting doctors, modifying information, and generating backups
    void eliminarPaciente() {
        system("cls");
        cout << "=== ELIMINAR PACIENTE ===" << endl;
        string cedula;
        cout << "Ingrese la cedula del paciente a eliminar: ";
        cin >> cedula;

        if (!Validaciones::validarCedulaEcuatoriana(cedula)) {
            cout << "Cedula no valida." << endl;
            system("pause");
            return;
        }

        ifstream archivo("output/pacientes.txt");
        ofstream temp("output/temp.txt");
        string linea;
        bool encontrado = false;
        bool saltarLineas = false;

        while (getline(archivo, linea)) {
            // Si estamos en modo saltar líneas y encontramos el separador, dejar de saltar
            if (saltarLineas && linea == "-------------------------") {
                saltarLineas = false;
                continue; // No copiar el separador del paciente eliminado
            }
            
            // Si estamos saltando líneas, continuar sin escribir
            if (saltarLineas) {
                continue;
            }
            
            // Verificar si es la línea de cédula que buscamos
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                saltarLineas = true; // Comenzar a saltar líneas
                continue; // No copiar esta línea
            }
            
            // Si no estamos saltando, copiar la línea al archivo temporal
            temp << linea << endl;
        }

        archivo.close();
        temp.close();
        remove("output/pacientes.txt");
        rename("output/temp.txt", "output/pacientes.txt");

        if (encontrado) {
            cout << "Paciente eliminado correctamente." << endl;
        } else {
            cout << "No se encontro un paciente con esa cedula." << endl;
        }
        system("pause");
    }

    void eliminarTodosPacientes() {
        system("cls");
        cout << "=== ELIMINAR TODOS LOS PACIENTES ===" << endl;
        ofstream archivo("output/pacientes.txt", ios::trunc);
        archivo.close();
        cout << "Todos los pacientes han sido eliminados." << endl;
        system("pause");
    }

    void eliminarDoctor() {
        system("cls");
        cout << "=== ELIMINAR DOCTOR ===" << endl;
        string cedula;
        cout << "Ingrese la cedula del doctor a eliminar: ";
        cin >> cedula;

        if (!Validaciones::validarCedulaEcuatoriana(cedula)) {
            cout << "Cedula no valida." << endl;
            system("pause");
            return;
        }

        ifstream archivo("output/doctores.txt");
        ofstream temp("output/temp.txt");
        string linea;
        bool encontrado = false;
        bool saltarLineas = false;
        string lineaAnterior = "";

        // Buffer para mantener líneas hasta confirmar si deben ser descartadas
        vector<string> buffer;

        while (getline(archivo, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                saltarLineas = true;
                buffer.clear(); // Descartamos el nombre que estaba en el buffer
                continue;
            }
            
            if (saltarLineas) {
                // Si encontramos el separador, dejamos de saltar líneas
                if (linea == "-------------------------") {
                    saltarLineas = false;
                    continue; // No escribir el separador
                }
                continue; // Saltamos esta línea
            }
            
            // Si la línea actual tiene un nombre
            if (linea.find("Nombre: ") != string::npos) {
                // Guardamos en el buffer en lugar de escribirla inmediatamente
                buffer.clear();
                buffer.push_back(linea);
            } 
            // Si la línea actual NO es un nombre ni hay nada que saltar, escribimos lo que haya en el buffer más la línea actual
            else if (!buffer.empty()) {
                // Escribimos el nombre y la línea actual (que debería ser la cédula)
                for (const auto& bufferedLine : buffer) {
                    temp << bufferedLine << endl;
                }
                temp << linea << endl;
                buffer.clear();
            }
            else {
                // Escribir directamente la línea si no es un nombre ni hay buffer
                temp << linea << endl;
            }
        }

        archivo.close();
        temp.close();
        remove("output/doctores.txt");
        rename("output/temp.txt", "output/doctores.txt");

        if (encontrado) {
            cout << "Doctor eliminado correctamente." << endl;
        } else {
            cout << "No se encontro un doctor con esa cedula." << endl;
        }
        system("pause");
    }

    void eliminarTodosDoctores() {
        system("cls");
        cout << "=== ELIMINAR TODOS LOS DOCTORES ===" << endl;
        ofstream archivo("output/doctores.txt", ios::trunc);
        archivo.close();
        cout << "Todos los doctores han sido eliminados." << endl;
        system("pause");
    }

    void eliminarTodasCitas() {
        system("cls");
        cout << "=== ELIMINAR TODAS LAS CITAS ===" << endl;
        
        // Borrar citas pendientes
        ofstream archivoPendientes("output/cita.txt", ios::trunc);
        archivoPendientes.close();
        
        // Borrar citas aceptadas
        ofstream archivoAceptadas("output/citas_aceptadas.txt", ios::trunc);
        archivoAceptadas.close();
        
        cout << "Se han eliminado todas las citas (pendientes y aceptadas)." << endl;
        system("pause");
    }

    void modificarInformacion() {
        system("cls");
        cout << "=== MODIFICAR INFORMACION ===" << endl;
        string cedula;
        cout << "Ingrese la cedula del paciente o doctor a modificar: ";
        cin >> cedula;

        // Check if the cedula belongs to a patient
        ifstream archivoPacientes("output/pacientes.txt");
        ofstream tempPacientes("output/tempPacientes.txt");
        string linea;
        bool encontrado = false;
        bool procesandoPaciente = false;

        while (getline(archivoPacientes, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                procesandoPaciente = true;
                
                // Get new patient information
                string nuevoNombre = obtenerNombreValido("Ingrese el nuevo nombre del paciente: ");
                
                // Get new cedula
                string nuevaCedula;
                bool cedulaValida = false;
                do {
                    nuevaCedula.clear();
                    cout << "Ingrese la nueva cédula del paciente: ";
                    while (true) {
                        char ch = _getch();
                        if (ch == 13) break;
                        else if (ch == 8) {
                            if (!nuevaCedula.empty()) {
                                nuevaCedula.pop_back();
                                cout << "\b \b";
                            }
                        } else if (ch >= '0' && ch <= '9' && nuevaCedula.length() < 10) {
                            nuevaCedula += ch;
                            cout << ch;
                        }
                    }
                    cout << endl;
                    cedulaValida = Validaciones::validarCedulaEcuatoriana(nuevaCedula);
                } while (!cedulaValida);

                // Get new birth date
                string nuevaFechaNacimiento;
                bool fechaNacimientoValida = false;
                while (!fechaNacimientoValida) {
                    nuevaFechaNacimiento.clear();
                    cout << "Ingrese la nueva fecha de nacimiento (DD-MM-YYYY): ";
                    while (true) {
                        char ch = _getch();
                        if (ch == 13) break;
                        else if (ch == 8) {
                            if (!nuevaFechaNacimiento.empty()) {
                                nuevaFechaNacimiento.pop_back();
                                cout << "\b \b";
                            }
                        } else if ((ch >= '0' && ch <= '9') || ch == '-') {
                            nuevaFechaNacimiento += ch;
                            cout << ch;
                        }
                    }
                    cout << endl;
                    fechaNacimientoValida = Validaciones::validarFechaNacimiento(nuevaFechaNacimiento);
                }

                // Get new gender
                string nuevoGenero = Validaciones::obtenerGenero("Ingrese el nuevo género del paciente (M/F): ");

                // Get new phone number
                string nuevoCelular;
                bool telefonoValido = false;
                do {
                    nuevoCelular.clear();
                    cout << "Ingrese el nuevo número de celular: ";
                    while (true) {
                        char ch = _getch();
                        if (ch == 13) break;
                        else if (ch == 8) {
                            if (!nuevoCelular.empty()) {
                                nuevoCelular.pop_back();
                                cout << "\b \b";
                            }
                        } else if (ch >= '0' && ch <= '9' && nuevoCelular.length() < 10) {
                            nuevoCelular += ch;
                            cout << ch;
                        }
                    }
                    cout << endl;
                    
                    // Check if phone number is valid and not duplicated
                    if (!Validaciones::validarTelefonoEcuador(nuevoCelular)) {
                        telefonoValido = false;
                    } else if (Validaciones::verificarTelefonoDuplicado(nuevoCelular)) {
                        telefonoValido = false;
                    } else {
                        telefonoValido = true;
                    }
                    
                } while (!telefonoValido);

                // Write new information to temp file
                tempPacientes << "Nombre: " << nuevoNombre << endl;
                tempPacientes << "Cédula: " << nuevaCedula << endl;
                tempPacientes << "Fecha de Nacimiento: " << nuevaFechaNacimiento << endl;
                tempPacientes << "Género: " << nuevoGenero << endl;
                tempPacientes << "Celular: " << nuevoCelular << endl;
                tempPacientes << "-------------------------" << endl;

                // Skip all lines until next patient or end of file
                while (getline(archivoPacientes, linea)) {
                    if (linea == "-------------------------") {
                        procesandoPaciente = false;
                        break;
                    }
                }
            } else if (!procesandoPaciente) {
                tempPacientes << linea << endl;
            }
        }

        archivoPacientes.close();
        tempPacientes.close();
        remove("output/pacientes.txt");
        rename("output/tempPacientes.txt", "output/pacientes.txt");

        if (!encontrado) {
            // Check if the cedula belongs to a doctor
            ifstream archivoDoctores("output/doctores.txt");
            ofstream tempDoctores("output/tempDoctores.txt");

            while (getline(archivoDoctores, linea)) {
                if (linea.find("Cédula: " + cedula) != string::npos) {
                    encontrado = true;
                    // Modify the information
                    string nuevoNombre = obtenerNombreValido("Ingrese el nuevo nombre del doctor: ");
                    tempDoctores << "Nombre: " << nuevoNombre << endl;

                    // Modify cedula
                    string nuevaCedula;
                    bool cedulaValida = false;
                    do {
                        nuevaCedula.clear();
                        cout << "Ingrese la nueva cédula del doctor: ";
                        while (true) {
                            char ch = _getch();
                            if (ch == 13) break;
                            else if (ch == 8) {
                                if (!nuevaCedula.empty()) {
                                    nuevaCedula.pop_back();
                                    cout << "\b \b";
                                }
                            } else if (ch >= '0' && ch <= '9' && nuevaCedula.length() < 10) {
                                nuevaCedula += ch;
                                cout << ch;
                            }
                        }
                        cout << endl;
                        if (Validaciones::validarCedulaEcuatoriana(nuevaCedula)) {
                            cedulaValida = true;
                        }
                    } while (!cedulaValida);
                    tempDoctores << "Cédula: " << nuevaCedula << endl;

                    getline(archivoDoctores, linea); // Skip the old name line
                } else {
                    tempDoctores << linea << endl;
                }
            }

            archivoDoctores.close();
            tempDoctores.close();
            remove("output/doctores.txt");
            rename("output/tempDoctores.txt", "output/doctores.txt");
        }

        if (encontrado) {
            cout << "Informacion modificada correctamente." << endl;
        } else {
            cout << "No se encontro un paciente o doctor con esa cedula." << endl;
        }
        system("pause");
    }

    void generarRespaldo() {
        system("cls");
        cout << "=== GENERAR RESPALDO ===" << endl;

        // Backup de todas las citas (pendientes y aceptadas) en un solo archivo
        ofstream citasBackup("output/citas_backup.txt", ios::trunc);
        
        // Primero escribimos las citas pendientes
        ifstream citasArchivo("output/cita.txt");
        if (citasArchivo.is_open()) {
            citasBackup << "=== CITAS PENDIENTES ===" << endl;
            string linea;
            while (getline(citasArchivo, linea)) {
                citasBackup << linea << endl;
            }
            citasArchivo.close();
        }

        // Luego escribimos las citas aceptadas
        ifstream citasAceptadasArchivo("output/citas_aceptadas.txt");
        if (citasAceptadasArchivo.is_open()) {
            citasBackup << "=== CITAS ACEPTADAS ===" << endl;
            string linea;
            while (getline(citasAceptadasArchivo, linea)) {
                citasBackup << linea << endl;
            }
            citasAceptadasArchivo.close();
        }
        citasBackup.close();

        // Backup doctores
        ifstream doctoresArchivo("output/doctores.txt");
        ofstream doctoresBackup("output/doctores_backup.txt", ios::trunc);
        doctoresBackup << doctoresArchivo.rdbuf();
        doctoresArchivo.close();
        doctoresBackup.close();

        // Backup pacientes
        ifstream pacientesArchivo("output/pacientes.txt");
        ofstream pacientesBackup("output/pacientes_backup.txt", ios::trunc);
        pacientesBackup << pacientesArchivo.rdbuf();
        pacientesArchivo.close();
        pacientesBackup.close();

        cout << "Respaldo generado correctamente:" << endl;
        cout << "- Todas las citas: citas_backup.txt" << endl;
        cout << "- Doctores: doctores_backup.txt" << endl;
        cout << "- Pacientes: pacientes_backup.txt" << endl;
        system("pause");
    }

    void mostrarMenuEliminar() {
        system("cls");
        cout << "=== MENU ELIMINAR ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Eliminar paciente por cedula" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Eliminar doctor por cedula" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Eliminar todas las citas" << endl;
        cout << (opcionSeleccionada == 3 ? "> " : "  ") << "4. Eliminar todos los pacientes" << endl;
        cout << (opcionSeleccionada == 4 ? "> " : "  ") << "5. Eliminar todos los doctores" << endl;
        cout << (opcionSeleccionada == 5 ? "> " : "  ") << "6. Volver al menu administrador" << endl;
    }

    void mostrarMenuRestaurar() {
        system("cls");
        cout << "=== RESTAURAR RESPALDO ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Restaurar todo" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Restaurar solo citas" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Restaurar solo doctores" << endl;
        cout << (opcionSeleccionada == 3 ? "> " : "  ") << "4. Restaurar solo pacientes" << endl;
        cout << (opcionSeleccionada == 4 ? "> " : "  ") << "5. Volver" << endl;
    }

    bool restaurarCitas() {
        ifstream backup("output/citas_backup.txt");
        string linea;
        string citaActual;
        bool esCitaAceptada = false;
        ofstream citasPendientes("output/cita.txt", ios::trunc);
        ofstream citasAceptadas("output/citas_aceptadas.txt", ios::trunc);

        if (!backup.is_open() || !citasPendientes.is_open() || !citasAceptadas.is_open()) {
            return false;
        }

        while (getline(backup, linea)) {
            if (linea == "=== CITAS PENDIENTES ===") {
                esCitaAceptada = false;
                continue;
            } else if (linea == "=== CITAS ACEPTADAS ===") {
                esCitaAceptada = true;
                continue;
            }

            if (!linea.empty()) {
                if (esCitaAceptada) {
                    citasAceptadas << linea << endl;
                } else {
                    citasPendientes << linea << endl;
                }
            }
        }

        backup.close();
        citasPendientes.close();
        citasAceptadas.close();
        return true;
    }

    void restaurarRespaldo() {
        bool volver = false;
        opcionSeleccionada = 0;

        while (!volver) {
            mostrarMenuRestaurar();
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 5) % 5;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 5;
                    break;
                case 13: // Enter
                    system("cls");
                    cout << "=== RESTAURAR RESPALDO ===" << endl;
                    switch(opcionSeleccionada) {
                        case 0: // Restaurar todo
                            {
                                bool exito = true;
                                
                                // Restaurar citas
                                if (restaurarCitas()) {
                                    cout << "Citas restauradas correctamente." << endl;
                                } else {
                                    cout << "Error al restaurar citas." << endl;
                                    exito = false;
                                }

                                // Restaurar doctores desde doctores_backup.txt
                                ifstream doctoresBackup("output/doctores_backup.txt");
                                ofstream doctoresRestore("output/doctores.txt", ios::trunc);
                                if (doctoresBackup && doctoresRestore) {
                                    doctoresRestore << doctoresBackup.rdbuf();
                                    cout << "Doctores restaurados correctamente." << endl;
                                } else {
                                    cout << "Error al restaurar doctores." << endl;
                                    exito = false;
                                }
                                doctoresBackup.close();
                                doctoresRestore.close();

                                // Restaurar pacientes desde pacientes_backup.txt
                                ifstream pacientesBackup("output/pacientes_backup.txt");
                                ofstream pacientesRestore("output/pacientes.txt", ios::trunc);
                                if (pacientesBackup && pacientesRestore) {
                                    pacientesRestore << pacientesBackup.rdbuf();
                                    cout << "Pacientes restaurados correctamente." << endl;
                                } else {
                                    cout << "Error al restaurar pacientes." << endl;
                                    exito = false;
                                }
                                pacientesBackup.close();
                                pacientesRestore.close();

                                if (exito) {
                                    cout << "\nTodos los archivos fueron restaurados exitosamente." << endl;
                                }
                            }
                            break;
                        
                        case 1: // Solo citas
                            if (restaurarCitas()) {
                                cout << "Citas restauradas correctamente desde citas_backup.txt" << endl;
                            } else {
                                cout << "Error: No se encontró el archivo citas_backup.txt" << endl;
                            }
                            break;
                        
                        case 2: // Solo doctores
                            {
                                ifstream backup("output/doctores_backup.txt");
                                ofstream restore("output/doctores.txt", ios::trunc);
                                if (backup && restore) {
                                    restore << backup.rdbuf();
                                    cout << "Doctores restaurados correctamente desde doctores_backup.txt" << endl;
                                } else {
                                    cout << "Error: No se encontró el archivo doctores_backup.txt" << endl;
                                }
                                backup.close();
                                restore.close();
                            }
                            break;
                        
                        case 3: // Solo pacientes
                            {
                                ifstream backup("output/pacientes_backup.txt");
                                ofstream restore("output/pacientes.txt", ios::trunc);
                                if (backup && restore) {
                                    restore << backup.rdbuf();
                                    cout << "Pacientes restaurados correctamente desde pacientes_backup.txt" << endl;
                                } else {
                                    cout << "Error: No se encontró el archivo pacientes_backup.txt" << endl;
                                }
                                backup.close();
                                restore.close();
                            }
                            break;
                        
                        case 4: // Volver
                            volver = true;
                            break;
                    }
                    if (!volver) {
                        system("pause");
                    }
                    break;
            }
        }
    }

    Lista menuPrincipal;
    Lista menuAdministrador;
    Lista menuPaciente;
    Lista menuDoctor;
    Lista menuEliminar;
    ArbolAVL arbol; // Agregar como miembro privado

    void inicializarMenus() {
        // Inicializar menú principal
        menuPrincipal.insertarOpcion("1. Administrador", 0);
        menuPrincipal.insertarOpcion("2. Doctor", 1);
        menuPrincipal.insertarOpcion("3. Paciente", 2);
        menuPrincipal.insertarOpcion("4. Salir", 3);

        // Inicializar menú administrador
        menuAdministrador.insertarOpcion("1. Eliminar informacion", 0);
        menuAdministrador.insertarOpcion("2. Modificar informacion", 1);
        menuAdministrador.insertarOpcion("3. Generar respaldo", 2);
        menuAdministrador.insertarOpcion("4. Restaurar respaldo", 3);
        menuAdministrador.insertarOpcion("5. Buscar informacion", 4);
        menuAdministrador.insertarOpcion("6. Volver al menu principal", 5);

        // Inicializar menú paciente
        menuPaciente.insertarOpcion("1. Agendar cita", 0);
        menuPaciente.insertarOpcion("2. Volver al menu principal", 1);

        // Inicializar menú doctor
        menuDoctor.insertarOpcion("1. Acceso Doctor", 0);
        menuDoctor.insertarOpcion("2. Registro Doctor", 1);
        menuDoctor.insertarOpcion("3. Volver al menu principal", 2);

        // Inicializar menú eliminar
        menuEliminar.insertarOpcion("1. Eliminar paciente por cedula", 0);
        menuEliminar.insertarOpcion("2. Eliminar doctor por cedula", 1);
        menuEliminar.insertarOpcion("3. Eliminar todas las citas", 2);
        menuEliminar.insertarOpcion("4. Eliminar todos los pacientes", 3);
        menuEliminar.insertarOpcion("5. Eliminar todos los doctores", 4);
        menuEliminar.insertarOpcion("6. Volver al menu administrador", 5);
    }

    // Modificar la función mostrarMenu para mantener el menú estático
    void mostrarMenu(const Lista& menu) {
        system("cls");
        cout << "=== MENU ===" << endl;
        Nodo* temp = menu.getActual();
        Nodo* primer = temp;
        
        // Primero encontramos el primer elemento
        while (temp->anterior != nullptr && temp->anterior != primer) {
            temp = temp->anterior;
        }
        
        // Mostramos todas las opciones en orden
        do {
            cout << (temp == menu.getActual() ? "> " : "  ") << temp->texto << endl;
            temp = temp->siguiente;
        } while (temp != nullptr && temp != primer);
    }

    // Agregar nueva función para mostrar menú de búsqueda
    void mostrarMenuBusqueda() {
        system("cls");
        cout << "=== MENU BUSQUEDA ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Buscar Paciente" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Buscar Doctor" << endl;
        cout << (opcionSeleccionada == 2 ? "> " : "  ") << "3. Volver" << endl;
    }

    void buscarInformacionPorCedula(const string& cedula) {
        bool encontrado = false;

        // Buscar en archivo de pacientes
        ifstream archivoPacientes("output/pacientes.txt");
        string linea;
        cout << "\nBuscando información...\n" << endl;

        // Verificar si es paciente
        bool esPaciente = false;
        while (getline(archivoPacientes, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                esPaciente = true;
                cout << "=== INFORMACIÓN DEL PACIENTE ===" << endl;
                cout << linea << endl; // Muestra la cédula
                
                // Mostrar las siguientes líneas con la información del paciente
                for (int i = 0; i < 4; i++) {
                    getline(archivoPacientes, linea);
                    cout << linea << endl;
                }
                break;
            }
        }
        archivoPacientes.close();

        // Buscar en archivo de doctores
        bool esDoctor = false;
        string especialidadDoctor;
        ifstream archivoDoctores("output/doctores.txt");
        while (getline(archivoDoctores, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontrado = true;
                esDoctor = true;
                cout << "\n=== INFORMACIÓN DEL DOCTOR ===" << endl;
                cout << linea << endl; // Muestra la cédula
                
                // Mostrar las siguientes líneas con la información del doctor
                for (int i = 0; i < 3; i++) {
                    getline(archivoDoctores, linea);
                    if (linea.find("Especialidad: ") != string::npos) {
                        especialidadDoctor = linea.substr(13);
                    }
                    cout << linea << endl;
                }
                break;
            }
        }
        archivoDoctores.close();

        // Buscar citas relacionadas
        if (esPaciente) {
            cout << "\n=== CITAS DEL PACIENTE ===" << endl;
            bool tieneCitas = false;

            // Buscar en citas pendientes
            cout << "\nCITAS PENDIENTES:" << endl;
            ifstream citasPendientes("output/cita.txt");
            string citaCompleta;
            bool dentroDeCita = false;
            while (getline(citasPendientes, linea)) {
                if (linea.find("=== RESUMEN DE LA CITA ===") != string::npos) {
                    citaCompleta = linea + "\n";
                    dentroDeCita = true;
                    continue;
                }
                if (dentroDeCita) {
                    citaCompleta += linea + "\n";
                    if (linea.find("Cedula: " + cedula) != string::npos) {
                        tieneCitas = true;
                        cout << "\n" << citaCompleta;
                    }
                    if (linea == "-------------------------") {
                        dentroDeCita = false;
                    }
                }
            }
            citasPendientes.close();

            // Buscar en citas aceptadas
            cout << "\nCITAS ACEPTADAS:" << endl;
            ifstream citasAceptadas("output/citas_aceptadas.txt");
            dentroDeCita = false;
            while (getline(citasAceptadas, linea)) {
                if (linea.find("=== RESUMEN DE LA CITA ===") != string::npos) {
                    citaCompleta = linea + "\n";
                    dentroDeCita = true;
                    continue;
                }
                if (dentroDeCita) {
                    citaCompleta += linea + "\n";
                    if (linea.find("Cedula: " + cedula) != string::npos) {
                        tieneCitas = true;
                        cout << "\n" << citaCompleta;
                    }
                    if (linea == "-------------------------") {
                        dentroDeCita = false;
                    }
                }
            }
            citasAceptadas.close();

            if (!tieneCitas) {
                cout << "No se encontraron citas para este paciente." << endl;
            }
        }

        if (esDoctor) {
            cout << "\n=== CITAS ASOCIADAS AL DOCTOR (Especialidad: " << especialidadDoctor << ") ===" << endl;
            bool tieneCitas = false;

            // Solo buscar en citas aceptadas
            ifstream citasAceptadas("output/citas_aceptadas.txt");
            string citaCompleta;
            bool dentroDeCita = false;
            
            while (getline(citasAceptadas, linea)) {
                if (linea.find("=== RESUMEN DE LA CITA ===") != string::npos) {
                    citaCompleta = linea + "\n";
                    dentroDeCita = true;
                    continue;
                }
                if (dentroDeCita) {
                    citaCompleta += linea + "\n";
                    if (linea.find("Cédula Doctor: " + cedula) != string::npos) {
                        tieneCitas = true;
                        cout << "\n" << citaCompleta;
                    }
                    if (linea == "-------------------------") {
                        dentroDeCita = false;
                    }
                }
            }
            citasAceptadas.close();

            if (!tieneCitas) {
                cout << "No se encontraron citas aceptadas para este doctor." << endl;
            }
        }

        if (!encontrado) {
            cout << "\nNo se encontró información para la cédula: " << cedula << endl;
        }
    }

    void realizarBusqueda() {
        bool volver = false;
        opcionSeleccionada = 0;

        while (!volver) {
            mostrarMenuBusqueda();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 3) % 3;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 3;
                    break;
                case 13: // Enter
                    if (opcionSeleccionada == 2) {
                        volver = true;
                    } else {
                        system("cls");
                        string cedula;
                        bool cedulaValida = false;

                        while (!cedulaValida) {
                            cedula.clear();
                            cout << "Ingrese la cedula a buscar: ";
                            char ch;
                            while ((ch = _getch()) != 13) {
                                if (ch == 8) { // Backspace
                                    if (!cedula.empty()) {
                                        cedula.pop_back();
                                        cout << "\b \b";
                                    }
                                } else if (ch >= '0' && ch <= '9' && cedula.length() < 10) {
                                    cedula += ch;
                                    cout << ch;
                                }
                            }
                            cout << endl;

                            if (cedula.empty()) {
                                cout << "Error: La cédula no puede estar vacía." << endl;
                                continue;
                            }

                            if (Validaciones::validarCedulaEcuatoriana(cedula)) {
                                cedulaValida = true;
                                // Llamar a la nueva función de búsqueda
                                buscarInformacionPorCedula(cedula);
                            } else {
                                cout << "Error: Cédula inválida." << endl;
                            }
                        }
                        system("pause");
                    }
                    break;
            }
        }
    }

    void mostrarCitasPaciente(const string& cedula) {
        ifstream archivoPendientes("output/cita.txt");
        ifstream archivoAceptadas("output/citas_aceptadas.txt");
        string linea;
        bool encontroCita = false;

        cout << "\nCitas del paciente:" << endl;
        cout << "\nCITAS PENDIENTES:" << endl;
        while (getline(archivoPendientes, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontroCita = true;
                cout << "\n=== CITA ===" << endl;
                cout << linea << endl;
                // Mostrar los detalles de la cita
                for (int i = 0; i < 5; i++) {
                    getline(archivoPendientes, linea);
                    cout << linea << endl;
                }
            }
        }

        cout << "\nCITAS ACEPTADAS:" << endl;
        while (getline(archivoAceptadas, linea)) {
            if (linea.find("Cédula: " + cedula) != string::npos) {
                encontroCita = true;
                cout << "\n=== CITA ===" << endl;
                cout << linea << endl;
                // Mostrar los detalles de la cita
                for (int i = 0; i < 5; i++) {
                    getline(archivoAceptadas, linea);
                    cout << linea << endl;
                }
            }
        }

        if (!encontroCita) {
            cout << "No se encontraron citas para este paciente." << endl;
        }

        archivoPendientes.close();
        archivoAceptadas.close();
    }

    void mostrarCitasDoctor(const string& cedula) {
        string fechaStr;
        bool fechaValida = false;

        while (!fechaValida) {
            fechaStr.clear();
            cout << "\nIngrese la fecha para consultar citas (DD-MM-YYYY): ";
            char ch;
            while ((ch = _getch()) != 13) {
                if (ch == 8) { // Backspace
                    if (!fechaStr.empty()) {
                        fechaStr.pop_back();
                        cout << "\b \b";
                    }
                } else if ((ch >= '0' && ch <= '9') || ch == '-') {
                    fechaStr += ch;
                    cout << ch;
                }
            }
            cout << endl;

            if (fechaStr.empty()) {
                cout << "Error: La fecha no puede estar vacía." << endl;
                continue;
            }

            if (Validaciones::validarFecha(fechaStr)) {
                fechaValida = true;
            } else {
                cout << "Error: Formato de fecha inválido. Use DD-MM-YYYY" << endl;
            }
        }

        // Mostrar citas para esa fecha
        ifstream archivoPendientes("output/cita.txt");
        ifstream archivoAceptadas("output/citas_aceptadas.txt");
        string linea;
        bool encontroCita = false;

        cout << "\nCitas para la fecha " << fechaStr << ":" << endl;
        cout << "\nCITAS PENDIENTES:" << endl;
        while (getline(archivoPendientes, linea)) {
            if (linea.find("Fecha de Cita: " + fechaStr) != string::npos) {
                encontroCita = true;
                // Retroceder al inicio de la cita
                for (int i = 0; i < 3; i++) {
                    archivoPendientes.seekg(-2, ios::cur);
                    while (archivoPendientes.tellg() > 0) {
                        archivoPendientes.seekg(-1, ios::cur);
                        if (archivoPendientes.get() == '\n') {
                            break;
                        }
                        archivoPendientes.seekg(-1, ios::cur);
                    }
                }
                // Mostrar la cita completa
                cout << "\n=== CITA ===" << endl;
                for (int i = 0; i < 6; i++) {
                    getline(archivoPendientes, linea);
                    cout << linea << endl;
                }
            }
        }

        cout << "\nCITAS ACEPTADAS:" << endl;
        while (getline(archivoAceptadas, linea)) {
            if (linea.find("Fecha de Cita: " + fechaStr) != string::npos) {
                encontroCita = true;
                // Retroceder al inicio de la cita
                for (int i = 0; i < 3; i++) {
                    archivoAceptadas.seekg(-2, ios::cur);
                    while (archivoAceptadas.tellg() > 0) {
                        archivoAceptadas.seekg(-1, ios::cur);
                        if (archivoAceptadas.get() == '\n') {
                            break;
                        }
                        archivoAceptadas.seekg(-1, ios::cur);
                    }
                }
                // Mostrar la cita completa
                cout << "\n=== CITA ===" << endl;
                for (int i = 0; i < 6; i++) {
                    getline(archivoAceptadas, linea);
                    cout << linea << endl;
                }
            }
        }

        if (!encontroCita) {
            cout << "No se encontraron citas para esta fecha." << endl;
        }

        archivoPendientes.close();
        archivoAceptadas.close();
    }

    


    // Add new method for PDF generation
    void generarPDFCitasAceptadas() {
        system("cls");
        cout << "=== GENERAR PDF DE CITAS ACEPTADAS ===" << endl;
        
        string nombreArchivo;
        cout << "Ingrese el nombre del archivo PDF (sin extension): ";
        cin >> nombreArchivo;
        nombreArchivo += ".pdf";
        
        if (PDFGenerator::generarPDFCitas(nombreArchivo)) {
            cout << "PDF generado correctamente en la carpeta output/" << nombreArchivo << endl;
        } else {
            cout << "Error al generar el PDF. Verifique que existan citas aceptadas." << endl;
        }
        
        system("pause");
    }

    // Add this new function to show the PDF menu
    void mostrarMenuPDF() {
        system("cls");
        cout << "=== MENU PDF ===" << endl;
        cout << (opcionSeleccionada == 0 ? "> " : "  ") << "1. Generar PDF de citas aceptadas" << endl;
        cout << (opcionSeleccionada == 1 ? "> " : "  ") << "2. Volver" << endl;
    }

public:
    Menu() {
        inicializarMenus();
    }

    // Modificar el método run para implementar navegación circular
    void run() {
        bool salir = false;
        while (!salir) {
            mostrarMenuPrincipal();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 4) % 4;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 4;
                    break;
                case 13: // Enter
                    switch(opcionSeleccionada) {
                        case 0: 
                            runAdministradorMenu();
                            break;
                        case 1:
                            runDoctorMenu();
                            break;
                        case 2:
                            runPacienteMenu();
                            break;
                        case 3:
                            salir = true;
                            break;
                    }
                    break;
            }
        }
        cout << "Saliendo del programa..." << endl;
        exit(0);
    }

    // Modificar los demás métodos run de manera similar
    void runAdministradorMenu() {
        bool volver = false;
        opcionSeleccionada = 0;
        while (!volver) {
            mostrarMenuAdministrador();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 7) % 7;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 7;
                    break;
                case 13: // Enter
                    switch(opcionSeleccionada) {
                        case 0:
                            runEliminarMenu();
                            break;
                        case 1:
                            modificarInformacion();
                            break;
                        case 2:
                            generarRespaldo();
                            break;
                        case 3:
                            restaurarRespaldo();
                            break;
                        case 4:
                            realizarBusqueda();
                            break;
                        case 5:
                            runPDFMenu(); // Add the new PDF menu
                            break;
                        case 6:
                            volver = true;
                            break;
                    }
                    break;
            }
        }
    }

    void runPacienteMenu() {
        bool volver = false;
        opcionSeleccionada = 0;
        while (!volver) {
            mostrarMenuPaciente();
            
            // Capturar la tecla presionada
            int key = _getch();
            if (key == 0 || key == 224) { 
                key = _getch();
            }
            
            switch (key) {
                case 72: // Flecha arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
                    break;
                case 80: // Flecha abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 2;
                    break;
                case 13: // Tecla Enter
                    if (opcionSeleccionada == 1) {
                        volver = true; // Volver al menu principal
                    } else if (opcionSeleccionada == 0) {
                        agendarCita(); // Usar el mismo metodo de agendar cita
                    }
                    break;
            }
        }
    }

    void runDoctorMenu() {
        bool volver = false;
        opcionSeleccionada = 0;
        while (!volver) {
            mostrarMenuOpcionesDoctor();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 3) % 3;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 3;
                    break;
                case 13: // Enter
                    switch(opcionSeleccionada) {
                        case 0:
                            accesoDoctor(); // La función original de acceso
                            break;
                        case 1:
                            registrarDoctor(); // La nueva función de registro
                            break;
                        case 2:
                            volver = true;
                            break;
                    }
                    break;
            }
        }
    }

    void runEliminarMenu() {
        bool volver = false;
        opcionSeleccionada = 0;
        while (!volver) {
            mostrarMenuEliminar();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 6) % 6;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 6;
                    break;
                case 13: // Enter
                    switch(opcionSeleccionada) {
                        case 0:
                            eliminarPaciente();
                            break;
                        case 1:
                            eliminarDoctor();
                            break;
                        case 2:
                            eliminarTodasCitas();
                            break;
                        case 3:
                            eliminarTodosPacientes();
                            break;
                        case 4:
                            eliminarTodosDoctores();
                            break;
                        case 5:
                            volver = true;
                            break;
                    }
                    break;
            }
        }
    }

    // Add new method to run the PDF menu
    void runPDFMenu() {
        bool volver = false;
        opcionSeleccionada = 0;
        while (!volver) {
            mostrarMenuPDF();
            
            int key = _getch();
            if (key == 0 || key == 224) key = _getch();
            
            switch (key) {
                case 72: // Arriba
                    opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
                    break;
                case 80: // Abajo
                    opcionSeleccionada = (opcionSeleccionada + 1) % 2;
                    break;
                case 13: // Enter
                    switch(opcionSeleccionada) {
                        case 0:
                            generarPDFCitasAceptadas();
                            break;
                        case 1:
                            volver = true;
                            break;
                    }
                    break;
            }
        }
    }

private:
    // Agregar variable miembro para almacenar la cédula del doctor actual
    string doctorActualCedula;

};

#endif // MENU_H