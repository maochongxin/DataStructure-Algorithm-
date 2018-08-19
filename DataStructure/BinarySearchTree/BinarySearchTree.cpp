//
//  main.cpp
//  二叉搜索树
//
//  Created by maochongxin on 2018/8/13.
//  Copyright © 2018 maochongxin. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* Left;
    Node* Right;
    Node(T value):data(value),Left(NULL),Right(NULL){}
};

template <class T>
class BinarySearchTree {
public:
    typedef Node<T>* TreeNode;
private:
    TreeNode Troot;
protected:
    
    void _DeleteTree(TreeNode &root) {
        if (root == NULL) {
            return;
        }
        if (root -> Left != NULL) {
            _DeleteTree(root -> Left);
        }
        if (root -> Right != NULL) {
            _DeleteTree(root -> Right);
        }
        delete root;
        root = NULL;
    }
    
    
    void _Insert(const T& value,TreeNode &root) {
        if (root == NULL) {
            root = new Node<T>(value);
        } else if (root -> data > value) {
            _Insert(value, root -> Left);
        } else if(root -> data < value) {
            _Insert(value, root -> Right);
        } else {
            cout << "Insert Error" << endl;
        }
    }
    
    void _PreOrder(TreeNode root) {
        if (root == NULL) {
            return;
        }
        cout << root -> data;
        _PreOrder(root -> Left);
        _PreOrder(root -> Right);
    };
    void _InOrder(TreeNode root) {
        if (root == NULL) {
            return;
        }
        _InOrder(root -> Left);
        cout << root -> data;
        _InOrder(root -> Left);
        
    };
    void _PostOrder(TreeNode root) {
        if (root == NULL) {
            return;
        }
        _PostOrder(root -> Left);
        _PostOrder(root -> Right);
        cout << root -> data;
    };
    void _LevelOrder(TreeNode root) {
        queue<Node<T>*> q;
        if (root) {
            q.push(root);
        }
        while (!q.empty()) {
            Node<T>* t = q.front();
            q.pop();
            cout << t -> data << " ";
            if (t -> Left) {
                q.push(t -> Left);
            }
            if (t -> Right) {
                q.push(t -> Right);
            }
        }
    };
    
    
    
    
    //search
    TreeNode _FindMax(TreeNode root) {
        if (root) {
            while (root -> Right) {
                root = root -> Right;
            }
        }
        return root;
    };
    TreeNode _FindMin(TreeNode root) {
        if (root) {
            while (root -> Left) {
                root = root -> Left;
            }
        }
        return root;
    };
    
    TreeNode _Find(TreeNode root,int key) {
        while (root -> data != key) {
            if (root -> data == key) {
                return root;
            } else {
                if (root -> data > key) {
                    root = root -> Left;
                } else {
                    root = root -> Right;
                }
            }
        }
        return NULL;
    }
    bool _Remove(TreeNode root,const int& value);
    
    
public:
    BinarySearchTree() = default;
    
    void Insert(const T& value) {
        if (Troot == NULL) {
            Troot = new Node<T>(value);
        } else {
            _Insert(value, this -> Troot);
        }
    }
    ~BinarySearchTree() {
        _DeleteTree(Troot);
        Troot = NULL;
    }
    void PreOrder() {
        _PreOrder(Troot);
    }
    void InOrder() {
        _InOrder(Troot);
    }
    void PostOrder() {
        _PostOrder(Troot);
    }
    void LevelOrder() {
        _LevelOrder(Troot);
    }
    
    
    TreeNode FindMax() {
        return _FindMax(Troot);
    }
    TreeNode FindMin() {
        return _FindMin(Troot);
    }
    TreeNode Find(const int& value) {
        return _Find(Troot, value);
    }
    
    
    TreeNode Successor(Node<T>* root);
    TreeNode PreDecessor(Node<T>* root);
    bool Remove(const int& value) {
        return _Remove(Troot, value);
    }
};

template <class T>
bool BinarySearchTree<T>::_Remove(Node<T>* root, const int& value) {
    assert(root);
    TreeNode father = NULL;
    TreeNode pcur = root;
    TreeNode del = pcur;
    
    while (pcur != NULL && pcur -> data != value) {
        if (pcur -> data > value) {
            father = pcur;
            pcur = pcur -> Left;
        } else if (pcur -> data < value) {
            father = pcur;
            pcur = pcur -> Right;
        }
    }
    if (pcur == NULL) {
        return false;
    }
    if (pcur -> Left == NULL) {
        if (pcur == root) {
            root = pcur -> Right;
        } else if (pcur == father -> Left) {
            father -> Left = pcur -> Right;
        } else {
            father -> Right = pcur -> Right;
        }
        del = pcur;
    } else if (pcur -> Right == NULL) {
        if (pcur == root) {
            root = pcur -> Left;
        } else if (father -> Left == pcur) {
            father -> Left = pcur -> Left;
        } else {
            father -> Right = pcur -> Left;
        }
        del = pcur;
    } else {
        Node<T>* left = pcur -> Right;
        father = pcur;
        while (left -> Left) {
            father = left;
            left = left -> Left;
        }
        del = left;
        pcur -> data = left -> data;
        if (father -> Left == left) {
            father -> Left = left -> Right;
        } else {
            father -> Right = left -> Right;
        }
        delete del;
        return true;
    }
    return false;
}



int main(int argc, const char * argv[]) {
    BinarySearchTree<int> bst;
    int n;
    while (cin >> n) {
        bst.Insert(n);
    }
    bst.LevelOrder();
    int t;
    cin >> t;
    bst.Remove(t);
    bst.LevelOrder();
    cout << bst.FindMax() -> data; 
    return 0;
}
