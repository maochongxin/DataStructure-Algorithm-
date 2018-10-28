//
//  AVLTree.h
//  AVL Tree
//
//  Created by maochongxin on 2018/10/28.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
struct Node;

template <typename T>
struct Node {
    T data;
    int height;
    Node<T>* left;
    Node<T>* right;
    Node(T _data): data(_data),height(0),left(NULL),right(NULL) {}
};


template <typename T>
class AVL {
public:
    typedef Node<T>* AvlTree;
    typedef Node<T>* Position;
    typedef T ElementType;
    
private:
    AvlTree root;
    
    AvlTree _Insert(AvlTree& tree,ElementType _data);
    Position _Find(AvlTree tree,ElementType x);
    Position _FindMax(AvlTree tree);
    Position _FindMin(AvlTree tree);
    AvlTree _Delete(AvlTree tree,ElementType x);
    
    void _levelOrder(AvlTree t);
    
    
    static int Height(Position p) {
        if (p == NULL) {
            return -1;
        } else {
            return p -> height;
        }
    }
    static Position SingleRotateWithLeft(Position k2) {
        Position k1 = k2 -> left;
        k1 = k2 -> left;
        k2 -> left = k1 -> right;
        k1 -> right = k2;
        k2 -> height = max(Height(k2 -> left),Height(k2 -> right)) + 1;
        k1 -> height = max(Height(k1 -> left),Height(k2 -> right)) + 1;
        return k1;
    }
    static Position SingleRotateWithRight(Position k2) {
        Position k1 = k2 -> right;
        k1 = k2 -> right;
        k2 -> right = k1 -> left;
        k1 -> left = k2;
        k2 -> height = max(Height(k2 -> left), Height(k2 -> right)) + 1;
        k1 -> height = max(Height(k1 -> left), Height(k1 -> right)) + 1;
        return k1;
    }
    static Position DoubleRotateWithLeft(Position k3) {
        k3 -> left = SingleRotateWithLeft(k3 -> left);
        return SingleRotateWithLeft(k3);
    }
    static Position DoubleRotateWithRight(Position k3) {
        k3 -> right = SingleRotateWithRight(k3 -> right);
        return SingleRotateWithRight(k3);
    }
    
    
public:
    
    AVL():root(NULL) {}
    AVL(vector<T> vec) {
        for (typename vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter) {
            Insert(*iter);
        }
    }
    
    friend ostream& operator<<(ostream& out,AVL tree) {
        tree.levelOrder();
        return out;
    }
    
    AvlTree Insert(ElementType _data) {
        return _Insert(root, _data);
    }
    Position Find(ElementType x) {
        return _Find(root, x);
    }
    Position FindMax() {
        return _FindMax(root);
    }
    Position FindMin() {
        return _FindMin(root);
    }
    AvlTree Delete(ElementType x) {
        _Delete(root, x);
    }
    void levelOrder() {
        _levelOrder(root);
    }
};
template <typename T>
Node<T>* AVL<T>::_Insert(Node<T>*& tree,T _data) {
    if (tree == NULL) {
        tree = new Node<T>(_data);
        if (tree == NULL) {
            return NULL;
        }
    } else if(_data < tree -> data) {
        tree -> left = _Insert(tree -> left, _data);
        if (Height(tree -> left) - Height(tree -> right) == 2) {
            if(_data > tree -> left -> data) {
                tree = SingleRotateWithLeft(tree);
            } else {
                tree = DoubleRotateWithLeft(tree);
            }
        }
    } else if(_data > tree -> data) {
        tree -> right = _Insert(tree -> right, _data);
        if (Height(tree -> right) - Height(tree -> left) == 2) {
            if (_data > tree -> right -> data) {
                tree = SingleRotateWithRight(tree);
            } else {
                tree = DoubleRotateWithRight(tree);
            }
        }
    }
    tree -> height = max(Height(tree -> left),Height(tree -> right)) + 1;
    return tree;
}

template <typename T>
Node<T>* AVL<T>::_Find(Node<T>* tree, T x) {
    if (tree == NULL) {
        return NULL;
    } else {
        while (x != tree -> data) {
            if (x > tree -> data) {
                tree = tree -> right;
            } else if(x < tree -> data){
                tree = tree -> left;
            }
        }
        return tree;
    }
}
template <typename T>
Node<T>* AVL<T>::_FindMax(Node<T>* tree) {
    if (tree == NULL) {
        return NULL;
    }
    while (tree -> right != NULL) {
        tree = tree -> right;
    }
    return tree;
}

template <typename T>
Node<T>* AVL<T>::_FindMin(Node<T>* tree) {
    if (tree == NULL) {
        return NULL;
    }
    while (tree -> left != NULL) {
        tree = tree -> left;
    }
    return tree;
}

template <typename T>
void AVL<T>::_levelOrder(Node<T>* t) {
    queue<Node<T>* > q;
    if (t != NULL) {
        q.push(t);
        while (!q.empty()) {
            Node<T>* f = q.front();
            q.pop();
            cout << f -> data << " ";
            if (f -> left) {
                q.push(f -> left);
            }
            if (f -> right) {
                q.push(f -> right);
            }
        }
    }
    cout << endl;
    return ;
}

#endif /* AVLTree_h */
