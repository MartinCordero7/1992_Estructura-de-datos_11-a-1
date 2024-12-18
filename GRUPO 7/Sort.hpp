#include "ILista.hpp"
#include <iostream>
namespace Sort
{
    template<typename T, typename U>
    void bubbleSortObj(ILista<T>& lista, U(*atributeGetter)(void));

    template<typename T>
    void bubbleSort(ILista<T>& lista);
}

template<typename T, typename U>
void Sort::bubbleSortObj(ILista<T>& lista, U(*atributeGetter)(T))
{
    int n = lista.contar();
    bool haCambiado = false;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (atributeGetter(lista.conseguirDato(j)) > atributeGetter(lista.conseguirDato(j + 1)))
            {
                lista.intercambiar(j, j + 1);
                haCambiado = true;
            }
        }

        if (!haCambiado)
            break;
    }
}

template<typename T>
void Sort::bubbleSort(ILista<T>& lista)
{
    int n = lista.contar();
    bool haCambiado = false;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (lista.conseguirDato(j) > lista.conseguirDato(j + 1))
            {
                lista.intercambiar(j, j + 1);
                haCambiado = true;
            }
        }

        if (!haCambiado)
            break;
    }
}

