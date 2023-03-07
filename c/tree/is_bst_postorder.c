#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree_node {
    int val;
    struct tree_node* left;
    struct tree_node* right;
};

bool is_bst_postorder(int* sequence, int length) {
    if (sequence == NULL || length <= 0)
        return false;
    int root = length - 1;

    int pivot = -1;
    for (int i = 0; i < length - 1; ++i) {
        if (sequence[i] > root) {
            pivot = i;
            break;
        }
    }

    for (int i = pivot; i < length - 1; ++i) {
        if (sequence[i] < root)
            return false;
    }

    if (pivot > 0 && pivot < length - 1)
        return is_bst_postorder(sequence, pivot)
            && is_bst_postorder(sequence + pivot, length - 1);
    else
        return true;
}

int main() {
    int sequence[] = {5, 7, 6, 9, 1, 10, 8};
    printf("is bst: %d\n", is_bst_postorder(sequence, sizeof(sequence)/sizeof(int)));
    return 0;
}
