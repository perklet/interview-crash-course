#include <stdio.h>
#include <stdlib.h>

int lower(int* nums, int n, int target) {
    int first = 0, last = n;
    while (first != last) {
        int middle = (first + last) / 2;
        if (target > nums[middle]) 
            first = middle + 1;
        else
            last = middle;
    }
    return first;
}

int upper(int* nums, int n, int target) {
    int first = 0, last = n;
    while (first != last) {
        int middle = (first + last) / 2;
        if (target >= nums[middle]) // only difference with lower
            first = middle + 1;
        else
            last = middle;
    }
    return first;
}

int main() {
    int nums[] = {0, 0, 1, 2, 3, 3, 3, 4, 5};
    for (int i = 0; i < 9; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    printf("lower is %d\n", lower(nums, 9, 9));
    printf("upper is %d\n", upper(nums, 9, 3));
    return 0;
}
