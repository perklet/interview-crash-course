int removeDuplicates(int A[], int n) {
    if (n <= 1) return n;
    
    int s = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] != A[s]) {
            A[++s] = A[i];
        }
    }
    return s + 1;
}
