double myPow(double x, int n) {
    if (x == 1.0) return 1.0;
    if (x == -1.0) return n % 2 == 0 ? 1 : -1;
    if (n < 0) return 1.0 / myPow(x, -n);
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n == 2) return x * x;

    if (n % 2 == 0) {
        return myPow(myPow(x, n / 2), 2);
    } else {
        return myPow(myPow(x, n / 2), 2) * x;
    }
    
}
