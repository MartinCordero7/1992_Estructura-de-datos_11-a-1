// BTreeNode.cpp
#include "BTreeNode.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include "BTree.h"

BTreeNode::BTreeNode(int _t, bool _leaf) {
    try {
        t = _t;
        leaf = _leaf;
        keys.reserve(2 * t - 1);
        children.reserve(2 * t);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

BTreeNode::~BTreeNode() {  // Destructor para liberar memoria dinámica
    try {
        for (auto child : children) {
            delete child;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::traverse() {
    try {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!leaf)
                children[i]->traverse();
            std::cout << " " << keys[i];
        }
        if (!leaf)
            children[i]->traverse();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

BTreeNode* BTreeNode::search(int k) {
    try {
        int i = 0;
        while (i < keys.size() && k > keys[i])
            i++;

        if (i < keys.size() && keys[i] == k)
            return this;

        if (leaf)
            return nullptr;

        return children[i]->search(k);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return nullptr;
    }
}

void BTreeNode::insertNonFull(int k) {
    try {
        int i = keys.size() - 1;

        if (leaf) {
            keys.push_back(0);
            while (i >= 0 && keys[i] >= k) { // Change comparison to >=
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
        } else {
            while (i >= 0 && keys[i] >= k) // Change comparison to >=
                i--;
            i++;

            if (children[i]->keys.size() == 2 * t - 1) {
                splitChild(i, children[i]);

                if (keys[i] < k)
                    i++;
            }
            children[i]->insertNonFull(k);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    try {
        BTreeNode* z = new BTreeNode(y->t, y->leaf);
        z->keys.assign(y->keys.begin() + t, y->keys.end());
        y->keys.resize(t - 1);

        if (!y->leaf) {
            z->children.assign(y->children.begin() + t, y->children.end());
            y->children.resize(t);
        }

        children.insert(children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, y->keys[t - 1]);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::saveToFile(ofstream &file) {
    try {
        for (const auto& key : keys) {
            file << key << " ";
        }
        file << "\n";

        if (!leaf) {
            for (auto child : children) {
                if (child) {
                    child->saveToFile(file);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int BTreeNode::findKey(int k) {
    try {
        int idx = 0;
        while (idx < keys.size() && keys[idx] < k)
            ++idx;
        return idx;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
}

void BTreeNode::remove(int k) {
    try {
        int idx = findKey(k);

        if (idx < keys.size() && keys[idx] == k) {
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        } else {
            if (leaf) {
                std::cout << "El elemento " << k << " no existe en el arbol.\n";
                return;
            }

            bool flag = (idx == keys.size());

            if (children[idx]->keys.size() < t)
                fill(idx);

            if (flag && idx > keys.size())
                children[idx - 1]->remove(k);
            else
                children[idx]->remove(k);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    try {
        keys.erase(keys.begin() + idx);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::removeFromNonLeaf(int idx) {
    try {
        int k = keys[idx];

        if (children[idx]->keys.size() >= t) {
            int pred = getPredecessor(idx);
            keys[idx] = pred;
            children[idx]->remove(pred);
        } else if (children[idx + 1]->keys.size() >= t) {
            int succ = getSuccessor(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ);
        } else {
            merge(idx);
            children[idx]->remove(k);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int BTreeNode::getPredecessor(int idx) {
    try {
        BTreeNode* cur = children[idx];
        while (!cur->leaf)
            cur = cur->children.back();

        return cur->keys.back();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
}

int BTreeNode::getSuccessor(int idx) {
    try {
        BTreeNode* cur = children[idx + 1];
        while (!cur->leaf)
            cur = cur->children.front();

        return cur->keys.front();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }
}

void BTreeNode::fill(int idx) {
    try {
        if (idx != 0 && children[idx - 1]->keys.size() >= t)
            borrowFromPrev(idx);
        else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
            borrowFromNext(idx);
        else {
            if (idx != keys.size())
                merge(idx);
            else
                merge(idx - 1);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    try {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx - 1];

        child->keys.insert(child->keys.begin(), keys[idx - 1]);

        if (!child->leaf)
            child->children.insert(child->children.begin(), sibling->children.back());

        keys[idx - 1] = sibling->keys.back();
        sibling->keys.pop_back();

        if (!sibling->leaf)
            sibling->children.pop_back();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::borrowFromNext(int idx) {
    try {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);

        if (!child->leaf)
            child->children.push_back(sibling->children.front());

        keys[idx] = sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());

        if (!sibling->leaf)
            sibling->children.erase(sibling->children.begin());
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::merge(int idx) {
    try {
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx + 1];

        child->keys.push_back(keys[idx]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

        if (!child->leaf)
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());

        keys.erase(keys.begin() + idx);
        children.erase(children.begin() + idx + 1);

        delete sibling;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void BTreeNode::imprimir(int nivel) {
    try {
        const int ESPACIO_INCREMENTO = 4;
        std::string espacio(nivel * ESPACIO_INCREMENTO, ' ');

        // Imprimir primero el subárbol derecho
        if (!leaf) {
            for (int i = keys.size(); i >= 0; i--) {
                if (i < children.size()) {
                    children[i]->imprimir(nivel + 1);
                }

                if (i < keys.size()) {
                    std::cout << espacio << "--[" << keys[i] << "]--" << std::endl;
                }
            }
        } else {
            for (int i = keys.size() - 1; i >= 0; i--) {
                std::cout << espacio << "--[" << keys[i] << "]--" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}