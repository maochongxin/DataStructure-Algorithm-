//
//  KMP.h
//  KMP
//
//  Created by maochongxin on 2018/10/27.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#ifndef KMP_h
#define KMP_h
#include <string>
using std::string;

static int _next[100];
void getNext(string str) {
    int i = 0,j = -1;
    _next[0] = -1;
    while (i < str.length()) {
        if (j == -1 || str[i] == str[j]) {
            i++;
            j++;
            _next[i] = j;
        } else {
            j = _next[j];
        }
    }
}

int KMP(string str,string s) {
    getNext(s);
    int i = 0, j = 0;
    while (i < str.length() && j < (int)s.length()) {   //一定要注意length是unsigned类型,与负数做比较事会发生强转 可能会导致结果永远为真或假
        if (j == -1 || str[i] == s[j]) {
            i++;
            j++;
        } else {
            j = _next[j];
        }
    }
    return j == s.length() ? i - j : -1;
}


#endif /* KMP_h */

