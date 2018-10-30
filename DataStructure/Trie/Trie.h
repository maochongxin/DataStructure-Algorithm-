//
//  Trie.h
//  Trie
//
//  Created by maochongxin on 2018/10/30.
//  Copyright © 2018 Maochongxin. All rights reserved.
//

#ifndef Trie_h
#define Trie_h
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class TrieNode {
public:
    char val;
    int cnt;
    int precnt;
    TrieNode* son[26];
    bool isEnd;
    TrieNode():cnt(0),isEnd(false),precnt(0) {
        memset(son, NULL, sizeof(son));
    }
    TrieNode(char c):val(c),cnt(0),isEnd(false),precnt(0) {
        memset(son, NULL, sizeof(son));
    }
};
class Trie {
private:
    TrieNode* root;
    void _insert(TrieNode*& root,const string& str);
    bool _find(TrieNode* root,const string& str);
    void _preorder(TrieNode* root);
    void _levelorder(TrieNode* root);
    bool _remove(TrieNode*& root, int pos,const string& str);
    int _countWordsWithPrefix(TrieNode* root,const string& str);
public:
    Trie() {
        root = new TrieNode();
    }
    Trie(char c) {
        root = new TrieNode(c);
    }
    void insert(const string& str) {
        _insert(root, str);
    }
    bool find(const string& str) {
        return _find(root, str);
    }
    void buildTree(vector<string> vec) {
        for (string str : vec) {
            _insert(root, str);
        }
    }
    bool remove(const string& str) {
        return _remove(root, 0,str);
    }
    void lelelOrder() {
        _levelorder(root);
    }
    void preorder() {
        _preorder(root);
    }
    int countWirdsWithPrefix(const string& str) {
        return _countWordsWithPrefix(root, str);
    }
};

void Trie::_insert(TrieNode*& root, const string& str) {
    TrieNode* p = root;
    if (str.empty()) {
        return;
    } else {
        for (int i = 0; i < str.size(); i++) {
            if (p -> son[str[i] - 'a'] == NULL) {
                p -> son[str[i] - 'a'] = new TrieNode(str[i]);
                p -> cnt++;
            }
            p -> son[str[i] - 'a'] -> precnt++;
            p = p -> son[str[i] - 'a'];
        }
        p -> isEnd = true;
    }
}

bool Trie::_find(TrieNode* root, const string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (root -> son[str[i] - 'a'] == NULL) {
            return false;
        } else {
            root = root -> son[str[i] - 'a'];
        }
    }
    return root -> isEnd;
}

void Trie::_levelorder(TrieNode* root) {
    if (root == NULL) {
        return;
    }
    queue<TrieNode*> q;
    q.push(root);
    while (!q.empty()) {
        TrieNode* p = q.front();
        q.pop();
        cout << p -> val;
        for (int i = 0; i < 26; i++) {
            if (p -> son[i] != NULL) {
                q.push(p -> son[i]);
            }
        }
    }
    cout << endl;
}
void Trie::_preorder(TrieNode* root) {
    if (root != NULL) {
        cout << root -> val;
        for (int i = 0; i < 26; i++) {
            _preorder(root -> son[i]);
        }
    }
}

bool Trie::_remove(TrieNode*& root, int pos, const string& str) {
    if (pos == str.size()) {
        root -> isEnd = false;
        return root -> cnt == 0;
    }
    if (root -> son[str[pos] - 'a'] == NULL) {
        return false;
    }
    if (_remove(root -> son[str[pos] - 'a'], pos + 1,str)) {
        delete root -> son[str[pos] - 'a'];
        root -> son[str[pos] - 'a'] = NULL;
        root -> precnt--;
        if (--root -> cnt == 0 && root -> isEnd == false) {
            return true;
        }
    }
    return false;
}

int Trie::_countWordsWithPrefix(TrieNode* root, const string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (root -> son[str[i] - 'a'] == NULL) {
            return 0;
        }
        root = root -> son[str[i] - 'a'];
    }
    return root -> precnt;
}

#endif /* Trie_h */
