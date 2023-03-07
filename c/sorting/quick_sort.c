#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int* A, int start, int end) {

    int pivot = A[end];
    int small = start - 1;

    for (int i = start; i < end; i++)
        if (A[i] < pivot)
            swap(&A[i], &A[++small]);

    swap(&A[++small], &A[end]);

    return small;
}

void do_quick_sort(int* A, int start, int end) {

    if (A == NULL || start == end) 
        return;

    int index = partition(A, start, end);

    if (index > start)
        do_quick_sort(A, start, index - 1);
    if (index < end)
        do_quick_sort(A, index + 1, end);
}

void quick_sort(int* A, int n) {
    do_quick_sort(A, 0, n-1);
}


int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    quick_sort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
