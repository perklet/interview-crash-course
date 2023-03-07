/**
 * Determine if there is a path sums up to given k
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_path_sum(struct tree_node* root, int sum) {
    if (!root)
        return false;
    if (root->val == sum && !root->left && !root->right)
        return true;
    return has_sum_path(root->left, sum - root->val) ||
           has_sum_path(root->right, sum - root->val);
}
