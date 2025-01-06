#include "Trie.h"

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