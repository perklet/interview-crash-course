#include <stdio.h>
#include <stdlib.h>

int min_depth(struct tree_node* root) {
    if (!root)
        return 0;
    if (!root->left)
        return min_depth(root->right) + 1;
    if (!root->right)
        return min_depth(root->left) + 1;

    return MIN(min_depth(root->left), min_depth(root->right)) + 1;
}

