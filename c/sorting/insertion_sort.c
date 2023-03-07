#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void insertion_sort(int* A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0 && A[j] < A[j-1]; j--)
            swap(&A[j], &A[j-1]);
}

void insertion_sort2(int* A, int n) {
    for (int i = 0; i < n; i++) {
        int j = i;
        int val = A[j];
        for (; j > 0 && val < A[j-1]; j--)
            A[j] = A[j-1];
        A[j] = val;
    }
}

int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    insertion_sort2(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
