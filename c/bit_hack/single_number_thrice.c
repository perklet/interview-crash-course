/**
 * each number appears three times except for one
 * https://leetcode.com/problems/single-number-ii/
 */

#include <stdio.h>
/**
 * the trick here is to do a no-carry ternary plus
 */

int single_number(int* A, int n) {

    int h = 0; // a for upper bit
    int l = 0; // b for lower bit

    for (int i = 0; i < n; i++) {
        int a = A[i];

        h ^= (l & a);
        l ^= a;

        a = h & l;
        h &= ~a;
        l &= ~a;
    }

    return h | l;
}

int main() {
    int A[] = {1, 1, 1, 3};
    printf("%d\n", single_number(A, sizeof(A) / sizeof(int)));
    return 0;
}


