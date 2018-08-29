//
//  main.cpp
//  List
//
//  Created by maochongxin on 2018/8/29.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

template <class T>
struct Node {
    typedef Node<T>* List;
    T data;
    List Preview;
    List Next;
    Node(T _data) {data = _data; Preview = NULL; Next = NULL;}
};

template <class T>
class List {
public:
    typedef Node<T>* ListNode;
private:
    ListNode Root;
    
    size_t _getLength(ListNode node) {
        //        int len = 0;
        //        ListNode first = Root;
        //        while (node -> Next != first) {
        //            node = node -> Next;
        //            len++;
        //        }
        //        return len + 1;
        ListNode cur = node;
        int cnt = 0;
        while (cur != end()) {
            cnt++;
            cur = cur -> Next;
        }
        return cnt + 1;
    }
    bool _Insert(ListNode node,const T& _data,size_t index) {
        if (index > this -> getLength()) {
            return false;
        } else {
            int th = 0;
            while (th < index) {
                th++;
                node = node -> Next;
            }
            node -> data = _data;
            return true;
        }
    }
    
    void _print(ListNode node) {
        while (node != end()) {
            cout << node -> data << " ";
            node = node -> Next;
        }
        cout << node -> data;
        //        int times = 0;
        //        while (times < getLength()) {
        //            cout << node -> data << " ";
        //            node = node -> Next;
        //            times++;
        //        }
        
    }
    
    void _push_back(ListNode node,T data) {
        ListNode pre = node -> Preview;
        ListNode newNode = new Node<T>(data);
        pre -> Next = newNode;
        newNode -> Preview = pre;
        newNode -> Next = node;
        node -> Preview = newNode;
    }
    
    bool _Remove(ListNode node,size_t index) {
        if (index > getLength()) {
            return false;
        } else {
            int th = 1;
            ListNode cur = node;
            while (th < index) {
                cur = cur -> Next;
                th++;
            }
            ListNode bef = cur -> Preview;
            ListNode next = cur -> Next;
            bef -> Next = next;
            next -> Preview = bef;
            delete cur;
            cur = nullptr;
            return true;
        }
    }
    
    bool _empty(ListNode node) {
        return node == NULL;
    }
    ListNode getNode(ListNode node) {
        return node;
    }
    void _Reverse(ListNode node) {
        ListNode tmp = Root -> Preview;
        while (node != tmp) {
            ListNode pre = node -> Preview;
            ListNode next = node -> Next;
            node -> Next = pre;
            node -> Preview = next;
            node = next;
        }
        node -> Next = node -> Preview;
        node -> Preview = node -> Next;
        ListNode s = Root;
        Root = Root -> Next;
        Root -> Preview = (s -> Preview) -> Next;
    }
    
    
public:
    List() = default;
    List(T _data) {
        Root = new Node<T>(_data);
        Root -> Next = Root;
        Root -> Preview = Root;
    }
    List(T* arr,size_t len) {
        Root = new Node<T>(arr[0]);
        Root -> Next = Root;
        Root -> Preview = Root;
        for (int i = 1; i < len; i++) {
            this -> push_back(arr[i]);
        }
        
    }
    size_t getLength() {
        return _getLength(Root);
    }
    bool Insert(const T& _data,size_t index) {
        return _Insert(Root, _data, index);
    }
    void push_back(const T& data) {
        _push_back(Root, data);
    }
    bool Remove(size_t index) {
        return _Remove(Root, index);
    }
    ListNode begin() {
        return getNode(Root);
    }
    ListNode end() {
        return getNode(Root -> Preview);
    }
    bool empty() {
        return _empty(Root);
    }
    void Reverse() {
        _Reverse(Root);
    }
    void print() {
        _print(Root);
    }
};


int main(int argc, const char * argv[]) {
    //    List<int> l(3);
    //    l.push_back(1);
    //    l.push_back(2);
    //    l.push_back(3);
    //    l.print();
    //    cout << endl;
    //    cout << l.begin() -> data;
    //    cout << endl;
    //    cout << l.end() -> data;
    //    cout << endl;
    //    l.Reverse();
    //    l.print();
    int arr[] = {1,2,3,4,5,6,7,8};
    List<int> l(arr,8);
    l.print();
    cout << endl << l.getLength();
    cout << endl;
    //    cout << endl;
    //    cout << l.end() -> data << endl;
    //    l.Reverse();
    //    cout << l.end() -> data << endl;
    //    l.print();
    //    cout << endl;
    //    l.push_back(12);
    //    l.print();
    //    cout << endl << l.getLength() << endl;
    //    l.Reverse();
    //    l.print();
    //    cout << endl;
    //    l.push_back(100);
    //    l.print();
    //    cout << endl;
    //    cout << l.end() -> data << "---" << l.begin() -> data << "---" << l.getLength() << endl;
    l.Remove(2);
    l.print();
    cout << endl;
    cout << l.getLength();
    return 0;
}
