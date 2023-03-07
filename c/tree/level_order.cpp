#include <iostream>
#include <queue>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;

    TreeNode(int val);
};

TreeNode::TreeNode(int val) {
    this->val = val;
    left = NULL;
    right = NULL;
}

void level_order(TreeNode* root) {
    if (root == NULL)
        return;

    std::queue<TreeNode*> q;

    q.push(root);

    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        std::cout << node->val << std::endl;
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }

}

int main() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(6);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(11);

    level_order(root);

    return 0;
}

