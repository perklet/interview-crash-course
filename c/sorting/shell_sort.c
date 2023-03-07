#include <stdio.h>

/**
 * shell sort 是插入排序的升级版，通过不断缩小gap到1，使得数组是有序的
 */


void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void shell_sort(int* A, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
            for (int j = i - gap; j >= 0 && A[j] > A[j + gap]; j -= gap)
                swap(&A[j], &A[j + gap]);
}

int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    shell_sort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
