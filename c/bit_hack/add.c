#include <stdio.h>

int add(int a, int b) {
    while (b) {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum, b = carry;
    }
    return a;
}

int main() {
    printf("%d", add(99, 99));
    return 0;
}
