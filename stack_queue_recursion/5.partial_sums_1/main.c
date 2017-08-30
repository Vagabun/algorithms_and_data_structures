#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000010

void precalc(long int *part_sums, const long int *arr, const long int n) {
    int i;
    part_sums[0] = 0;
    for (i = 1; i <= n; ++i)
        part_sums[i] = part_sums[i-1] + arr[i];
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long int n, Q, a, b;
    int i, j;

    long int *arr = malloc(MAXSIZE * sizeof(long int));
    long int *part_sums = malloc(MAXSIZE * sizeof(long int));

    fscanf(input, "%li %li", &n, &Q);
    for (i = 1; i <= n; ++i) {
        fscanf(input, "%li", &arr[i]);
    }

    precalc(part_sums, arr, n);

    for (j = 0; j < Q; ++j) {
        fscanf(input, "%li %li", &a, &b);
        fprintf(output, "%li ", part_sums[b]-part_sums[a-1]);
    }

    free(arr);
    free(part_sums);
    fclose(input);
    fclose(output);
    return 0;
}