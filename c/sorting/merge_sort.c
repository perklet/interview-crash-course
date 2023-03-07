#include <stdio.h>
#include <stdlib.h>


/**
 * Top-down approch
 */

#define SWAP(a, b) do {int temp = a; a = b; b = temp;} while(0)
void do_merge_sort(int* A, int start, int end);
void merge(int* A, int start, int mid, int end);

void merge_sort(int* A, int n) {

    if (A == NULL || n < 1)
        return;

    do_merge_sort(A, 0, n - 1);
}

void do_merge_sort(int* A, int start, int end) {

    if (start == end)
        return;

    int mid = (start + end) / 2;
    do_merge_sort(A, start, mid);
    do_merge_sort(A, mid + 1, end);
    merge(A, start, mid, end);
}

/**
 * 注意这里的merge算法会反复分配内存
 */
void merge(int* A, int start, int mid, int end) {

    int len1 = mid - start + 1;
    int len2 = end - mid;

    int S[len1];
    int E[len2];

    for (int i = 0; i < len1; ++i) {
        S[i] = A[start + i];
    }

    for (int i = 0; i < len2; ++i) {
        E[i] = A[mid + 1 + i];
    }

    int i = start, j = 0, k = 0;

    while (j < len1 && k < len2) {
        if (S[j] <= E[k]) {
            A[i++] = S[j++];
        } else {
            A[i++] = E[k++];
        }
    }

    while (j < len1) {
        A[i++] = S[j++];
    }

    while (k < len2) {
        A[i++] = E[k++];
    }
}

/**
 * 这种归并方法不需要反复开辟内存空间，但是需要一个额外的固定的辅助数组
 */
int aux[10];
void merge2(int* A, int lo, int mid, int hi) {
    // 首先把原来数组中的元素复制到辅助数组中
    for (int k = lo; k < hi; k++)
        aux[k] = A[k]

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            A[k] = aux[j++]


/**
 * Bottom-up approch
 */

void merge_sort2(int* A, int n) {
    


int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("");

    merge_sort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("");

    return 0;
}
