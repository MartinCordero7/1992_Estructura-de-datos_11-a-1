#include "BTree.h"

#include <functional> // Include this header for std::function
#include <queue>      // Include this header for std::queue

BTree::BTree(int _t) {
    try {
        root = nullptr;
        t = _t;
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

BTree::~BTree() {  // Destructor para liberar memoria
    try {
        delete root;
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::insert(int k) {
    try {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(k);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->children.push_back(root);
                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->children[i]->insertNonFull(k);
                root = s;
            } else {
                root->insertNonFull(k);
            }
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::traverse() {
    try {
        if (root != nullptr)
            root->traverse();
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

BTreeNode* BTree::search(int k) {
    try {
        return (root == nullptr) ? nullptr : root->search(k);
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
        return nullptr;
    }
}

void BTree::remove(int k) {
    try {
        if (!root) {
            cout << "El arbol esta vacio.\n";
            return;
        }

        root->remove(k);

        if (root->keys.size() == 0) {
            BTreeNode* tmp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->children[0];

            delete tmp;
        }

        // Guardar cambios en el archivo
        saveToFile("datos.txt");
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::saveToFile(const string &filename) {
    try {
        ofstream file(filename);
        if (file.is_open()) {
            if (root != nullptr)
                root->saveToFile(file); // Save the tree structure
            file.close();
        } else {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

// Nueva función para imprimir el árbol en consola
void BTree::imprimirArbol() {
    try {
        if (!root) {
            std::cout << "El arbol esta vacio." << std::endl;
            return;
        }
        imprimirNodo(root, 0);
        std::cout << "Altura del arbol: " << calcularAltura() << std::endl;
        imprimirNiveles();
        imprimirProfundidades();
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirNodo(BTreeNode* nodo, int nivel) {
    try {
        if (!nodo) return;

        const int ESPACIO_INCREMENTO = 4;
        std::string espacio(nivel * ESPACIO_INCREMENTO, ' ');

        std::cout << espacio << "--[";
        for (size_t i = 0; i < nodo->keys.size(); ++i) {
            std::cout << nodo->keys[i];
            if (i < nodo->keys.size() - 1) std::cout << ", ";
        }
        std::cout << "]--" << std::endl;

        for (BTreeNode* child : nodo->children) {
            imprimirNodo(child, nivel + 1);
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

int BTree::calcularAltura() {
    try {
        return calcularAlturaNodo(root);
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 0;
    }
}

int BTree::calcularAlturaNodo(BTreeNode* nodo) {
    try {
        if (!nodo) return 0;
        int altura = 0;
        for (BTreeNode* child : nodo->children) {
            altura = std::max(altura, calcularAlturaNodo(child));
        }
        return altura + 1;
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 0;
    }
}

void BTree::imprimirNiveles() {
    try {
        int altura = calcularAltura();
        for (int i = 0; i < altura; ++i) {
            std::cout << "Nivel " << i << ": ";
            imprimirNivelNodo(root, i);
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirNivelNodo(BTreeNode* nodo, int nivel) {
    try {
        if (!nodo) return;
        if (nivel == 0) {
            for (const auto& clave : nodo->keys) {
                std::cout << clave << " ";
            }
        } else {
            for (BTreeNode* child : nodo->children) {
                imprimirNivelNodo(child, nivel - 1);
            }
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirProfundidades() {
    try {
        imprimirProfundidadNodo(root, 0);
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirProfundidadNodo(BTreeNode* nodo, int profundidad) {
    try {
        if (!nodo) return;
        std::cout << "Profundidad del nodo con claves [";
        for (size_t i = 0; i < nodo->keys.size(); ++i) {
            std::cout << nodo->keys[i];
            if (i < nodo->keys.size() - 1) std::cout << ", ";
        }
        std::cout << "] es: " << profundidad << std::endl;
        for (BTreeNode* child : nodo->children) {
            imprimirProfundidadNodo(child, profundidad + 1);
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirArbolDetallado() {
    try {
        if (!root) {
            std::cout << "El arbol esta vacio." << std::endl;
            return;
        }
        imprimirNodoDetallado(root, 0, "raiz");
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void BTree::imprimirNodoDetallado(BTreeNode* nodo, int nivel, const std::string& posicion) {
    try {
        if (!nodo) return;

        const int ESPACIO_INCREMENTO = 4;
        std::string espacio(nivel * ESPACIO_INCREMENTO, ' ');

        std::cout << espacio << "--[" << posicion << "]-- ";
        for (size_t i = 0; i < nodo->keys.size(); ++i) {
            std::cout << nodo->keys[i];
            if (i < nodo->keys.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < nodo->children.size(); ++i) {
            std::string nuevaPosicion = (i == 0) ? "izquierda" : (i == nodo->children.size() - 1) ? "derecha" : "compartido";
            imprimirNodoDetallado(nodo->children[i], nivel + 1, nuevaPosicion);
        }
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

BTreeNode* BTree::getRoot() {
    return root;
}