#ifdef _BST_H_
#define _BST_H_

#include <iostream>
#include <vector>
template <typename T>
struct Node {
    T val;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node (T _val): val(_val), left(nullptr), right(nullptr) {}
};

template <typename T>
class Bintree {
private:
    std::shared_ptr<Node> root;
private:
    void _insert (T, std::shared_ptr<Node>);
public:
    Bintree (T val) {
        root = std::make_shared<Node>(val);
    }
    Bintree(const std::vector<T>&) {
        for (T i : vec) { this->insert(i); }
    }
    // ~Bintree() {}
    void insert(T val) { _insert(val,root); }
};

template <typename T>
void Bintree::_insert (T val, std::shared_ptr<Node> t) {
    if (t == nullptr) {
        t = std::make_shared<Node>(val);
    } else {
        if (t->val < val) {
            _insert(val, t->right);
        } else if (t->val > val) {
            _insert(val, t->left);
        }
    }
}

#endif