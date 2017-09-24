#include <stdio.h>

long long x[3000010];
long long z[3000010] = { 0 };
long long y[3000010];

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 1;
    while (fscanf(input, "%lli", &n) != EOF) {
        x[counter] = n;
        ++counter;
    }

    long long min, max, i;
    min = max = x[1];
    for (i = 2; i < counter; ++i) {
        if (x[i] > max)
            max = x[i];
        else if (x[i] < min)
            min = x[i];
    }

    for (i = 1; i < counter; ++i)
        ++z[x[i]];

    for (i = min + 1; i <= max; ++i)
        z[i] += z[i-1];

    for (i = 1; i < counter; ++i) {
        y[z[x[i]]] = x[i];
        --z[x[i]];
    }

    for (i = 1; i < counter; ++i)
        fprintf(output, "%lli ", y[i]);

    fclose(input);
    fclose(output);

    return 0;
}