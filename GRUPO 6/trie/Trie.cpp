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
        info.lines = {node_str};
        info.width = node_str.size();
        info.root_pos = 0;
        return info;
    }

    std::vector<SubtreeInfo> childSubtrees;
    for (auto& pair : children) {
        childSubtrees.push_back(pair.second->buildSubtree(pair.first));
    }

    int total_width = 0;
    std::vector<int> widths;
    for (auto& st : childSubtrees) {
        total_width += st.width + 2;
        widths.push_back(st.width);
    }
    if (!childSubtrees.empty()) total_width -= 2;

    int max_height = 0;
    for (auto& st : childSubtrees) {
        max_height = std::max(max_height, (int)st.lines.size());
    }

    std::vector<std::string> lines(max_height + 2, std::string(total_width, ' '));
    int root_x = total_width / 2;
    
    // Nodo actual
    lines[0].replace(
        root_x - node_str.size()/2, 
        node_str.size(), 
        node_str
    );

    // Conexiones
    std::string& conn_line = lines[1];
    int child_x = 0;
    for (size_t i = 0; i < childSubtrees.size(); ++i) {
        int child_root = child_x + childSubtrees[i].root_pos;
        conn_line[child_root] = (i == 0) ? '/' : '\\';
        child_x += widths[i] + 2;
    }

    // Subárboles
    child_x = 0;
    for (size_t i = 0; i < childSubtrees.size(); ++i) {
        for (size_t line = 0; line < childSubtrees[i].lines.size(); ++line) {
            lines[line + 2].replace(
                child_x, 
                childSubtrees[i].lines[line].size(), 
                childSubtrees[i].lines[line]
            );
        }
        child_x += widths[i] + 2;
    }

    info.lines = lines;
    info.width = total_width;
    info.root_pos = root_x;
    return info;
}

void Trie::printTree() {
    SubtreeInfo root_info;
    root_info.lines = {"root"};
    root_info.width = 4;
    root_info.root_pos = 2;

    if (!children.empty()) {
        std::vector<SubtreeInfo> childSubtrees;
        for (auto& pair : children) {
            childSubtrees.push_back(pair.second->buildSubtree(pair.first));
        }

        int total_width = 0;
        for (auto& st : childSubtrees) {
            total_width += st.width + 2;
        }
        if (!childSubtrees.empty()) total_width -= 2;

        std::vector<std::string> lines(childSubtrees[0].lines.size() + 2, std::string(total_width, ' '));
        lines[0].replace(total_width/2 - 2, 4, "root");

        // Conexiones
        std::string& conn_line = lines[1];
        int current_x = 0;
        for (size_t i = 0; i < childSubtrees.size(); ++i) {
            int child_root = current_x + childSubtrees[i].root_pos;
            conn_line[child_root] = (i == 0) ? '/' : '\\';
            current_x += childSubtrees[i].width + 2;
        }

        // Subárboles
        current_x = 0;
        for (auto& st : childSubtrees) {
            for (size_t line = 0; line < st.lines.size(); ++line) {
                lines[line + 2].replace(
                    current_x, 
                    st.lines[line].size(), 
                    st.lines[line]
                );
            }
            current_x += st.width + 2;
        }

        for (auto& line : lines) {
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
