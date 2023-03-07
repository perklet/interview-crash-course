#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

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

void free_tree(struct tree_node* root) {
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

#endif
