/**
 * Beauty of Programming 4.1 and LeetCode 226
 * invert a binary tree
 * given a binary tree, return its mirror.
 */


#include <stdio.h>
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

struct tree_node* invert_tree(struct tree_node* root) {
    if (root == NULL)
        return NULL;

    struct tree_node* left = root->left;
    root->left = invert_tree(root->right);
    root->right = invert_tree(left);

    return root;
}

void preorder(struct tree_node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main() {

    struct tree_node* root = create_node(8);
    root->left = create_node(6);
    root->left->left = create_node(5);
    root->left->right = create_node(7);
    root->right = create_node(10);
    root->right->left = create_node(9);
    root->right->right = create_node(11);

    preorder(root);
    puts("");

    root = invert_tree(root);

    preorder(root);
    puts("");

    return 0;
}

