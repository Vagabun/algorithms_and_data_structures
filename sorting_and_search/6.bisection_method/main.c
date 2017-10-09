#include <stdio.h>
#include <math.h>

double f(double a, double b, double c, double d, double x) {
    return a*log(b + x) - c/(d + x);
}

double bisection(double l, double r, double a, double b, double c, double d) {
    double fA = f(a, b, c, d, l), m;
    do {
        m = (l + r)/2;
        if (m == l || m == r)
            return m;
        if (fA * f(a, b, c, d, m) < 0)
            r = m;
        else
            l = m;
    } while ((l + r)/2 != l && (l + r)/2 != r);
    printf("%lf", m);
}
int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    double a, b, c, d;
    fscanf(input, "%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("%lf", bisection(0, 1e10, a, b, c, d));
    return 0;
}