/**
 * determine if two trees are the same
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree_node {
    int val;
    struct tree_node* left;
    struct tree_node* right;
};

struct tree_node* create_node(int val) {
    struct tree_node* node = malloc(sizeof(struct tree_node));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}
bool is_same_tree(struct tree_node* t1, struct tree_node* t2) {
    if (!t1 || !t2)
        return t1 == t2;
    else
        return t1->val == t2->val &&
            is_same_tree(t1->left, t2->left) &&
            is_same_tree(t1->right, t2->right);
}

int main() {

    /*
             10
            /  \
          5     12
        /  \  /
       3   8 11
    */
    struct tree_node* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(12);
    root->left->left = create_node(3);
    root->left->right = create_node(8);
    root->right->left = create_node(11);

    is_same_tree(root, root) ? puts("yes") : puts("no");

    return 0;
}

