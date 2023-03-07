#include <stdio.h>
#include <stdlib.h>

int find_major_element(int* nums, int n) {
    int candidate;
    int times = 0;

    for (int i = 0; i < n; ++i) {
        if (times == 0) {
            candidate = nums[i];
            ++times;
        } else {
            if (candidate == nums[i])
                ++times;
            else
                --times;
        }
    }

    return candidate;
}

int main() {
    int nums[] = {0, 0, 0, 0, 1, 2, 3};
    int major = find_major_element(nums, sizeof(nums)/sizeof(int));
    printf("Major element is %d\n", major);
    return 0;
}
