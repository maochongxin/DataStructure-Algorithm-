#ifdef _TRIE_H_
#define _TRIE_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Node {
    char val;
    int count;
    bool isEnd;
    std::vector<std::shared_ptr<Node>> _next;
    Node(char c): val(c),count(0),isEnd(false) {
        _next.resize(26,nullptr);
    }
};

class Trie {
private:
    std::shared_ptr<Node> root;
    
public:
    Trie() {
        root = std::make_shared<Node>('#');
    }
    void insert(std::string);
    bool find(std::string);
    int countWords(std::string);
};

void Trie::insert(std::string str) {
    std::shared_ptr<Node> t = this->root;
    for (const char& c : str) {
        if (t->_next[c - 'a'] == nullptr) {
            t->_next[c - 'a'] = std::make_shared<Node>(c);
        }
        t = t->_next[c - 'a'];
        t->count++;
    }
    t->isEnd = true;
}

bool Trie::find(std::string str) {
    std::shared_ptr<Node> t = this->root;
    for (const char& c : str) {
        t = t->_next[c - 'a'];
    }
    return t->isEnd;
}

int Trie::countWords(std::string str) {
    std::shared_ptr<Node> t = this->root;
    for (const char& c : str) {
        t = t->_next[c - 'a'];
    }
    return t->count;
}

#endif

