int searchInsert(int A[], int n, int target) {
    int i;
    for (i = 0; i < n && A[i] < target; i++)
        ;
    if (i == 0) {
        return 0;
    } else if ( i == n) {
        return n;
    } else {
        return i;
    }
}
