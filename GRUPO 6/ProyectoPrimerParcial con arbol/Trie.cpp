#include "Trie.h"
#include <algorithm>
#include <queue>

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string& key, Libro* libro) {
    TrieNode* node = root;
    for (char c : key) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->libro = libro;
}

Libro* Trie::search(const string& key) {
    TrieNode* node = root;
    for (char c : key) {
        if (node->children.find(c) == node->children.end()) {
            return nullptr;
        }
        node = node->children[c];
    }
    return node->libro;
}

void Trie::remove(const string& key) {
    removeHelper(root, key, 0);
}

bool Trie::removeHelper(TrieNode* node, const string& key, int depth) {
    if (!node) return false;

    if (depth == key.size()) {
        if (node->libro) {
            node->libro = nullptr;
            return node->children.empty();
        }
        return false;
    }

    char c = key[depth];
    if (removeHelper(node->children[c], key, depth + 1)) {
        delete node->children[c];
        node->children.erase(c);
        return node->children.empty() && !node->libro;
    }
    return false;
}

void Trie::printAll(TrieNode* node, string prefix, ofstream& archivo) {
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

void Trie::printAll(ofstream& archivo) {
    printAll(root, "", archivo);
}

void Trie::collectAllBooks(TrieNode* node, vector<Libro*>& libros) {
    if (node->libro) {
        libros.push_back(node->libro);
    }
    for (auto& child : node->children) {
        collectAllBooks(child.second, libros);
    }
}

vector<Libro*> Trie::collectAllBooks() {
    vector<Libro*> libros;
    collectAllBooks(root, libros);
    return libros;
}

void Trie::collectSuggestions(TrieNode* node, const string& prefix, vector<string>& suggestions) {
    if (node->libro) {
        suggestions.push_back(prefix);
    }
    for (auto& child : node->children) {
        collectSuggestions(child.second, prefix + child.first, suggestions);
    }
}

vector<string> Trie::getSuggestions(const string& prefix) {
    vector<string> suggestions;
    TrieNode* node = root;
    for (char c : prefix) {
        if (node->children.find(c) == node->children.end()) {
            return suggestions; // No suggestions if prefix not found
        }
        node = node->children[c];
    }
    collectSuggestions(node, prefix, suggestions);
    return suggestions;
}

// Función para calcular la distancia de Levenshtein
int Trie::levenshteinDistance(const string& s1, const string& s2) {
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
vector<string> Trie::getTypoSuggestions(const string& prefix, int maxDistance) {
    vector<string> suggestions;
    vector<Libro*> libros = collectAllBooks();
    for (const auto& libro : libros) {
        if (levenshteinDistance(prefix, libro->getTitulo()) <= maxDistance) {
            suggestions.push_back(libro->getTitulo());
        }
    }
    return suggestions;
}