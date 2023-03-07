/**
 * A problem from LeetCode
 * https://leetcode.com/problems/jump-game/
 */

#define max(a,b) ((a)>(b)?(a):(b))
bool canJump(int* nums, int n) {
    int i;
    int reach = 0;
    for (i = 0; i < n && i <= reach; i++)
        reach = max(i + nums[i], reach);
    return i == n;
}
