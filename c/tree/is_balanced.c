/**
 * determine if a tree is balanced
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int height(struct tree_node* root) {
    if (!root)
        return 0;
    
    int left_height = height(root->left);
    if (left_height == -1)
        return -1;
    int right_height = height(root->right);
    if (right_height == -1)
        return -1;

    if (abs(left_height - right_height) > 1)
        return -1;
    return max(left_height, right_height) + 1;
}

bool is_balanced(struct tree_node* root) {
    return height(root) != -1;
}
