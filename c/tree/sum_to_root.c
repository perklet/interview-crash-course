/*
 * Given a binary tree, return sum of all the paths
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/
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

int sum(struct tree_node* root, int s) {
    if (!root->left && !root->right)
        return s * 10 + root->val;
    int val = 0;
    if (root->left)
        val += sum(root->left, s * 10 + root->val);
    if (root->right)
        val += sum(root->right, s * 10 + root->val);

    return val;
}

int sum_to_root(struct tree_node* root) {
    if (!root)
        return 0;
    return sum(root, 0);
}



int main() {
    
    /*
             1
            /  \
          1     0
    */
    struct tree_node* root = create_node(1);
    root->left = create_node(1);
    root->right = create_node(2);

    printf("The sum is %d\n", sum_to_root(root));

    return 0;

}
