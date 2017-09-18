#include <stdio.h>

#define MAXSIZE 3000010

long long x[MAXSIZE];
long long y[MAXSIZE];

void merge_sort(long long a, long long b) {
    if (a >= b)
        return;
    long long mid = (a + b) / 2;
    merge_sort(a, mid);
    merge_sort(mid + 1, b);
    long long i = a;
    long long j = mid + 1;
    long long k;
    for (k = a; k <= b; ++k) {
        if ((j > b) || (i <= mid && x[i] < x[j])) {
            y[k] = x[i];
            ++i;
        } else {
            y[k] = x[j];
            ++j;
        }
    }
    for (k = a; k <= b; ++k)
        x[k] = y[k];
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long i, n, counter = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        x[counter] = n;
        ++counter;
    }

    merge_sort(0, counter - 1);

    for (i = 0; i < counter; ++i)
        fprintf(output, "%lli ", x[i]);

    fclose(input);
    fclose(output);

    return 0;
}