#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

class RadixTreeNode {
public:
    std::string prefix;
    std::unordered_map<char, RadixTreeNode*> children;
    bool is_end_of_word;

    RadixTreeNode(const std::string& prefix = "") : prefix(prefix), is_end_of_word(false) {}

    ~RadixTreeNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class RadixTree {
private:
    RadixTreeNode* root;

    // Funcion auxiliar para dividir un nodo
    void splitNode(RadixTreeNode* parent, RadixTreeNode* node, const std::string& prefix, int common_length) {
        std::string common_prefix = prefix.substr(0, common_length);
        std::string remaining_prefix = node->prefix.substr(common_length);

        // Crear un nuevo nodo para el prefijo común
        RadixTreeNode* new_node = new RadixTreeNode(common_prefix);
        new_node->children[remaining_prefix[0]] = node;
        node->prefix = remaining_prefix;

        // Reemplazar el nodo actual con el nuevo nodo en el padre
        parent->children[common_prefix[0]] = new_node;
    }

    // Funcion auxiliar para insertar una palabra
    void insertHelper(RadixTreeNode* node, const std::string& word) {
        int i = 0;
        RadixTreeNode* parent = nullptr;
        while (i < word.length()) {
            bool match = false;
            for (auto& pair : node->children) {
                int common_length = 0;
                while (common_length < pair.second->prefix.length() &&
                       common_length < word.length() - i &&
                       pair.second->prefix[common_length] == word[i + common_length]) {
                    common_length++;
                }

                if (common_length > 0) {
                    match = true;
                    if (common_length < pair.second->prefix.length()) {
                        splitNode(node, pair.second, word.substr(i), common_length);
                    }
                    parent = node;
                    node = pair.second;
                    i += common_length;
                    break;
                }
            }

            if (!match) {
                // No hay coincidencia, crear un nuevo nodo
                RadixTreeNode* new_node = new RadixTreeNode(word.substr(i));
                node->children[word[i]] = new_node;
                new_node->is_end_of_word = true;
                return;
            }
        }
        node->is_end_of_word = true;
    }

    // Funcion auxiliar para buscar una palabra
    bool searchHelper(RadixTreeNode* node, const std::string& word) {
        int i = 0;
        while (i < word.length()) {
            bool match = false;
            for (auto& pair : node->children) {
                int common_length = 0;
                while (common_length < pair.second->prefix.length() &&
                       common_length < word.length() - i &&
                       pair.second->prefix[common_length] == word[i + common_length]) {
                    common_length++;
                }

                if (common_length > 0) {
                    if (common_length < pair.second->prefix.length()) {
                        return false; // No coincide completamente
                    }
                    node = pair.second;
                    i += common_length;
                    match = true;
                    break;
                }
            }

            if (!match) {
                return false;
            }
        }
        return node->is_end_of_word;
    }

    // Funcion auxiliar para eliminar una palabra
    bool deleteHelper(RadixTreeNode* node, const std::string& word, int depth = 0) {
        if (depth == word.length()) {
            if (!node->is_end_of_word) {
                return false; // La palabra no existe
            }
            node->is_end_of_word = false;
            return node->children.empty();
        }

        char current_char = word[depth];
        if (node->children.find(current_char) == node->children.end()) {
            return false; // La palabra no existe
        }

        RadixTreeNode* child = node->children[current_char];
        bool should_delete_child = deleteHelper(child, word, depth + child->prefix.length());

        if (should_delete_child) {
            node->children.erase(current_char);
            delete child;
            return node->children.empty() && !node->is_end_of_word;
        }

        return false;
    }

    // Funcion auxiliar para mostrar todas las palabras (recorrido prefijo)
    void displayPrefixHelper(RadixTreeNode* node, std::string current_prefix) {
        if (node->is_end_of_word) {
            std::cout << current_prefix << std::endl;
        }

        for (auto& pair : node->children) {
            displayPrefixHelper(pair.second, current_prefix + pair.second->prefix);
        }
    }

    // Funcion auxiliar para recorrido postfijo
    void displayPostfixHelper(RadixTreeNode* node, std::string current_prefix) {
        for (auto& pair : node->children) {
            displayPostfixHelper(pair.second, current_prefix + pair.second->prefix);
        }

        if (node->is_end_of_word) {
            std::cout << current_prefix << std::endl;
        }
    }

    // Funcion auxiliar para recorrido infijo
    void displayInfixHelper(RadixTreeNode* node, std::string current_prefix) {
        bool has_printed = false;

        for (auto& pair : node->children) {
            displayInfixHelper(pair.second, current_prefix + pair.second->prefix);
            if (!has_printed && node->is_end_of_word) {
                std::cout << current_prefix << std::endl;
                has_printed = true;
            }
        }

        if (!has_printed && node->is_end_of_word) {
            std::cout << current_prefix << std::endl;
        }
    }

    // Funcion auxiliar para calcular la altura del arbol
    int heightHelper(RadixTreeNode* node) {
        if (node->children.empty()) {
            return 0;
        }

        int max_height = 0;
        for (auto& pair : node->children) {
            max_height = std::max(max_height, heightHelper(pair.second));
        }

        return max_height + 1;
    }

    // Funcion auxiliar para calcular la profundidad de un nodo
    int depthHelper(RadixTreeNode* node, const std::string& word, int depth = 0) {
        if (word.empty()) {
            return depth;
        }

        char current_char = word[0];
        if (node->children.find(current_char) == node->children.end()) {
            return -1; // No se encontro el nodo
        }

        RadixTreeNode* child = node->children[current_char];
        return depthHelper(child, word.substr(child->prefix.length()), depth + 1);
    }

    // Funcion auxiliar para calcular el nivel de un nodo
    int levelHelper(RadixTreeNode* node, const std::string& word, int current_level = 0) {
        if (word.empty()) {
            return current_level;
        }

        char current_char = word[0];
        if (node->children.find(current_char) == node->children.end()) {
            return -1; // No se encontro el nodo
        }

        RadixTreeNode* child = node->children[current_char];
        return levelHelper(child, word.substr(child->prefix.length()), current_level + 1);
    }

    // Funcion auxiliar para imprimir el arbol por consola
    void printTreeHelper(RadixTreeNode* node, const std::string& prefix, int level) {
        if (node == nullptr) return;
        std::cout << std::string(level * 2, ' ') << prefix << (node->is_end_of_word ? "*" : "") << std::endl;
        for (auto& pair : node->children) {
            printTreeHelper(pair.second, std::string(1, pair.first), level + 1);
        }
    }

    void printTreeStructuredHelper(RadixTreeNode* node, const std::string& prefix, bool isTail) {
        std::cout << prefix << (isTail ? "--- " : "--- ") << node->prefix << (node->is_end_of_word ? "*" : "") << std::endl;
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            printTreeStructuredHelper(it->second, prefix + (isTail ? "    " : " -   "), std::next(it) == node->children.end());
        }
    }

public:
    RadixTree() : root(new RadixTreeNode()) {}

