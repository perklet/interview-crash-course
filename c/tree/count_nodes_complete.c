/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode* root) {
    if (!root)
        return 0;
    int left_height = 0, right_height = 0;
    struct TreeNode* left = root;
    struct TreeNode* right = root;
    
    while (left) {
        left = left->left;
        left_height++;
    }
    
    while (right) {
        right = right->right;
        right_height++;
    }
    
    if (left_height == right_height)
        return (0x1 << left_height) - 1;
    return countNodes(root->left) + countNodes(root->right) + 1;
}
