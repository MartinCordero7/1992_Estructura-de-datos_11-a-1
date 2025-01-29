/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Util de entrada de datos                                 *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "RadixTree.h"
#include <algorithm>
#include <queue>

RadixTree::RadixTree() {
    root = new RadixTreeNode();
}

void RadixTree::insert(const string& key, Libro* libro) {
    RadixTreeNode* node = root;
    size_t i = 0;
    while (i < key.size()) {
        bool found = false;
        for (auto& child : node->children) {
            size_t j = 0;
            while (j < child.first.size() && i + j < key.size() && child.first[j] == key[i + j]) {
                j++;
            }
            if (j == child.first.size()) {
                node = child.second;
                i += j;
                found = true;
                break;
            } else if (j > 0) {
                RadixTreeNode* newNode = new RadixTreeNode();
                newNode->children[child.first.substr(j)] = child.second;
                node->children[child.first.substr(0, j)] = newNode;
                node->children.erase(child.first);
                node = newNode;
                i += j;
                found = true;
                break;
            }
        }
        if (!found) {
            node->children[key.substr(i)] = new RadixTreeNode();
            node = node->children[key.substr(i)];
            break;
        }
    }
    node->libro = libro;
}

Libro* RadixTree::search(const string& key) {
    RadixTreeNode* node = root;
    size_t i = 0;
    while (i < key.size()) {
        bool found = false;
        for (auto& child : node->children) {
            size_t j = 0;
            while (j < child.first.size() && i + j < key.size() && child.first[j] == key[i + j]) {
                j++;
            }
            if (j == child.first.size()) {
                node = child.second;
                i += j;
                found = true;
                break;
            } else if (j == key.size() - i) {
                return nullptr;
            }
        }
        if (!found) {
            return nullptr;
        }
    }
    return node->libro;
}

void RadixTree::remove(const string& key) {
    removeHelper(root, key, 0);
}

bool RadixTree::removeHelper(RadixTreeNode* node, const string& key, size_t depth) {
    if (!node) return false;

    if (depth == key.size()) {
        if (node->libro) {
            node->libro = nullptr;
            return node->children.empty();
        }
        return false;
    }

    for (auto& child : node->children) {
        size_t j = 0;
        while (j < child.first.size() && depth + j < key.size() && child.first[j] == key[depth + j]) {
            j++;
        }
        if (j == child.first.size()) {
            if (removeHelper(child.second, key, depth + j)) {
                delete child.second;
                node->children.erase(child.first);
                return node->children.empty() && !node->libro;
            }
            return false;
        }
    }
    return false;
}

void RadixTree::printAll(RadixTreeNode* node, string prefix, ofstream& archivo) {
    if (node->libro) {
        archivo << node->libro->getTitulo() << ";"
                << node->libro->getAutor().getNombre() << ";"
                << node->libro->getAutor().getIsni() << ";"
                << node->libro->getAutor().getFechaNacimiento().mostrar() << ";"
                << node->libro->getIsbn() << ";"
                << node->libro->getFechaPublicacion().mostrar() << endl;
    }
    for (auto& child : node->children) {
        printAll(child.second, prefix + child.first, archivo);
    }
}

void RadixTree::printAll(ofstream& archivo) {
    printAll(root, "", archivo);
}

void RadixTree::collectAllBooks(RadixTreeNode* node, vector<Libro*>& libros) {
    if (node->libro) {
        libros.push_back(node->libro);
    }
    for (auto& child : node->children) {
        collectAllBooks(child.second, libros);
    }
}

vector<Libro*> RadixTree::collectAllBooks() {
    vector<Libro*> libros;
    collectAllBooks(root, libros);
    return libros;
}

void RadixTree::collectSuggestions(RadixTreeNode* node, const string& prefix, vector<string>& suggestions) {
    if (node->libro) {
        suggestions.push_back(prefix);
    }
    for (auto& child : node->children) {
        collectSuggestions(child.second, prefix + child.first, suggestions);
    }
}

vector<string> RadixTree::getSuggestions(const string& prefix) {
    vector<string> suggestions;
    RadixTreeNode* node = root;
    size_t i = 0;
    while (i < prefix.size()) {
        bool found = false;
        for (auto& child : node->children) {
            size_t j = 0;
            while (j < child.first.size() && i + j < prefix.size() && child.first[j] == prefix[i + j]) {
                j++;
            }
            if (j == child.first.size()) {
                node = child.second;
                i += j;
                found = true;
                break;
            } else if (j == prefix.size() - i) {
                return suggestions; // No suggestions if prefix not found
            }
        }
        if (!found) {
            return suggestions; // No suggestions if prefix not found
        }
    }
    collectSuggestions(node, prefix, suggestions);
    return suggestions;
}

