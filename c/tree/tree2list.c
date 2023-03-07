#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void concat(struct tree_node* x, struct tree_node* y) {
    x->right = y;
    y->left = x;
}

struct tree_node* convert_circular(struct tree_node* root) {
    if (!root)
        return NULL;
    struct tree_node* left = convert_circular(root->left);
    struct tree_node* right = convert_circular(root->right);

    if (!left && !right) {
        root->left = root;
        root->right = root;
        return root;
    }

    struct tree_node* tail_right = right ? right->left : NULL;

    if (!left)
        concat(right->left, root);
    else
        concat(left->left, root);

    if (!right)
        concat(root, left);
    else
        concat(root, right);

    if (left && right)
        concat(tail_right, left);

    return left ? left : root;
}

struct tree_node* convert(struct tree_node* root) {
    struct tree_node* head = convert_circular(root);
    head->left->right = NULL;
    head->left = NULL;
    return head;
}

int main() {
    struct tree_node* root = create_node(4);
    root->left = create_node(2);
    root->left->left = create_node(1);
    root->left->left->left = create_node(0);
    root->left->right = create_node(3);
    root->right = create_node(5);
    root->right->right = create_node(6);

    struct tree_node* head = convert(root);

    while (head) {
        printf("%d ", head->val);
        head = head->right;
    }

}

