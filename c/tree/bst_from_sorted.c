/**
 * construct a BST from sorted array
 * https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct tree_node* bst_from_sorted(int* nums, int n) {
    if (!nums)
        return NULL;
    return _convert(nums, 0, n-1);
}

struct tree_node* _convert(int* nums, int left, int right) {
    if (left > right)
        return NULL;
    
    int mid = left + (right - left) / 2;
    struct tree_node* node = create_node(nums[mid]);
    node->left = _convert(nums, left, mid - 1);
    node->right = _convert(nums, mid + 1, right);
    return node;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};
    struct tree_node* root = bst_from_sorted(nums, sizeof(nums) / sizeof(int));
    return 0;
}
