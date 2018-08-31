//
//  main.cpp
//  排序
//
//  Created by maochongxin on 2018/8/31.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

template <typename T>
void Swap(T& a,T& b) {
    T c(a);
    a = b;
    b = c;
    return;
}

template <typename T>
void BubbleSort(T* arr,size_t length,bool (*func)(const T&,const T&)) {
    for (int i = 0; i < length; i++) {
        for (int j = 1; j < length - i; j++) {
            if (!func(arr[j - 1],arr[j])) {
                Swap<T>(arr[j - 1], arr[j]);
            }
        }
    }
    return ;
}

template <typename T>
void SelectSort(T* arr,size_t length,bool (*func)(const T&,const T&)) {
    for (int i = 0; i < length; i++) {
        int _min = i;
        for (int j = i + 1; j < length; j++) {
            if (!func(arr[_min],arr[j])) {
                _min = j;
            }
        }
        Swap<T>(arr[_min], arr[i]);
    }
    return ;
}

template <typename T>
void InsertSort(T* arr,size_t length,bool (*func)(const T&,const T&)) {
    for (int i = 1; i < length; i++) {
        T key = arr[i];
        size_t j = i - 1;
        while (j >= 0 && func(key,arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void ShellSort(T* arr,size_t length,bool (*func)(const T&,const T&)) {
    size_t gap = round(length << 1);
    while (gap) {
        for (size_t i = gap; i < length; i++) {
            T temp = arr[i];
            size_t j = i;
            while (j >= gap && !func(arr[j - gap],temp)) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap = round(gap << 1);
    }
    return;
}

template <typename T>
void Merge(T* arr,size_t p,size_t q,size_t r) {
    size_t lLen = q - p + 1;
    size_t rLen = r - q;
    T* L = new T(lLen + 1);
    T* R = new T(rLen + 1);
    int i,j;
    for (i = 0; i < lLen; i++) {
        *(L + i) = arr[p + i];
    }
    for (j = 0; j < rLen; j++) {
        *(R + j) = arr[q + j + 1];
    }
    *(L + lLen) = numeric_limits<T>::max();
    *(R + rLen) = numeric_limits<T>::max();
    i = j = 0;
    for (size_t l = p; l <= r; l++) {
        if (L[i] <= R[j]) {
            arr[l] = L[i++];
        } else {
            arr[l] = R[j++];
        }
    }
}

template <typename T>
void MergeSort(T* arr,size_t p,size_t r) {
    if (p < r) {
        size_t q = p + (r - p) / 2;
        MergeSort(arr, p, q);
        MergeSort(arr, q + 1, r);
        Merge(arr, p, q, r);
    }
}


template <typename T>
void QuickSort(T* arr,size_t left,size_t right,bool (*func)(const T&,const T&)){
    size_t l = left;
    size_t r = right;
    T v = arr[(left + right) / 2];
    
    while (l <= r) {
        while (func(arr[l],v)) { ++l; }
        while (func(v,arr[r])) { --r; }
        if (l <= r) {
            Swap<T>(arr[l], arr[r]);
            ++l;
            --r;
        }
    }
    if (l == r) { l++; }
    if (left < r) {
        QuickSort<T>(arr, left, r,func);
    }
    if (l < right) {
        QuickSort<T>(arr, l, right,func);
    }
}

bool cmp(const int& a,const int& b) {
    return a < b;
}
bool cmp(const string& a,const string& b) {
    return a < b;
}
bool cmp(const double& a,const double& b) {
    return a < b;
}
int main(int argc, const char * argv[]) {
    string arr[] = {"asdad","wdaf","asdasv","wwwwww","scvcxvs","gfgdvv","ssdqgfv","oouhjkh"};
    int arr2[] = {2,23,9,1,12,5,5323,23};
    double arr3[] = {1.1,2.2,1.3,1.32,2.222,3.333,3.0,1.11};
//    InsertSort(arr3, 8, cmp);
//    SelectSort(arr3, 8, cmp);
//    BubbleSort(arr3, 8, cmp);
//    QuickSort(arr3, 0, 7, cmp);    // string fail
    MergeSort(arr3, 0, 7);
    for (int i = 0; i < 8; i++) {
        cout << arr3[i] << " ";
    }
    return 0;
}
