/**
 * given n, find out how many unique BSTs with [1...n]
 * https://leetcode.com/problems/unique-binary-search-trees/
 */

#include <stdio.h>
#include <stdlib.h>

int numTrees(int n) {
    if (n == 0)
        return 0;
    int* nums = malloc(sizeof(int) * (n + 1));
    nums[0] = 1;

    for (int i = 1; i <= n; i++) {
        int num = 0;
        for (int k = 0; k <= i; k++)
            num += nums[k - 1] * nums[i - k];
        nums[i] = num;
    }

    return nums[n];
}

int main() {
    int n = 4;
    printf("Unique trees as of %d is %d\n", n, numTrees(n));
    return 0;
}
