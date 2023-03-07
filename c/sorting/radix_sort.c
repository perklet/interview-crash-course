#include <stdio.h>
#include <stdlib.h>

void radix_sort(int* A, int n) {
    int semi_sorted[n];
    int sig = 1;
    int largest = A[0];

    for (int i = 0; i < n; i++)
        if (A[i] > largest) largest = A[i];

    while (largest / sig > 0) {
        int bucket[10] = {0};
        for (int i = 0; i < n; i++)
            bucket[(A[i] / sig) % 10]++;
        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i-1];
        for (int i = n - 1; i >= 0; i--)
            semi_sorted[--bucket[(A[i] / sig) % 10]] = A[i];
        for (int i = 0; i < n; i++)
            A[i] = semi_sorted[i];
        sig *= 10;
    }
}


int main() {

    int n = 10;
    int A[] = {80, 91, 72, 43, 55, 66, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    radix_sort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
