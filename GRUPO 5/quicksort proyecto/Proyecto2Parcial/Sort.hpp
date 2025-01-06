#include "ILista.hpp"
#include <iostream>
#include <functional>

namespace Sort
{
    template<typename T, typename U>
    void bubbleSortObj(ILista<T>& lista, std::function<U (const T&)> atributeGetter, bool creciente = true);

    template<typename T>
    void bubbleSort(ILista<T>& lista, bool creciente = true);

        // QuickSort
    template<typename T, typename U>
    void quickSortObj(ILista<T>& lista, std::function<U (const T&)> atributeGetter, bool creciente = true);
    
    template<typename T>
    void quickSort(ILista<T>& lista, bool creciente = true);

    // Funciones auxiliares privadas para QuickSort
    template<typename T, typename U>
    void quickSortObjRecursivo(ILista<T>& lista, int inicio, int fin, 
                              std::function<U (const T&)> atributeGetter, bool creciente);
    
    template<typename T, typename U>
    int particionObj(ILista<T>& lista, int inicio, int fin, 
                     std::function<U (const T&)> atributeGetter, bool creciente);
    
    template<typename T>
    void quickSortRecursivo(ILista<T>& lista, int inicio, int fin, bool creciente);
    
    template<typename T>
    int particion(ILista<T>& lista, int inicio, int fin, bool creciente);
}

template<typename T, typename U>
void Sort::bubbleSortObj(ILista<T>& lista, std::function<U (const T&)> atributeGetter, bool creciente)
{
    int n = lista.contar();
    bool haCambiado = false;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (creciente)
            {
                if (atributeGetter(lista.conseguirDato(j)) > atributeGetter(lista.conseguirDato(j + 1)))
                {
                    lista.intercambiar(j, j + 1);
                    haCambiado = true;
                }
            }
            else
            {
                if (atributeGetter(lista.conseguirDato(j)) < atributeGetter(lista.conseguirDato(j + 1)))
                {
                    lista.intercambiar(j, j + 1);
                    haCambiado = true;
                }
            }
        }

        if (!haCambiado)
            break;
    }
}

template<typename T>
void Sort::bubbleSort(ILista<T>& lista, bool creciente)
{
    int n = lista.contar();
    bool haCambiado = false;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (creciente)
            {
                if (lista.conseguirDato(j) > lista.conseguirDato(j + 1))
                {
                    lista.intercambiar(j, j + 1);
                    haCambiado = true;
                }
            }
            else
            {
                if (lista.conseguirDato(j) < lista.conseguirDato(j + 1))
                {
                    lista.intercambiar(j, j + 1);
                    haCambiado = true;
                }
            }
        }

        if (!haCambiado)
            break;
    }
}

//Quicksort
template<typename T, typename U>
void Sort::quickSortObj(ILista<T>& lista, std::function<U (const T&)> atributeGetter, bool creciente) {
    quickSortObjRecursivo(lista, 0, lista.contar() - 1, atributeGetter, creciente);
}

template<typename T, typename U>
void Sort::quickSortObjRecursivo(ILista<T>& lista, int inicio, int fin, 
                                std::function<U (const T&)> atributeGetter, bool creciente) {
    if (inicio < fin) {
        int pivote = particionObj(lista, inicio, fin, atributeGetter, creciente);
        quickSortObjRecursivo(lista, inicio, pivote - 1, atributeGetter, creciente);
        quickSortObjRecursivo(lista, pivote + 1, fin, atributeGetter, creciente);
    }
}

template<typename T, typename U>
int Sort::particionObj(ILista<T>& lista, int inicio, int fin, 
                      std::function<U (const T&)> atributeGetter, bool creciente) {
    U pivote = atributeGetter(lista.conseguirDato(fin));
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (creciente) {
            if (atributeGetter(lista.conseguirDato(j)) <= pivote) {
                i++;
                lista.intercambiar(i, j);
            }
        } else {
            if (atributeGetter(lista.conseguirDato(j)) >= pivote) {
                i++;
                lista.intercambiar(i, j);
            }
        }
    }
    lista.intercambiar(i + 1, fin);
    return i + 1;
}

// Implementación de QuickSort simple
template<typename T>
void Sort::quickSort(ILista<T>& lista, bool creciente) {
    quickSortRecursivo(lista, 0, lista.contar() - 1, creciente);
}

template<typename T>
void Sort::quickSortRecursivo(ILista<T>& lista, int inicio, int fin, bool creciente) {
    if (inicio < fin) {
        int pivote = particion(lista, inicio, fin, creciente);
        quickSortRecursivo(lista, inicio, pivote - 1, creciente);
        quickSortRecursivo(lista, pivote + 1, fin, creciente);
    }
}

template<typename T>
int Sort::particion(ILista<T>& lista, int inicio, int fin, bool creciente) {
    T pivote = lista.conseguirDato(fin);
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (creciente) {
            if (lista.conseguirDato(j) <= pivote) {
                i++;
                lista.intercambiar(i, j);
            }
        } else {
            if (lista.conseguirDato(j) >= pivote) {
                i++;
                lista.intercambiar(i, j);
            }
        }
    }
    lista.intercambiar(i + 1, fin);
    return i + 1;
}
Last edited 
