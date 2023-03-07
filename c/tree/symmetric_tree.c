/**
 * determine if a tree is symmetric
 * https://leetcode.com/problems/symmetric-tree/
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

bool sym(struct tree_node* left, struct tree_node* right) {
    if (!left && !right)
        return true;
    if (left && !right || right && !left)
        return false;
    if (left && right)
        return (left->val == right->val) &&
            sym(left->left, right->right) &&
            sym(left->right, right->left);
}

bool is_symmetric(struct tree_node* root) {
    if (root == NULL)
        return true;
    return sym(root->left, root->right);
}


int main() {
    
    struct tree_node* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(5);
    root->left->left = create_node(3);
    root->left->right = create_node(8);
    root->right->left = create_node(8);
    root->right->right = create_node(3);
    is_symmetric(root) ? printf("yes\n") : printf("no\n");
    return 0;
}


