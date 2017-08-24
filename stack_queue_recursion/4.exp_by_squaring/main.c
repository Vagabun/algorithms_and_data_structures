#include <stdio.h>

struct array{
    double a[40][40];
    int size;
};

struct array multiply_arr(struct array a, struct array b, int size) {
    struct array c;
    c.size = size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0;
            for (int k = 0; k < size; ++k) {
                sum = sum + a.a[i][k] * b.a[k][j];
            }
            c.a[i][j] = sum;
        }
    }
    return c;
}

struct array pow(struct array x, long long int n) {
    if (n == 1) return x;
    if (n % 2 == 0) return pow(multiply_arr(x, x, x.size), n/2);
    else return multiply_arr(x, pow(x, n - 1), x.size);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long int N;
    int P;
    struct array a1, a2;

    fscanf(input, "%lli %d", &N, &P);
    a1.size = P;
    for (int i = 0; i < a1.size; ++i) {
        for (int j = 0; j < a1.size; ++j) {
            fscanf(input, "%lf", &a1.a[i][j]);
        }
    }

    a2 = pow(a1, N);

    for (int k = 0; k < P; ++k) {
        for (int l = 0; l < P; ++l) {
            fprintf(output, "%.6lf ", a2.a[k][l]);
        }
        fprintf(output, "\n");
    }

    return 0;
}