/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//main.cpp
#include "ListaCircular.cpp"
#include "ValidarPersona.cpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ListaCircular<Persona> lista_persona;
    ListaCircular<Persona> lista_auxiliar;

    // Insertar datos de ejemplo
    lista_persona.insertar(Persona("1234567890", "Carlos", "Garcia"));
    lista_persona.insertar(Persona("7890129874", "Ana", "Lopez"));
    lista_persona.insertar(Persona("4567892354", "Pedro", "Martinez"));
    lista_persona.insertar(Persona("6543216842", "Bruno", "Alvarez"));
    lista_persona.insertar(Persona("9876541325", "Luis", "Zapata"));

    int opcion;

    ValidarPersona ingresar_string;

    do {
        cout << "*********** Listas Simples ***********" << endl;
        cout << "1. Insertar Persona" << endl;
        cout << "2. Buscar Persona" << endl;
        cout << "3. Eliminar Persona" << endl;
        cout << "4. Cifrar Dato" << endl;
        cout << "5. Mostrar Lista" << endl;
        cout << "6. Reordenar lista de personas" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese una opción: ";
        opcion = ingresar_string.ingresar_entero('7');

        switch (opcion) {
        case 1: {
            char continuar;

            Persona sujeto;

            ingresar_string.ingresar_cedula("Ingrese la cédula: ", sujeto);
            ingresar_string.ingresar_nombre("Ingrese el nombre: ", sujeto);
            ingresar_string.ingresar_apellido("Ingrese el apellido: ", sujeto);

            lista_persona.insertar(sujeto);
            break;
        }
        case 2: {
            int op;
            std::string opcion;
            std::string criterio;

            cout << "**** Seleccione criterio de búsqueda ****" << endl;
            cout << "1. Cédula" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "Ingrese una opción: ";
            op = ingresar_string.ingresar_entero('3');
            if (op == 1) {
                opcion = "cedula";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio = ingresar_string.ingresar_cedula_sin_persona();
            } else if (op == 2) {
                opcion = "nombre";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio = ingresar_string.ingresar_nombre_sin_persona();
            } else if (op == 3) {
                opcion = "apellido";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio = ingresar_string.ingresar_apellido_sin_persona();
            }

            lista_persona.buscar(opcion, criterio);
            break;
        }
        case 3: {
            int op1;
            std::string opcion1;
            std::string criterio1;

            cout << "**** Seleccione criterio de búsqueda ****" << endl;
            cout << "1. Cédula" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "Ingrese una opción: ";
            op1 = ingresar_string.ingresar_entero('3');
           if (op1 == 1) {
                opcion1 = "cedula";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio1 = ingresar_string.ingresar_cedula_sin_persona();
            } else if (op1 == 2) {
                opcion1 = "nombre";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio1 = ingresar_string.ingresar_nombre_sin_persona();
            } else if (op1 == 3) {
                opcion1 = "apellido";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterio1 = ingresar_string.ingresar_apellido_sin_persona();
            }

            lista_persona.eliminar(opcion1, criterio1);
            break;
        }
        case 4:{
            int op2;
            std::string opcion2;
            char letra;
            int desplazamiento;

            cout << "**** Seleccione dato a cifrar ****" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "Ingrese una opción: ";
            op2 = ingresar_string.ingresar_entero('2');
           if (op2 == 1) {
                opcion2 = "nombre";
            } else if (op2 == 2) {
                opcion2 = "apellido";
            }

            cout << "**Ingrese la letra que desea desplazar**" << endl;
            letra=ingresar_string.leerLetra();
            //cin>>letra;

            cout << "**Ingrese el numero veces que desea depslazar la letra**" << endl;
            desplazamiento=ingresar_string.ingresar_desplazamiento(255);
            //cin>>desplazamiento;

            lista_persona.cifrar(opcion2,letra,desplazamiento,lista_auxiliar);
            break;

        }
        case 5:
            cout << "**Lista normal**" << endl;
            lista_persona.mostrar();
            cout << "**Lista cifrada**" << endl;
            lista_auxiliar.mostrar();
 
            break;
        case 6:
             int op3,orden;

            cout << "**** Seleccione criterio de ordenamiento****" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "3. Cédula" << endl;
            cout << "Ingrese una opción: ";
            op3 = ingresar_string.ingresar_entero('3');
            cout << "**** Seleccione tipo de orden****" << endl;
            cout << "1. Ascendente" << endl;
            cout << "2. Descendente" << endl;
            cout << "Ingrese una opción: ";
            orden=ingresar_string.ingresar_entero('2');

            lista_persona.ordenar(op3,orden);
            break;

        case 7:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    } while (opcion != 7);

    return 0;
}