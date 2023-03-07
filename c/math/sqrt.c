#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double sqrt_newton(double x) {
    if (x <= 0) return 0;
    const double EPS = x * 0.0001;
    double y = x / 2; // initial guess
    while (fabs(y * y - x) > EPS) {
        y = (y + x / y) / 2;
    }

    return y;
}

int main() {
    printf("%f: sqrt is %f", 4.0, sqrt_newton(4.0));
    return 0;
}

