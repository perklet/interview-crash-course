#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

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

void inorder(struct tree_node* root) {
    struct stack* s = create_stack(100);
    struct tree_node* current = root;

    while (!is_empty_stack(s) || current) {
        if (current) {
            push_stack(s, current);
            current = current->left;
        } else {
            struct tree_node* node = top_stack(s);
            pop_stack(s);
            printf("%d ", node->val);
            current = node->right;
        }
    }
    puts("");
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

    inorder(root);

    return 0;
}
