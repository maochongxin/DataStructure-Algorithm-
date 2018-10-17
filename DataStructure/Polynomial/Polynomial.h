//
//  Polynomial.h
//  Polynomial
//
//  Created by maochongxin on 2018/10/17.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#ifndef Polynomial_h
#define Polynomial_h
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const size_t maxSize = 10;

struct polyElem {
    double coef;
    int exp;
};

class polyClass {

private:
    polyElem* data;
    size_t length;
    size_t esize;   //剩余空间
    void SetEsize(size_t n) {
        esize = n;
    }
    
public:
    polyClass() {
        data = new polyElem[maxSize];
        length = 0;
        esize = maxSize;
        SetEsize(esize);
    }
    ~polyClass() {
        delete[] data;
    }
    size_t getEsize() {
        return this -> esize;
    }
    size_t getLength() const {
        return length;
    }
    void createList(const vector<double>& coef,const vector<int>& exp);
    polyClass& operator=(polyClass& s);
    friend polyClass& operator+(const polyClass&, const polyClass&);
    void display();
    void sort();
};

void polyClass::createList(const vector<double>& coef,const vector<int>& exp) {
    if (getEsize() < coef.size()) {
        delete[] data;
        data = new polyElem[maxSize + coef.size()];
        this -> SetEsize(maxSize + coef.size());
    }
    for (int i = 0; i < coef.size(); i++) {
        data[i].coef = coef[i];
        data[i].exp = exp[i];
    }
    length = coef.size();
    this -> SetEsize(maxSize);
}

polyClass& polyClass::operator=(polyClass& s) {
    if (this -> getEsize() < s.getEsize()) {
        delete[] data;
        data = new polyElem[s.getEsize()];
    }
    for (int i = 0; i < s.getLength(); i++) {
        data[i].coef = s.data[i].coef;
        data[i].exp = s.data[i].exp;
    }
    length = s.getLength();
    return *this;
}

polyClass& operator+(const polyClass& poly1, const polyClass& poly2) {
    static polyClass poly3;
    int l1 = 0,l2 = 0,l3 = 0;
    while (l1 < poly1.getLength() && l2 < poly2.getLength()) {
        if (poly1.data[l1].exp == poly2.data[l2].exp) {
            poly3.data[l3].coef = poly1.data[l1].coef + poly2.data[l2++].coef;
            poly3.data[l3++].exp = poly1.data[l1++].exp;
        } else {
            if (poly1.data[l1].exp > poly2.data[l2].exp) {
                poly3.data[l3].exp = poly1.data[l1].exp;
                poly3.data[l3++].coef = poly1.data[l1++].coef;
            } else {
                poly3.data[l3].exp = poly2.data[l2].exp;
                poly3.data[l3++].coef = poly2.data[l2++].coef;
            }
        }
    }
    while (l1 < poly1.getLength()) {
        poly3.data[l3].coef = poly1.data[l1].coef;
        poly3.data[l3++].exp = poly1.data[l1++].exp;
    }
    while (l2 < poly2.length) {
        poly3.data[l3].coef = poly2.data[l2].coef;
        poly3.data[l3++].exp = poly2.data[l2++].exp;
    }
    poly3.length = l3;
    return poly3;
}

void polyClass::sort() {
    std::sort(this -> data,this -> data + this -> getLength(),[](const polyElem& p1,const polyElem& p2) -> bool {return p1.exp < p2.exp;});
}

void polyClass::display() {
    int i = 0;
    bool first = true;
    while (i < length) {
        if (first) first = false;
        else if (data[i].coef > 0) cout << "+";
        if (data[i].exp == 0)
            cout << data[i].coef;
        else if (data[i].exp == 1)
            cout << data[i].coef << "x";
        else
            cout << data[i].coef << "x^" << data[i].exp;
        i++;
    }
}

#endif /* Polynomial_h */
