#include <stdio.h>

double pow(double x, long long int n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n % 2 == 0) return pow(x*x, n/2);
    else return x * pow(x, n - 1);
}

int main() {

    long long int N;
    int P;

    double a = 0.543728;
    printf("%.6f", pow(a, 20));
    return 0;
}