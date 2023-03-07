/**
 * given a array of numbers, each number appears twice except one.
 * https://leetcode.com/problems/single-number/
 */

/**
 * using XOR, we know that for any `n`: n^n == 0
 */
int single_number(int* A, int n) {
    int result = 0;
    for (int i = 0; i < n; i++)
        result ^= A[i];
    return result;
}
