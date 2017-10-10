#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct {
    double a, b, c, d;
} eq_data;

double f(double x) {
    return eq_data.a*log(eq_data.b + x) - eq_data.c/(eq_data.d + x);
}

double bisection(double l, double r) {
    double fA = f(l), m;
    do {
        m = (l + r)/2;
        if (m == l || m == r)
            return m;
        if (fA * f(m) < 0)
            r = m;
        else
            l = m;
    } while ((l + r)/2 != l && (l + r)/2 != r);
    return m;
}
int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fscanf(input, "%lf %lf %lf %lf", &eq_data.a, &eq_data.b, &eq_data.c, &eq_data.d);
    fprintf(output, "%.6lf", bisection(0, 1e10));
    return 0;
}