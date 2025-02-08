#include "HashAbierto.h"
#include <iostream>
#include <graphics.h>
#include <thread>
#include <chrono>

template <typename T>
HashAbierto<T>::HashAbierto(int size) : size(size) {
    table.resize(size, nullptr);
}

template <typename T>
HashAbierto<T>::~HashAbierto() {
    for (int i = 0; i < size; ++i) {
        HashA_Nodo<T>* entry = table[i];
        while (entry != nullptr) {
            HashA_Nodo<T>* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
}

template <typename T>
int HashAbierto<T>::hashFunction(T key) {
    return std::hash<T>{}(key) % size;
}

// Specialization for std::string
template <>
int HashAbierto<std::string>::hashFunction(std::string key) {
    unsigned int hashValue = 0;

    // Procesar los caracteres de la cadena de derecha a izquierda
    for (int i = key.length() - 1; i >= 0; i--) {
        char c = key[i];
        unsigned int charBin = static_cast<unsigned int>(c);

        // Paso 1: Sumar el valor ASCII del carácter al hash
        hashValue += charBin;

        // Si no es el primer carácter, aplicar desplazamiento y XOR
        if (i > 0) {
            // Desplazar hashValue y aplicar XOR con los 4 bits más significativos de hashValue
            unsigned int firstFourBits = (hashValue >> 28) & 0xF; // Extraer los 4 bits más significativos
            hashValue = (hashValue << 4) ^ firstFourBits; // Desplazar y aplicar XOR con los primeros 4 bits
        }

        // Mostrar el hash parcial para depuración
        std::cout << "Char: " << c << " HashValue: " << hashValue << std::endl;
    }

    int finalHash = hashValue % size; // Calcular el índice final
    std::cout << "Final Hash for key \"" << key << "\": " << finalHash << std::endl;

    return finalHash;
}


template <typename T>
void HashAbierto<T>::insertar(T key) {
    int hashValue = hashFunction(key);
    
    // Crear un nuevo nodo con el valor a insertar
    HashA_Nodo<T>* newNode = new HashA_Nodo<T>(key);
    
    // Insertar el nuevo nodo al inicio de la lista enlazada
    newNode->next = table[hashValue];
    table[hashValue] = newNode;

    // Graficar la tabla hash después de insertar
    graficar();
}

template <typename T>
bool HashAbierto<T>::buscar(T key) {
    int hashValue = hashFunction(key);
    HashA_Nodo<T>* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->data == key) {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

template <typename T>
bool HashAbierto<T>::eliminar(T key) {
    int hashValue = hashFunction(key);
    HashA_Nodo<T>* prev = nullptr;
    HashA_Nodo<T>* entry = table[hashValue];

    // Buscar el nodo
    while (entry != nullptr && entry->data != key) {
        prev = entry;
        entry = entry->next;
    }

    // Si no encontramos el nodo
    if (entry == nullptr) {
        return false; // No se encontró el elemento
    } else {
        // Si es el primer nodo en la lista
        if (prev == nullptr) {
            table[hashValue] = entry->next;
        } else {
            prev->next = entry->next;
        }

        delete entry;  // Eliminar el nodo
        graficar();  // Graficar la tabla después de eliminar
        return true;  // El elemento fue eliminado exitosamente
    }
}


template <typename T>
void HashAbierto<T>::mostrar() {
    for (int i = 0; i < size; ++i) {
        HashA_Nodo<T>* entry = table[i];
        std::cout << "[" << i << "]";
        while (entry != nullptr) {
            std::cout << " -> " << entry->data;
            entry = entry->next;
        }
        std::cout << std::endl;
    }
}

template <typename T>
void HashAbierto<T>::graficar() {
    static bool isGraphInitialized = false;
    static int gd = DETECT, gm;

    if (!isGraphInitialized) {
        initgraph(&gd, &gm, "");
        isGraphInitialized = true;
    }

    int x = 20, y = getmaxy() - 50; // Position table at the bottom
    int cellWidth = 40, cellHeight = 20; // Smaller cell size

    cleardevice();

    // Draw table horizontally
    for (int i = 0; i < size; ++i) {
        rectangle(x + i * cellWidth, y, x + (i + 1) * cellWidth, y + cellHeight);
        line(x + i * cellWidth, y, x + (i + 1) * cellWidth, y + cellHeight); // Diagonal line
        std::string indexText = std::to_string(i);
        outtextxy(x + i * cellWidth + 5, y + 5, const_cast<char*>(indexText.c_str()));
    }

    // Draw numbers in table and connect with arrows
    for (int i = 0; i < size; ++i) {
        HashA_Nodo<T>* entry = table[i];
        int offsetY = y - cellHeight - 10;
        int prevX = x + i * cellWidth + cellWidth / 2, prevY = y;
        while (entry != nullptr) {
            std::string text = std::to_string(entry->data);
            rectangle(x + i * cellWidth, offsetY, x + (i + 1) * cellWidth, offsetY + cellHeight); // Node rectangle
            outtextxy(x + i * cellWidth + 5, offsetY + 5, const_cast<char*>(text.c_str()));
            line(prevX, prevY, x + i * cellWidth + cellWidth / 2, offsetY + cellHeight); // Draw arrow
            prevY = offsetY;
            offsetY -= cellHeight + 10;
            entry = entry->next;
        }
    }

    delay(500); // Small delay to update the graph
}

// Specialization for std::string
template <>
void HashAbierto<std::string>::graficar() {
    static bool isGraphInitialized = false;
    static int gd = DETECT, gm;

    if (!isGraphInitialized) {
        initgraph(&gd, &gm, "");
        isGraphInitialized = true;
    }

    int x = 20, y = getmaxy() - 50; // Position table at the bottom
    int cellWidth = 40, cellHeight = 20; // Smaller cell size

    cleardevice();

    // Draw table horizontally
    for (int i = 0; i < size; ++i) {
        rectangle(x + i * cellWidth, y, x + (i + 1) * cellWidth, y + cellHeight);
        line(x + i * cellWidth, y, x + (i + 1) * cellWidth, y + cellHeight); // Diagonal line
        std::string indexText = std::to_string(i);
        outtextxy(x + i * cellWidth + 5, y + 5, const_cast<char*>(indexText.c_str()));
    }

    // Draw strings in table and connect with arrows
    for (int i = 0; i < size; ++i) {
        HashA_Nodo<std::string>* entry = table[i];
        int offsetY = y - cellHeight - 10;
        int prevX = x + i * cellWidth + cellWidth / 2, prevY = y;
        while (entry != nullptr) {
            rectangle(x + i * cellWidth, offsetY, x + (i + 1) * cellWidth, offsetY + cellHeight); // Node rectangle
            outtextxy(x + i * cellWidth + 5, offsetY + 5, const_cast<char*>(entry->data.c_str()));
            line(prevX, prevY, x + i * cellWidth + cellWidth / 2, offsetY + cellHeight); // Draw arrow
            prevY = offsetY;
            offsetY -= cellHeight + 10;
            entry = entry->next;
        }
    }

    delay(500); // Small delay to update the graph
}

// Explicit template instantiation
template class HashAbierto<int>;
template class HashAbierto<std::string>;
