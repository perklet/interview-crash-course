#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "tree.h"


bool check(struct tree_node* root, int min, int max);

bool valid_bst(struct tree_node* root) {
    if (root == NULL)
        return true;
    return check(root, INT_MIN, INT_MAX);
}

bool check(struct tree_node* root, int min, int max) {
    return root->val > min && root->val < max &&
        (root->left ? check(root->left, min, root->val) : true) &&
        (root->right ? check(root->right, root->val, max) : true) ;
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

    bool result = valid_bst(root);
    printf("valid: %d\n", result);

    return 0;
}
