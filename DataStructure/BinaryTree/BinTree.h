#ifndef BinTree_H
#define BinTree_H

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* Left;
    Node* Right;
    Node():data(0),Left(NULL),Right(NULL){};
};

template <class T>
class BinTree {
private:
    Node<T>* root;
protected:
    bool _empty() { return root == NULL; }
    Node<T>* _Create(T* arr,size_t lengh,const T& invalid,size_t& index) {
        //index需要写引用的原因是C++的函数有值传递当递归到下一层,会重新开辟一块栈空间,这时候会新生成一个index,这个index不会影响上一层的index,因此必须传指针或者传引用
        Node<T>* root = NULL;
        if(index < lengh && arr[index] != invalid) {
            root = new Node<T>();
            root -> data = arr[index];
            root -> Left = _Create(arr, lengh, invalid, ++index);
            root -> Right = _Create(arr, lengh, invalid, ++index);
        }
        return root;
    }
    //拷贝构造
    Node<T>* _Copy(const Node<T>* root) {
        if(root == NULL) {
            return NULL;
        }
        Node<T>* copyroot = new Node<T>();
        copyroot -> data = root -> data;
        copyroot -> Left = _Copy(root -> Left);
        copyroot -> Right = _Copy(root -> Right);
        return copyroot;
    }
    //前序遍历
    void _PreOrder(Node<T>* root) {
        if(root == NULL) {
            return;
        }
        cout << root -> data << endl;
        _PreOrder(root -> Left);
        _PreOrder(root -> Right);
    }
    //中序遍历
    void _InOrder(Node<T>* root) {
        if(root == NULL) {
            return;
        }
        _InOrder(root -> Left);
        cout << root -> data << endl;
        _InOrder(root -> Right);
    }
    //后序遍历
    void _PostOrder(Node<T>* root) {
        if(root == NULL) {
            return;
        }
        _PreOrder(root -> Left);
        _PreOrder(root -> Right);
        cout << root -> data << endl;
    }
    //层序遍历
    void _LevelOrder(Node<T>* root) {
        queue<Node<T>*> que;
        if(root) {
            que.push(root);
        } else {
            return;
        }
        while (!que.empty()) {
            Node<T>* cur = que.front();
            que.pop();
            cout << cur -> data << endl;
            if(cur -> Left) {
                que.push(cur -> Left);
            }
            if(cur -> Right) {
                que.push(cur -> Right);
            }
        }
        cout << endl;
        return ;
    }
    //节点个数
    size_t _Size(Node<T>* root) {
        if(root == NULL) {
            return 0;
        }
        if((root -> Left == NULL && root -> Right == NULL)) {
            return 1;
        }
        return _Size(root -> Left) + _Size(root -> Right) + 1;
    }
    //第K层节点数目
    size_t _K_Level_Size(Node<T>* root,int K) {
        if(root == NULL) {
            return 0;
        } else if(K == 1) {
            return 1;
        } else if(K > 1) {
            return _K_Level_Size(root -> Left, K - 1) + _K_Level_Size(root -> Right, K - 1);
        } else
            return 0;
    }

    //深度
    size_t _Depth(Node<T>* root) {
        if(root == NULL) {
            return 0;
        }
        if(root -> Left == NULL && root -> Right == NULL) {
            return 1;
        }
        size_t leftDepth = _Depth(root -> Left);
        size_t rightDepth = _Depth(root -> Right);
        return max(leftDepth, rightDepth) + 1;          //+1是根节点
    }

    //翻转 HomeBrew作者没写出来的那个🐶
    void _Reverise(Node<T>* root) {
        if(root == NULL) {
            return ;
        }
        swap(root -> Left, root -> Right);
        _Reverise(root -> Left);
        _Reverise(root -> Right);
    }
    void _Destory(Node<T>* root) {
        if(root == NULL) {
            return;
        }
        _Destory(root -> Left);
        _Destory(root -> Right);
        delete root;
        root = NULL;

    }
public:
    BinTree():root(NULL){}
    BinTree(T* arr,const T& invalid,size_t len) {
        size_t index = 0;
        root = _Create(arr, len, invalid,index);
    }
    BinTree(const BinTree<T>& t) {
        root = _Copy(t.root);
    }
    void PreOrder() {
        _PreOrder(root);
        cout << endl;
        return;
    }
    void InOrder() {
        _InOrder(root);
        cout << endl;
        return;
    }
    void PostOrder() {
        _PostOrder(root);
        cout << endl;
        return;
    }
    void LevelOrder() {
        _LevelOrder(root);
        cout << endl;
        return;
    }
    size_t Size() {
        return _Size(root);
    }

    size_t K_Level_Size(int K) {
        return _K_Level_Size(root, K);
    }

    size_t Depth() {
        return _Depth(root);
    }

    void Reverse() {
        _Reverise(root);
    }

    ~BinTree() {
        _Destory(root);
        root = NULL;
    }

};


#endif