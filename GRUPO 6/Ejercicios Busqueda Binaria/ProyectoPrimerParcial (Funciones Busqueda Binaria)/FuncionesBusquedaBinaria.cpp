#include "FuncionesBusquedaBinaria.h"

void FuncionesBusquedaBinaria::ordenarPorTitulo(ListaCircularDoble& lista) {
    if (!lista.getCabeza() || lista.getCabeza()->siguiente == lista.getCabeza()) {
        return;
    }

    bool intercambio;
    Nodo* actual;
    Nodo* ultimo = nullptr;

    do {
        intercambio = false;
        actual = lista.getCabeza();

        do {
            string tituloActual = actual->libro.getTitulo();
            string tituloSiguiente = actual->siguiente->libro.getTitulo();
            
            // Convertir a minúsculas para comparación
            transform(tituloActual.begin(), tituloActual.end(), tituloActual.begin(), ::tolower);
            transform(tituloSiguiente.begin(), tituloSiguiente.end(), tituloSiguiente.begin(), ::tolower);

            if (tituloActual > tituloSiguiente) {
                // Intercambiar libros
                Libro temp = actual->libro;
                actual->libro = actual->siguiente->libro;
                actual->siguiente->libro = temp;
                intercambio = true;
            }
            actual = actual->siguiente;
        } while (actual->siguiente != lista.getCabeza());

    } while (intercambio);
}

bool FuncionesBusquedaBinaria::estaOrdenada(const ListaCircularDoble& lista) {
    if (!lista.getCabeza() || lista.getCabeza()->siguiente == lista.getCabeza()) {
        return true;
    }
    
    Nodo* actual = lista.getCabeza();
    do {
        string tituloActual = actual->libro.getTitulo();
        string tituloSiguiente = actual->siguiente->libro.getTitulo();
        transform(tituloActual.begin(), tituloActual.end(), tituloActual.begin(), ::tolower);
        transform(tituloSiguiente.begin(), tituloSiguiente.end(), tituloSiguiente.begin(), ::tolower);
        
        if (tituloActual > tituloSiguiente) {
            return false;
        }
        actual = actual->siguiente;
    } while (actual->siguiente != lista.getCabeza());
    
    return true;
}

bool FuncionesBusquedaBinaria::comparaPrefijo(const string& str, const string& prefijo) {
    if (str.length() < prefijo.length()) return false;
    return str.substr(0, prefijo.length()) == prefijo;
}

int FuncionesBusquedaBinaria::contarNodos(const ListaCircularDoble& lista) {
    if (!lista.getCabeza()) return 0;
    int count = 0;
    Nodo* actual = lista.getCabeza();
    do {
        count++;
        actual = actual->siguiente;
    } while (actual != lista.getCabeza());
    return count;
}

Nodo* FuncionesBusquedaBinaria::obtenerNodoPorIndice(const ListaCircularDoble& lista, int indice) {
    if (!lista.getCabeza()) return nullptr;
    Nodo* actual = lista.getCabeza();
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }
    return actual;
}


void FuncionesBusquedaBinaria::buscarPorPrefijo(const ListaCircularDoble& lista, const string& prefijo) {
    if (!lista.getCabeza() || prefijo.empty()) {
        cout << "No hay libros registrados o el prefijo está vacío." << endl;
        return;
    }

    // Verificar y ordenar si es necesario
    if (!estaOrdenada(lista)) {
        ordenarPorTitulo(const_cast<ListaCircularDoble&>(lista));
    }

    // Convertir prefijo a minúsculas una sola vez
    string prefijoLower = prefijo;
    transform(prefijoLower.begin(), prefijoLower.end(), prefijoLower.begin(), ::tolower);

    int n = contarNodos(lista);
    int izq = 0;
    int der = n - 1;
    int primerIndice = -1;

    // Buscar la primera ocurrencia del prefijo
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        Nodo* nodoMedio = obtenerNodoPorIndice(lista, medio);
        string tituloMedio = nodoMedio->libro.getTitulo();
        string tituloLower = tituloMedio;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        bool esPrefijo = tituloLower.compare(0, prefijoLower.length(), prefijoLower) == 0;
        bool esIgualOMayor = tituloLower.compare(0, prefijoLower.length(), prefijoLower) >= 0;

        if (esPrefijo) {
            primerIndice = medio;
            der = medio - 1; // Seguir buscando hacia la izquierda
        } else if (!esIgualOMayor) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    if (primerIndice == -1) {
        cout << "No se encontraron coincidencias con el prefijo '" << prefijo << "'." << endl;
        return;
    }

    // Imprimir encabezado
    cout << "Libros encontrados con el prefijo '" << prefijo << "':" << endl;
    cout << left << setw(41) << "Título" 
        << setw(25) << "Autor" 
        << setw(25) << "ISNI" 
        << setw(20) << "ISBN"
        << setw(15) << "Publicación" 
        << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;

    // Mostrar todos los libros que coinciden con el prefijo
    for (int i = primerIndice; i < n; i++) {
        Nodo* nodo = obtenerNodoPorIndice(lista, i);
        string titulo = nodo->libro.getTitulo();
        string tituloLower = titulo;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (tituloLower.compare(0, prefijoLower.length(), prefijoLower) != 0) {
            break;
        }

        cout << left << setw(40) << titulo
            << setw(25) << nodo->libro.getAutor().getNombre()
            << setw(25) << nodo->libro.getAutor().getIsni()
            << setw(20) << nodo->libro.getIsbn()
            << setw(15) << nodo->libro.getFechaPublicacion().mostrar()
            << setw(15) << nodo->libro.getAutor().getFechaNacimiento().mostrar() << endl;
    }
}