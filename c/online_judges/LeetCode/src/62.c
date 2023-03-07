typedef unsigned long long largeInt;

largeInt choose(largeInt n, largeInt k) {
    if (n < k) {
        return 0;
    }
    k = k < n - k ? k : n - k;
    largeInt r = 1;
    for (largeInt d = 1; d <= k; d++) {
        r *= n--;
        r /= d;
    }
    
    return r;
}



int uniquePaths(int m, int n) {
    return choose(m + n - 2, n - 1);
}
