#include <stdio.h>
#include <math.h>

double f(double a, double b, double c, double d, double x) {
    return a*log(b + x) - c/(d + x);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    double a, b, c, d;
    fscanf(input, "%lf %lf %lf %lf", &a, &b, &c, &d);
    return 0;
}