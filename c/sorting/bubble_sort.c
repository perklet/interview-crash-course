#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void bubblesort(int* A, int n) {
    for (int i = 0; i < n; i++) 
        for (int j = i; j < n; j++)
            if (A[i] > A[j])
                swap(&A[i], &A[j]);
}

int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    bubblesort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
