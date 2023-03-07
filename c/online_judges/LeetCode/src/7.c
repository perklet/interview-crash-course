int reverse(int x) {
    if (x == -2147483648) return 0;
    long int result = 0;
    int sign = x > 0 ? 1 : -1;
    x *= sign;
    while (x) {
        result *= 10;
        result += x % 10;
        if (result > INT_MAX) return 0;
        x /= 10;
    }
    return sign * result;
}
