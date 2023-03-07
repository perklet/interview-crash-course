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

void postorder(struct tree_node* root) {

    if (root == NULL) 
        return;

    struct stack* s = create_stack(100);
    push_stack(s, root);
    // output stack
    struct stack* o = create_stack(100);

    while (!is_empty_stack(s)) {
        struct tree_node* node = top_stack(s);
        pop_stack(s);
        push_stack(o, node);

        if (node->left != NULL)
            push_stack(s, node->left);
        if (node->right != NULL)
            push_stack(s, node->right);
    }

    while (!is_empty_stack(o)) {
        struct tree_node* node = top_stack(o);
        printf("%d ", node->val);
        pop_stack(o);
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

    postorder(root);

    return 0;
}






