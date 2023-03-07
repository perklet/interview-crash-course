#include <stdio.h>
#include <stdlib.h>

int search_rotated(int* nums, int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == key)
            return mid;

        // lower half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= key && key < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        // upper half is sorted
        } else {
            if (nums[mid] < key && key <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int nums[] = {4, 5, 6, 7, 8, 0, 1, 2, 3};
    printf("0 in %d", search_rotated(nums, sizeof(nums) / sizeof(int), 0));
    return 0;
}
