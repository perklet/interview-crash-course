#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}


struct Heap {
    int* el;
    int size;
};


void heap_build(struct Heap* heap) {
}

// 向结尾插入新元素，并上滤到正确的位置
void heap_swim(struct Heap* heap, int k) {
    while (k > 1 && heap->el[k/2] < heap->el[k]) {
        swap(&heap->el[k/2], &heap->el[k]);
        k /= 2;
    }
}

// 把root处的元素下滤到正确位置
void heap_sink(struct Heap* heap, int size, int element) {
}


void heap_sort(int* A, int n) {
}

void heap_delete_max() {}

int main() {

    int n = 10;
    int A[] = {8, 9, 7, 4, 5, 6, 3, 2, 1, 0};

    puts("Before: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    heap_sort(A, n);

    puts("Sorted: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    puts("\n");

    return 0;
}
