/*
 * connect a tree node to its right sibling in a ordinary binary tree
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 */

struct tree_node {
    int val;
    struct tree_node* left;
    struct tree_node* right;
    struct tree_node* next;
};

void connect(struct tree_node* root) {
    struct tree_node* head = root;
    struct tree_node* prev = NULL;
    struct tree_node* cur = NULL;

    while (head != NULL) {
        cur = head;
        prev = NULL;
        head = NULL;

        while (cur) {
            if (cur->left) {
                if (prev)
                    prev->next = cur->left;
                else
                    head = cur->left;
                prev = cur->left;
            }
            if (cur->right) {
                if (prev)
                    prev->next = cur->right;
                else
                    head = cur->right;
                prev = cur->right;
            }
            cur = cur->next;
        }
    }
}

