/**
 * Given n, find how many zeros in the end of n!
 */
#include <stdio.h>
#include <stdlib.h>

int end_zeros(n) {
    int count = 0;
    while (n) {
        count += n / 5;
        n /= 5;
    }
    return count;
}

int main() {
    int n = 100;
    printf("%d zeros in the end of %d!", end_zeros(n), n);
    return 0;
}
