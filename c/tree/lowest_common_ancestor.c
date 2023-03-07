/**
 * find lowest common ancestor of two nodes
 */

struct tree_node* lca(struct tree_node* root,
                      struct tree_node* p,
                      struct tree_node* q)
{
    if (!root || root == p || root == q)
        return root;
    struct tree_node* left = lca(root->left, p, q);
    struct tree_node* right = lca(root->right, p, q);

    if (!left)
        return right;
    if (!right)
        return left;
    return root;
}
