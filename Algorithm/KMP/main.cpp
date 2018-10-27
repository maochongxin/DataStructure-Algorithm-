//
//  main.cpp
//  KMP
//
//  Created by maochongxin on 2018/10/27.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include <iostream>
#include "KMP.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string s1,s2;
    while (cin >> s1 >> s2) {
        cout << KMP(s1, s2) << endl;
    }
    return 0;
}