// Función para calcular la distancia de Levenshtein
int RadixTree::levenshteinDistance(const string& s1, const string& s2) {
    const size_t m = s1.size();
    const size_t n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (size_t i = 0; i <= m; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1 });
            }
        }
    }

    return dp[m][n];
}

// Función para obtener sugerencias basadas en errores tipográficos
vector<string> RadixTree::getTypoSuggestions(const string& prefix, int maxDistance) {
    vector<string> suggestions;
    vector<Libro*> libros = collectAllBooks();
    for (const auto& libro : libros) {
        if (levenshteinDistance(prefix, libro->getTitulo()) <= maxDistance) {
            suggestions.push_back(libro->getTitulo());
        }
    }
    return suggestions;
}

vector<string> RadixTree::getSuggestionsByAuthor(const string& prefix) {
    vector<string> suggestions;
    vector<Libro*> libros = collectAllBooks();
    for (const auto& libro : libros) {
        if (libro->getAutor().getNombre().find(prefix) == 0) {
            suggestions.push_back(libro->getAutor().getNombre());
        }
    }
    return suggestions;
}

vector<string> RadixTree::getSuggestionsByIsbn(const string& prefix) {
    vector<string> suggestions;
    vector<Libro*> libros = collectAllBooks();
    for (const auto& libro : libros) {
        if (libro->getIsbn().find(prefix) == 0) {
            suggestions.push_back(libro->getIsbn());
        }
    }
    return suggestions;
}

vector<string> RadixTree::getSuggestionsByCharacter(const string& input) {
    vector<string> suggestions;
    queue<pair<RadixTreeNode*, string>> nodes;
    nodes.push({root, ""});

    while (!nodes.empty()) {
        auto nodePair = nodes.front();
        RadixTreeNode* node = nodePair.first;
        string prefix = nodePair.second;
        nodes.pop();

        if (node->libro && prefix.find(input) != string::npos) {
            suggestions.push_back(prefix);
        }

        for (auto& child : node->children) {
            nodes.push({child.second, prefix + child.first});
        }
    }

    return suggestions;
}

void RadixTree::generateGraph(const string& outputFile) {
    ofstream file(outputFile);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para generar el gráfico" << endl;
        return;
    }

    file << "digraph G {" << endl;
    queue<pair<RadixTreeNode*, string>> nodes;
    nodes.push({root, "root"});

    while (!nodes.empty()) {
        auto nodePair = nodes.front();
        RadixTreeNode* node = nodePair.first;
        string nodeName = nodePair.second;
        nodes.pop();

        // Sort children alphabetically
        vector<pair<string, RadixTreeNode*>> sortedChildren(node->children.begin(), node->children.end());
        sort(sortedChildren.begin(), sortedChildren.end());

        for (auto& child : sortedChildren) {
            string childName = nodeName + "_" + child.first;
            file << "    \"" << nodeName << "\" -> \"" << childName << "\" [label=\"" << child.first << "\"];" << endl;
            nodes.push({child.second, childName});
        }

        if (node->libro) {
            file << "    \"" << nodeName << "\" [label=\"" << node->libro->getTitulo() << "\", shape=box];" << endl;
        }
    }

    file << "}" << endl;
    file.close();
}

void RadixTree::printInOrder(RadixTreeNode* node, const string& prefix) {
    if (!node) return;
    // Sort children alphabetically
    vector<pair<string, RadixTreeNode*>> sortedChildren(node->children.begin(), node->children.end());
    sort(sortedChildren.begin(), sortedChildren.end());

    for (auto& child : sortedChildren) {
        printInOrder(child.second, prefix + child.first);
    }
    if (node->libro) {
        cout << prefix << ": " << node->libro->getTitulo() << endl;
    }
}

void RadixTree::printPreOrder(RadixTreeNode* node, const string& prefix) {
    if (!node) return;
    if (node->libro) {
        cout << "PreOrder - " << prefix << ": " << node->libro->getTitulo() << endl;
    }
    for (auto& child : node->children) {
        printPreOrder(child.second, prefix + child.first);
    }
}

void RadixTree::printPostOrder(RadixTreeNode* node, const string& prefix) {
    if (!node) return;
    for (auto& child : node->children) {
        printPostOrder(child.second, prefix + child.first);
    }
    if (node->libro) {
        cout << "PostOrder - " << prefix << ": " << node->libro->getTitulo() << endl;
    }
}

void RadixTree::printPreOrder() {
    printPreOrder(root, "");
}

void RadixTree::printPostOrder() {
    printPostOrder(root, "");
}

void RadixTree::printInOrder() {
    printInOrder(root, "");
}
