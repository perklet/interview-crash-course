/**
 * find the lowest common ancestor of two BST nodes
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 */

#include <stdio.h>
#include <stdlib.h>

struct tree_node* find_lca_bst(struct tree_node* root, 
                               struct tree_node* p,
                               struct tree_node* q)
{
    while (root) {
        if (root->val > p->val && root->val > q->val)
            root = root->left;
        else if (root->val < p->val && root->val < q->val)
            root = root->right;
        else
            return root;
    }
}


