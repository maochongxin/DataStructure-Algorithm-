//
//  main.cpp
//  Polynomial
//
//  Created by maochongxin on 2018/10/17.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include <iostream>
#include "Polynomial.h"
int main(int argc, const char * argv[]) {
    polyClass poly1, poly2, poly3;
    vector<double>coef1 = { 2,3.2,-6,10 };
    vector<int>exp1 = { 3,5,1,0 };
    vector<double>coef2 = { 6,1.8,-2,1,-2.5,-5 };
    vector<int>exp2 = { 1,5,3,2,4,0};
    poly1.createList(coef1, exp1);
    poly1.display(); cout << endl;
    poly1.sort();
    poly1.display();   //排序
    cout << endl;
    
    poly2.createList(coef2, exp2);
    poly2.display();
    poly2.sort();
    cout << endl;
    
    poly3 = poly1 + poly2;
    poly3.display();
    return 0;
}
