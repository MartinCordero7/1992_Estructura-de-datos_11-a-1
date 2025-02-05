#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <graphics.h>
#include <limits>
#include <string>
#include <functional>
#include <sstream>

template <typename T>
class HashTable {
private:
    int size;
    std::vector<std::list<T>> table;

    // Funcion hash para cualquier tipo de dato
    int hashFunction(const T& key) {
        std::hash<T> hashFunc;
        return hashFunc(key) % size;
    }

public:
    HashTable(int tableSize) : size(tableSize) {
        table.resize(size);
    }

    // Insertar un valor en la tabla hash
    void insert(const T& key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    // Buscar un valor en la tabla hash
    bool search(const T& key) {
        int index = hashFunction(key);
        for (const T& value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }

    // Eliminar un valor de la tabla hash
    void remove(const T& key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    // Mostrar la tabla hash
    void display() const {
        for (int i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const T& value : table[i]) {
                std::cout << value << " -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }

    // Verificar si la tabla hash esta vacia
    bool isEmpty() const {
        for (const auto& bucket : table) {
            if (!bucket.empty()) {
                return false;
            }
        }
        return true;
    }

    // Contar el numero de elementos en la tabla hash
    size_t count() const {
        size_t total = 0;
        for (const auto& bucket : table) {
            total += bucket.size();
        }
        return total;
    }

    // Limpiar la tabla hash
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }

    // Dibuja la tabla hash
    void draw() const {
        int gd = DETECT, gm;
        initwindow(getmaxwidth(), getmaxheight(), "Hash Table");

        int x = 50, y = 50;
        for (int i = 0; i < size; ++i) {
            rectangle(x, y, x + 100, y + 50);
            std::ostringstream oss;
            oss << "N " << i;
            outtextxy(x + 5, y + 10, const_cast<char*>(oss.str().c_str()));
            int valueX = x + 120;
            for (const T& value : table[i]) {
                rectangle(valueX, y, valueX + 100, y + 50);
                std::ostringstream valueOss;
                valueOss << value;
                outtextxy(valueX + 10, y + 20, const_cast<char*>(valueOss.str().c_str()));
                valueX += 120;
            }
            y += 70;
        }

        getch();
        closegraph();
    }

    // Guardar la tabla hash en un archivo
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << size << std::endl;
            for (const auto& bucket : table) {
                for (const T& value : bucket) {
                    outFile << value << " ";
                }
                outFile << std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "No se pudo abrir el archivo para guardar." << std::endl;
        }
    }

    // Cargar la tabla hash desde un archivo
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            inFile >> size;
            table.clear();
            table.resize(size);
            T value;
            for (auto& bucket : table) {
                while (inFile >> value) {
                    bucket.push_back(value);
                    if (inFile.peek() == '\n') break;
                }
            }
            inFile.close();
        } else {
            std::cerr << "No se pudo abrir el archivo para cargar." << std::endl;
        }
    }
};

void menu(HashTable<int>& htInt, HashTable<std::string>& htString) {
    int choice, intValue;
    std::string strValue;
    std::string filenameInt = "hash_table_data_int.txt";
    std::string filenameString = "hash_table_data_string.txt";

    htInt.loadFromFile(filenameInt);
    htString.loadFromFile(filenameString);

    do {
        std::cout << "\n--- Menu de Tabla Hash ---" << std::endl;
        std::cout << "1. Insertar un valor entero" << std::endl;
        std::cout << "2. Buscar un valor entero" << std::endl;
        std::cout << "3. Eliminar un valor entero" << std::endl;
        std::cout << "4. Mostrar tabla hash de enteros" << std::endl;
        std::cout << "5. Insertar un valor string" << std::endl;
        std::cout << "6. Buscar un valor string" << std::endl;
        std::cout << "7. Eliminar un valor string" << std::endl;
        std::cout << "8. Mostrar tabla hash de strings" << std::endl;
        std::cout << "9. Dibujar tabla hash de enteros" << std::endl;
        std::cout << "10. Dibujar tabla hash de strings" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Elige una opcion: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Ingresa un valor entero a insertar: ";
                std::cin >> intValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                htInt.insert(intValue);
                break;
            case 2:
                std::cout << "Ingresa un valor entero a buscar: ";
                std::cin >> intValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                if (htInt.search(intValue)) {
                    std::cout << intValue << " encontrado en la tabla hash." << std::endl;
                } else {
                    std::cout << intValue << " no encontrado en la tabla hash." << std::endl;
                }
                break;
            case 3:
                std::cout << "Ingresa un valor entero a eliminar: ";
                std::cin >> intValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                htInt.remove(intValue);
                std::cout << "Valor " << intValue << " eliminado." << std::endl;
                break;
            case 4:
                std::cout << "Tabla Hash de Enteros:" << std::endl;
                htInt.display();
                break;
            case 5:
                std::cout << "Ingresa un valor string a insertar: ";
                std::cin >> strValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                htString.insert(strValue);
                break;
            case 6:
                std::cout << "Ingresa un valor string a buscar: ";
                std::cin >> strValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                if (htString.search(strValue)) {
                    std::cout << strValue << " encontrado en la tabla hash." << std::endl;
                } else {
                    std::cout << strValue << " no encontrado en la tabla hash." << std::endl;
                }
                break;
            case 7:
                std::cout << "Ingresa un valor string a eliminar: ";
                std::cin >> strValue;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Valor no valido. Intenta de nuevo." << std::endl;
                    break;
                }
                htString.remove(strValue);
                std::cout << "Valor " << strValue << " eliminado." << std::endl;
                break;
            case 8:
                std::cout << "Tabla Hash de Strings:" << std::endl;
                htString.display();
                break;
            case 9:
                std::cout << "Dibujando tabla hash de enteros:" << std::endl;
                htInt.draw();
                std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
            case 10:
                std::cout << "Dibujando tabla hash de strings:" << std::endl;
                htString.draw();
                std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
            case 0:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
        }

        htInt.saveToFile(filenameInt);
        htString.saveToFile(filenameString);

    } while (choice != 0);
}