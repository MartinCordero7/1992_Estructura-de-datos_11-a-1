/*********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNOS: Xavier Altamirano, Martin Cordero, Isaac Oña
 * FECHA CREACION: Viernes, 31 de Enero de 2025
 * FECHA MODIFICACION: Lunes, 03 de Febrero de 2025
 * Enunciado del problema: Splaytree
 * Nivel: TERCERO     NRC: 1992
 *********/
#include <iostream>
#include <iomanip>
#include "node.cpp"
#include <graphics.h> 
#include <windows.h> 
using namespace std;

// Función global para obtener resolución
void obtenerResolucion(int &ancho, int &alto) {
    ancho = GetSystemMetrics(SM_CXSCREEN);
    alto = GetSystemMetrics(SM_CYSCREEN);
}

class SplayTree {
private:
    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        // Recursividad
        if (root == nullptr || root->key == key)
            return root;

        if (key < root->key) {
            if (root->left == nullptr) return root;

            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key >= root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        } else {
            if (root->right == nullptr) return root;

            if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            } else if (key >= root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    void printTree(Node* root, int space) {
        // Recursividad
        const int COUNT = 5;
        if (root == nullptr)
            return;

        space += COUNT;
        printTree(root->right, space);

        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << root->key << "\n";

        printTree(root->left, space);
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);

        root = splay(root, key);

        Node* newNode = new Node(key);

        if (key <= root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        return newNode;
    }

    void recursiveInsert(Node*& root, int key) {
        // Recursividad
        root = insert(root, key);
    }

    void recursiveDisplay(Node* node, int space) {
        // Recursividad
        printTree(node, space);
    }

    int height(Node* node) {
        // Recursividad
        if (node == nullptr) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    int depth(Node* node, int key, int currentDepth = 0) {
        // Recursividad
        if (node == nullptr) return -1;
        if (node->key == key) return currentDepth;
        if (key < node->key) return depth(node->left, key, currentDepth + 1);
        return depth(node->right, key, currentDepth + 1);
    }

    int level(Node* node, int key) {
        return depth(node, key) + 1;
    }

    void inorder(Node* root) {
        // Recursividad
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    void preorder(Node* root) {
        // Recursividad
        if (root == nullptr) return;
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root) {
        // Recursividad
        if (root == nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }

    void drawNode(Node* node, int x, int y, int xOffset) {
        if (node == nullptr) return;

        // Mejorar visual del nodo
        int radius = 25;
        setcolor(BLUE);
        circle(x, y, radius);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        floodfill(x, y, BLUE);
        
        // Mostrar valor del nodo
        setcolor(BLACK);
        char keyStr[10];
        sprintf(keyStr, "%d", node->key);
        // Centrar texto
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(x - textwidth(keyStr)/2, y - textheight(keyStr)/2, keyStr);

        // Dibujar conexiones
        if (node->left != nullptr) {
            setcolor(RED);
            line(x, y + radius, x - xOffset / 4, y + 50);
            drawNode(node->left, x - xOffset / 4, y + 50, xOffset / 2);
        }
        if (node->right != nullptr) {
            setcolor(RED);
            line(x, y + radius, x + xOffset / 4, y + 50);
            drawNode(node->right, x + xOffset / 4, y + 50, xOffset / 2);
        }
    }

    void inorder(Node* root, stringstream& ss) {
        if (root == nullptr) return;
        inorder(root->left, ss);
        ss << root->key << " ";
        inorder(root->right, ss);
    }

    void preorder(Node* root, stringstream& ss) {
        if (root == nullptr) return;
        ss << root->key << " ";
        preorder(root->left, ss);
        preorder(root->right, ss);
    }

    void postorder(Node* root, stringstream& ss) {
        if (root == nullptr) return;
        postorder(root->left, ss);
        postorder(root->right, ss);
        ss << root->key << " ";
    }

    void drawTraversalResults(int x, int y, const string& inorder, const string& preorder, const string& postorder) {
        int cellWidth = 200;
        int cellHeight = 50;
        int padding = 10;

        setcolor(BLACK);
        rectangle(x, y, x + cellWidth, y + cellHeight);
        outtextxy(x + padding, y + padding, const_cast<char*>("Inorder:"));
        outtextxy(x + padding, y + padding + 20, const_cast<char*>(inorder.c_str()));

        rectangle(x, y + cellHeight, x + cellWidth, y + 2 * cellHeight);
        outtextxy(x + padding, y + cellHeight + padding, const_cast<char*>("Preorder:"));
        outtextxy(x + padding, y + cellHeight + padding + 20, const_cast<char*>(preorder.c_str()));

        rectangle(x, y + 2 * cellHeight, x + cellWidth, y + 3 * cellHeight);
        outtextxy(x + padding, y + 2 * cellHeight + padding, const_cast<char*>("Postorder:"));
        outtextxy(x + padding, y + 2 * cellHeight + padding + 20, const_cast<char*>(postorder.c_str()));
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        recursiveInsert(root, key);
    }

    void display() {
        if (root == nullptr) {
            cout << "El arbol esta vacio." << endl;
            return;
        }
        recursiveDisplay(root, 0);
    }

    int getHeight() {
        return height(root);
    }

    int getDepth(int key) {
        return depth(root, key);
    }

    int getLevel(int key) {
        return level(root, key);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        postorder(root);
        cout << endl;
    }

    void drawTree() {
        int anchoPantalla, altoPantalla;
        DEVMODE dm;
        memset(&dm, 0, sizeof(dm));
        dm.dmSize = sizeof(dm);
        
        // Obtener la resolución real de la tarjeta gráfica
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
            anchoPantalla = dm.dmPelsWidth;
            altoPantalla = dm.dmPelsHeight;
        } else {
            // Si falla, usar GetSystemMetrics como respaldo
            anchoPantalla = GetSystemMetrics(SM_CXSCREEN);
            altoPantalla = GetSystemMetrics(SM_CYSCREEN);
        }
        
        // Iniciar modo gráfico en pantalla completa
        initwindow(anchoPantalla, altoPantalla, "Arbol Splay", -3, -3);
        
        setbkcolor(WHITE);
        cleardevice();
        
        if (root != nullptr) {
            // Ajustar el dibujo del árbol 
            drawNode(root, anchoPantalla * 0.35, 50, anchoPantalla / 4);

            // Obtener los recorridos
            stringstream inorderStream, preorderStream, postorderStream;
            inorder(root, inorderStream);
            preorder(root, preorderStream);
            postorder(root, postorderStream);

            // Dibujar los resultados de los recorridos
            drawTraversalResults(anchoPantalla * 0.35, altoPantalla / 2 - 75, inorderStream.str(), preorderStream.str(), postorderStream.str());
        } else {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(anchoPantalla / 2 - 100, altoPantalla / 2, const_cast<char*>("Arbol vacio"));
        }
        
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(10, altoPantalla - 30, const_cast<char*>("Presiona cualquier tecla para continuar..."));
        getch();
        closegraph();
    }
};