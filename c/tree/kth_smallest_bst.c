/**
 * find the kth smallest number in a BST
 *
 * https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stack.h"

int kth_smallest(struct tree_node* root, k) {
    if (!root)
        return -1;

    struct stack* s = create_stack(100);

    while (root) {
        push_stack(s, root);
        root = root->left;
    }


    while (k) {
        struct tree_node* node;
        do {
            node = top_stack(s);
            pop_stack(s);
            if (--k == 0)
                return node->val;
        } while (!node->right);

        node = node->right;

        while (node) {
            push_stack(s, node);
            node = node->left;
        }
    }

    return -1;

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

    printf("%d\n", kth_smallest(root, 1));
    printf("%d\n", kth_smallest(root, 2));
    printf("%d\n", kth_smallest(root, 3));

    return 0;
}



