#include <stdio.h>

long int arr[1010][1010];
long int part_sums[1010][1010];

void precalc(const int n, const int m) {
    int i, j;
    long int t;
    for (j = 0; j <= m; ++j)
        part_sums[0][j] = 0;

    for (i = 1; i <= n; ++i) {
        part_sums[i][0] = 0;
        t = 0;
        for (j = 1; j <= m ; ++j) {
            t += arr[i][j];
            part_sums[i][j] = part_sums[i-1][j] + t;
        }
    }
}

int main() {

    int n, m, i, j, a, b, alpha, beta;
    long int Q, k, sum;

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fscanf(input, "%d %d %li", &n, &m, &Q);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m ; ++j) {
            fscanf(input, "%li", &arr[i][j]);
        }
    }

    precalc(n, m);

    for (k = 0; k < Q; ++k) {
        fscanf(input, "%d %d %d %d", &a, &b, &alpha, &beta);
        sum = part_sums[b][beta] - part_sums[a-1][beta] - part_sums[b][alpha-1] + part_sums[a-1][alpha-1];
        fprintf(output, "%li ", sum);
    }

    return 0;
}