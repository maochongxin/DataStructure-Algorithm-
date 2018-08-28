//
//  main.cpp
//  Queue
//
//  Created by maochongxin on 2018/8/28.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

template <class T>
class Queue {
public:
    typedef T* pointer;
    typedef T& reference;
private:
    size_t basic = 10;
    pointer arr = nullptr;
    void Delete() {
        delete [] arr;
        arr = nullptr;
    }
    pointer begin;
    pointer end;
    pointer Tail;
    
    size_t size;    //总容量
    size_t least;   //剩余空间
    size_t length;  //队列长度
public:
    Queue() {
        arr = new T[10];
        begin = arr;
        end = arr + 10;
        Tail = arr - 1;
        least =  10;
        length = 0;
        size = 10;
    }
    Queue(size_t n,T data) {
        arr = new T[2 * n]();
        for (int i = 0; i < n; i++) {
            arr[i] = data;
        }
        begin = arr;
        Tail = begin + n - 1;
        end = arr + 2 * n;
        least = end - Tail;
        length = n;
        size = n;
    }
    Queue(T data) {
        arr = new T[10];
        arr[0] = data;
        begin = arr;
        Tail = begin;
        end = arr + 10;
        least = end - Tail - 1;
        length = 1;
        size = 10;
    }
    ~Queue() {
        Delete();
    };
    
    void push(T data) {
        if (least >= 1) {
            *(++Tail) = data;
            length++;
            least--;
        } else {
            pointer t = arr;
            arr = new T[size *= 2];
            for (int i = 0; i < length; i++) {
                arr[i] = t[i];
            }
            delete [] t;
            t = nullptr;
            *(++Tail) = data;
            length++;
            least = size - length;
        }
    }
    T front() const {
        if(arr) {
            return *begin;
        } else {
            return NULL;
        }
    }
    bool empty() {
        return begin > Tail;
    }
    void pop() {
        if (empty()) {
            least--;
        }
        if(!empty()) {
            begin++;
            length--;
        }
    }
    size_t len() {
        return length;
    }
};

int main(int argc, const char * argv[]) {
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
    Queue<int> q1;
    for (int i = 0; i < 11; i++) {
        q1.push(arr[i]);
    }
    while (!q1.empty()) {
        cout << q1.front() << "---" << q1.len() << endl;
        q1.pop();
    }
    Queue<int> q2(12,6);
    while (!q2.empty()) {
        cout << q2.front() << "---" << q2.len() << endl;
        q2.pop();
    }
    Queue<int> q3(0);
    for (int i = 0; i < 11; i++) {
        q3.push(arr[i]);
    }
    while (!q3.empty()) {
        cout << q3.front() << "---" << q3.len() << endl;
        q3.pop();
    }
    return 0;
}
