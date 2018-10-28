//
//  main.cpp
//  AVL Tree
//
//  Created by maochongxin on 2018/10/28.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#include "AVLTree.h"
int main(int argc, const char * argv[]) {
    vector<int> vec = {1,2,3,4,5,6,7,8,9};
    AVL<int> t(vec);
    cout << t;
    cout << t.FindMax() -> data;
    return 0;
}
