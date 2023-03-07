#include <stdio.h>
#include <stdlib.h>

bool ugly_number(int n) {
    if (n <= 0)
        return false;
    if (n == 1)
        return true;
    while (n > 1) {
        if (n % 2 == 0)
            n /= 2;
        else if (n % 3 == 0)
            n /= 3;
        else if (n % 5 == 0)
            n /= 5;
        else
            return false;
    }
    return true;
}

int main() {
    while (1) {
        int n;
        scanf("%d", &n);
        ugly_number(n) ? puts("yes") : puts("no");
    }
    return 0;
}
