#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void prime_sieve(int n, bool* primes) {
    primes[0] = primes[1] = false;

    for (int i = 0; i < n; i++) {
        primes[i] = true;
    }

    int limit = sqrt(n);
    for (int i = 2; i <= limit; i++) {
        if (primes[i]) {
            for (int j = i*i; j < n; j += i)
                primes[j] = false;
        }
    }
}

int main() {
    const int n = 100;
    bool primes[n];
    prime_sieve(n, primes);

    for (int i = 0; i < n; i++) {
        if (primes[i])
            printf("%d ", i);
    }
    puts("");
    return 0;
}
