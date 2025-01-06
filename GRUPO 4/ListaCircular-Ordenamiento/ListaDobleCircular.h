 #ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H

#include <iostream>
#include "Libro.h"
#include "Autor.h"
#include "Fecha.h"

using namespace std;

template <typename T>
class Nodo
{
public:
    T dato;
    Nodo *siguiente;
    Nodo *anterior;

    Nodo(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDobleCircular
{
private:
    Nodo<T> *cabeza;

public:
    ListaDobleCircular() : cabeza(nullptr) {}

    // Verifica si la lista está vacía
    bool vacia() const
    {
        return cabeza == nullptr;
    }

    // Insertar al final de la lista
    void insertar(const T &dato)
    {
        Nodo<T> *nuevoNodo = new Nodo<T>(dato);
        if (vacia())
        {
            cabeza = nuevoNodo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        }
        else
        {
            Nodo<T> *ultimo = cabeza->anterior;
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->anterior = ultimo;
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
        }
    }

    // Buscar un dato en la lista
    Nodo<T> *buscar(const T &dato) const
    {
        if (vacia())
            return nullptr;

        Nodo<T> *actual = cabeza;
        do
        {
            if (actual->dato == dato)
            {
                return actual;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        return nullptr;
    }

    void eliminar(const T &dato)
    {
        if (vacia())
            return;

        Nodo<T> *actual = cabeza;

        do
        {
            if (actual->dato == dato)
            {
                if (actual->siguiente == actual)
                {
                    // Caso especial: solo un nodo en la lista
                    delete actual;
                    cabeza = nullptr;
                }
                else
                {
                    if (actual == cabeza)
                    {
                        cabeza = cabeza->siguiente;
                    }
                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;
                    delete actual;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Imprimir los elementos de la lista
    void imprimir() const
    {
        if (vacia())
        {
            cout << "La lista esta vacia.\n";
            return;
        }

        Nodo<T> *actual = cabeza;
        do
        {
            // Si el tipo de dato es Libro, se llama a imprimirLibro()
            if constexpr (std::is_same<T, Libro>::value)
            {
                actual->dato.imprimirLibro(); // Llama a imprimirLibro() de la clase Libro
            }
            else if constexpr (std::is_same<T, Autor>::value)
            {
                actual->dato.imprimirAutor(); // Llama a imprimirAutor() de la clase Autor
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Destructor para liberar memoria
    ~ListaDobleCircular()
    {
        if (vacia())
            return;

        Nodo<T> *actual = cabeza;
        do
        {
            Nodo<T> *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }

    // Getter for the head of the list (cabeza)
    Nodo<T> *getCabeza() const
    {
        return cabeza;
    }

    void clear()
    {
        if (vacia())
            return;

        Nodo<T> *actual = cabeza;
        do
        {
            Nodo<T> *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);

        cabeza = nullptr; // Set the head to nullptr to indicate the list is now empty
    }

    void actualizarAutorEnLibros(const Autor &autorEliminado)
    {
        if (vacia())
            return;

        Nodo<T> *actual = cabeza;
        do
        {
            if constexpr (std::is_same<T, Libro>::value)
            {
                if (actual->dato.getAutor().getCedula() == autorEliminado.getCedula())
                {
                    Autor sinAutor("-----", "Sin autor", "", "", Fecha()); // Autor genérico
                    actual->dato.setAutor(sinAutor);                            // Actualiza el autor del libro
                }
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

void eliminarLibrosPorAutor(const Autor &autorEliminado) {
    if (vacia())
        return;

    Nodo<T> *actual = cabeza;
    bool completedLoop = false;

    while (!completedLoop) {
        Nodo<T> *siguienteNodo = actual->siguiente; // Save the next node
        completedLoop = (actual->siguiente == cabeza); // Check if the next node is back to the head

        if constexpr (std::is_same<T, Libro>::value) {
            if (actual->dato.getAutor().getCedula() == autorEliminado.getCedula()) {
                eliminarNodo(actual); // Remove the current node
            }
        }

        actual = siguienteNodo; // Move to the next node
    }
}

// Helper method to remove a node
void eliminarNodo(Nodo<T> *nodoAEliminar) {
    if (!nodoAEliminar)
        return;

    // Handle case where the list has only one node
    if (nodoAEliminar == cabeza && nodoAEliminar->siguiente == cabeza) {
        delete nodoAEliminar;
        cabeza = nullptr;
        return;
    }

    // Update pointers of the previous and next nodes
    nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
    nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;

    // Update cabeza if needed
    if (nodoAEliminar == cabeza) {
        cabeza = nodoAEliminar->siguiente;
    }

    delete nodoAEliminar;
}



Libro *buscarId(int id)
{
    if (vacia())
        return nullptr;

    Nodo<Libro> *actual = cabeza;
    do
    {
        if (actual->dato.getId() == id)
        {
            return &actual->dato; // Return a pointer to the matching Libro
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr; // Return nullptr if no match is found
}


Autor *buscarCedula(const std::string &cedula)
{
    if (vacia())
        return nullptr;

    Nodo<T> *actual = cabeza;
    do
    {
        if constexpr (std::is_same<T, Autor>::value)
        {
            if (actual->dato.getCedula() == cedula)
            {
                return &actual->dato; // Return a pointer to the matching Autor
            }
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr; // Return nullptr if no match is found
}




};

#endif // LISTADOBLECIRCULAR_H