    ~RadixTree() {
        delete root;
    }

    void insert(const std::string& word) {
        insertHelper(root, word);
    }

    bool search(const std::string& word) {
        return searchHelper(root, word);
    }

    void remove(const std::string& word) {
        deleteHelper(root, word);
    }

    void displayPrefix() {
        displayPrefixHelper(root, "");
    }

    void displayPostfix() {
        displayPostfixHelper(root, "");
    }

    void displayInfix() {
        displayInfixHelper(root, "");
    }

    int height() {
        return heightHelper(root);
    }

    int depth(const std::string& word) {
        return depthHelper(root, word);
    }

    int level(const std::string& word) {
        return levelHelper(root, word);
    }

    void printTree() {
        printTreeHelper(root, "", 0);
    }

    void printTreeStructured() {
        printTreeStructuredHelper(root, "", true);
    }

    RadixTreeNode* getRoot() {
        return root;
    }
};

// Funcion para mostrar el menu
void displayMenu() {
    std::cout << "\n--- Menu del Arbol Radix ---" << std::endl;
    std::cout << "1. Insertar palabra" << std::endl;
    std::cout << "2. Buscar palabra" << std::endl;
    std::cout << "3. Eliminar palabra" << std::endl;
    std::cout << "4. Mostrar palabras (Prefijo)" << std::endl;
    std::cout << "5. Mostrar palabras (Postfijo)" << std::endl;
    std::cout << "6. Mostrar palabras (Infijo)" << std::endl;
    std::cout << "7. Calcular altura del arbol" << std::endl;
    std::cout << "8. Calcular profundidad de una palabra" << std::endl;
    std::cout << "9. Calcular nivel de una palabra" << std::endl;
    std::cout << "10. Imprimir arbol" << std::endl; // Nueva opción en el menú
    std::cout << "11. Salir" << std::endl;
    std::cout << "Ingrese su opcion: ";
}

