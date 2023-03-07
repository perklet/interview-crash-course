int max(int j, int k) {
    return j > k ? j : k;
}

// dynamic programming
// max(A[n]) = max(max(A[n-1], max(A[n-1]) + n)
int maxSubArray(int* nums, int numsSize) {
    int sum = 0;
    int m = INT_MIN;
    
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        m = max(m, sum);
        if (sum < 0) { // previous sequence contributes negatively
            sum = 0;
        }
    }
    
    return m;
}
