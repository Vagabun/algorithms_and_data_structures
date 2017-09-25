#include <stdio.h>

long long source[3000010];
long long dest[3000010];
long long count[10];

long long get_digit(long long n, long long i) {
    i -= 1;
    long long j, p = 1;
    for (j = 0; j < i; ++j)
        p *= 10;
    return ((n / p) % 10);
}

long long get_length(long long m) {
    long long l = 0;
    while (m > 0) {
        ++l;
        m /= 10;
    }
    return l;
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 0, max = -1;
    while (fscanf(input, "%lli", &n) != EOF) {
        if (n > max)
            max = n;
        source[counter] = n;
        ++counter;
    }

    long long i, j;
    for (i = 1; i <= get_length(max); ++i) {
        for (j = 0; j < 10; ++j)
            count[j] = 0;
        for (j = 0; j < counter; ++j)
            ++count[get_digit(source[j], i)];
        long long sum = 0;
        for (j = 0; j < 10; ++j) {
            long long tmp = count[j];
            count[j] = sum;
            sum += tmp;
        }
        for (j = 0; j < counter; ++j) {
            long long d = get_digit(source[j], i);
            dest[count[d]] = source[j];
            ++count[d];
        }
        for (j = 0; j < counter; ++j)
            source[j] = dest[j];
    }

    for (j = 0; j < counter; ++j)
        fprintf(output, "%lli ", source[j]);

    fclose(input);
    fclose(output);

    return 0;
}