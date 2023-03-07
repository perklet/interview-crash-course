#include <iostream>
#include <vector>


struct TreeNode {
    int val;
    struct tree_node* left;
    struct tree_node* right;

    TreeNode(val);
};

TreeNode::TreeNode(int val) {
    this->val = val;
    left = right = NULL;
}

void print_stack(std::vector<TreeNode*> s) {
    for (auto& n : s) {
        std::cout << n->val <<std::endl;
    }
}

void find_path(TreeNode* root, target) {
    if (root == NULL)
        return;

    std::vector<TreeNode*> s
