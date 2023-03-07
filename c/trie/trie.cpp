#include <iostream>
#include <string.h>


struct TrieNode {
    static const int branchCount = 26;

    bool isWord;
    TrieNode* next[branchCount];

    TrieNode() : isWord(false) {
        memset(next, NULL, sizeof(next));
    };
};


class Trie {
public:
    Trie();
    ~Trie();
    void insert(const char* word);
    bool search(const char* word);

private:
    void deleteNode(TrieNode* root);
    TrieNode* m_root;
};


Trie::Trie() : m_root(new TrieNode) {}
Trie::~Trie() {
    deleteNode(m_root);
}

void Trie::insert(const char* word) {
    TrieNode* location = m_root;
    while (*word) {
        if (!location->next[*word - 'a']) {
            location->next[*word - 'a'] = new TrieNode;
        }
        location = location->next[*word - 'a'];
        word++;
    }
    location->isWord = true;
}

bool Trie::search(const char* word) {
    TrieNode* location = m_root;
    while (*word && location) {
        location = location->next[*word - 'a'];
        word++;
    }
    return location != NULL && location->isWord;
}

void Trie::deleteNode(TrieNode* root) {
    for (int i = 0; i < TrieNode::branchCount; i++) {
        if (root->next[i] != NULL)
            deleteNode(root->next[i]);
    }
    delete root;
}

int main() {
    Trie t;
    t.insert("google");
    t.insert("googol");
    if (t.search("hello"))
        std::cout << "hello found" << std::endl;
    else
        std::cout << "hello not found" << std::endl;
    if (t.search("google"))
        std::cout << "google found" << std::endl;
    return 0;
}
