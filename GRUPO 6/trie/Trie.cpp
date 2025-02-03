#include "trie.h"
#include <iostream>
#include <algorithm>

Trie::Trie() : isLeaf(false) {}

void Trie::insert(std::string key) {
    if (key.empty()) {
        isLeaf = true;
        return;
    }
    char c = key[0];
    if (!children[c]) children[c] = new Trie();
    children[c]->insert(key.substr(1));
}

bool Trie::search(std::string key) {
    if (key.empty()) return isLeaf;
    char c = key[0];
    if (children.find(c) == children.end()) return false;
    return children[c]->search(key.substr(1));
}

bool Trie::deletion(std::string key) {
    if (key.empty()) {
        if (!isLeaf) return false;
        isLeaf = false;
        return children.empty();
    }
    char c = key[0];
    if (children.find(c) == children.end()) return false;
    bool shouldDelete = children[c]->deletion(key.substr(1));
    if (shouldDelete) {
        delete children[c];
        children.erase(c);
        return !isLeaf && children.empty();
    }
    return false;
}

Trie::SubtreeInfo Trie::buildSubtree(char c) {
    SubtreeInfo info;
    std::string node_str(1, c);
    
    if (isLeaf) node_str += "*";
    
    if (children.empty()) {
        info.lines.push_back(node_str);
        info.width = node_str.size();
        info.root_pos = 0;
        return info;
    }

    std::list<SubtreeInfo> childSubtrees;
    for (auto& pair : children) {
        childSubtrees.push_back(pair.second->buildSubtree(pair.first));
    }

    int total_width = 0;
    std::list<int> widths;
    for (auto& st : childSubtrees) {
        total_width += st.width + 2;
        widths.push_back(st.width);
    }
    if (!childSubtrees.empty()) total_width -= 2;

    int max_height = 0;
    for (auto& st : childSubtrees) {
        max_height = std::max(max_height, (int)st.lines.size());
    }

    // Crear las líneas iniciales
    for (int i = 0; i < max_height + 2; i++) {
        info.lines.push_back(std::string(total_width, ' '));
    }

    int root_x = total_width / 2;
    
    // Nodo actual
    auto first_line = info.lines.begin();
    first_line->replace(root_x - node_str.size()/2, node_str.size(), node_str);

    // Conexiones
    auto conn_line = std::next(info.lines.begin());
    int child_x = 0;
    auto childIt = childSubtrees.begin();
    auto widthIt = widths.begin();
    
    for (size_t i = 0; childIt != childSubtrees.end(); ++i, ++childIt, ++widthIt) {
        int child_root = child_x + childIt->root_pos;
        (*conn_line)[child_root] = (i == 0) ? '/' : '\\';
        child_x += *widthIt + 2;
    }

    // Subárboles
    child_x = 0;
    for (auto& subtree : childSubtrees) {
        auto lineIt = std::next(info.lines.begin(), 2);
        auto subtreeLineIt = subtree.lines.begin();
        
        while (subtreeLineIt != subtree.lines.end()) {
            lineIt->replace(child_x, subtreeLineIt->size(), *subtreeLineIt);
            ++lineIt;
            ++subtreeLineIt;
        }
        child_x += subtree.width + 2;
    }

    info.width = total_width;
    info.root_pos = root_x;
    return info;
}

void Trie::printTree() {
    SubtreeInfo root_info;
    root_info.lines.push_back("root");
    root_info.width = 4;
    root_info.root_pos = 2;

    if (!children.empty()) {
        std::list<SubtreeInfo> childSubtrees;
        for (auto& pair : children) {
            childSubtrees.push_back(pair.second->buildSubtree(pair.first));
        }

        int total_width = 0;
        for (auto& st : childSubtrees) {
            total_width += st.width + 2;
        }
        if (!childSubtrees.empty()) total_width -= 2;

        // Crear lista de líneas
        std::list<std::string> lines;
        auto firstChild = childSubtrees.front();
        for (size_t i = 0; i < firstChild.lines.size() + 2; i++) {
            lines.push_back(std::string(total_width, ' '));
        }

        // Root node
        auto firstLine = lines.begin();
        firstLine->replace(total_width/2 - 2, 4, "root");

        // Conexiones
        auto connLine = std::next(lines.begin());
        int current_x = 0;
        for (auto& child : childSubtrees) {
            int child_root = current_x + child.root_pos;
            (*connLine)[child_root] = (current_x == 0) ? '/' : '\\';
            current_x += child.width + 2;
        }

        // Subárboles
        current_x = 0;
        for (auto& st : childSubtrees) {
            auto lineIt = std::next(lines.begin(), 2);
            auto stLineIt = st.lines.begin();
            
            while (stLineIt != st.lines.end()) {
                lineIt->replace(current_x, stLineIt->size(), *stLineIt);
                ++lineIt;
                ++stLineIt;
            }
            current_x += st.width + 2;
        }

        // Imprimir líneas
        for (const auto& line : lines) {
            std::cout << line << std::endl;
        }
    } else {
        std::cout << "root" << std::endl;
    }
}

void Trie::printInOrder(std::string prefix = "") {
    if (isLeaf) {
        std::cout << prefix << std::endl;
    }
    for (auto& pair : children) {
        pair.second->printInOrder(prefix + pair.first);
    }
}

int Trie::getHeight() {
    int maxHeight = 0;
    for (auto& pair : children) {
        maxHeight = std::max(maxHeight, pair.second->getHeight());
    }
    return 1 + maxHeight;
}

int Trie::getDepth() {
    return getHeight(); // En un Trie, la profundidad es igual a la altura
}

int Trie::getLevel() {
    return getHeight() - 1; // Nivel máximo es altura - 1
}
