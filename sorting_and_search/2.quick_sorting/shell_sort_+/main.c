#include <stdio.h>
#include <math.h>

long long arr[3000010];

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    long long h = 1;
    while (h < (long long)round(counter/9.0))
        h = 3 * h + 1;

    long long k;
    while (h > 0) {
        for (k = 0; k < h; ++k) {
            long long i = k + h;
            while (i < counter) {
                long long y = arr[i];
                long long j = i - h;
                while (j >= 0 && arr[j] > y) {
                    arr[j+h] = arr[j];
                    j -= h;
                }
                arr[j+h] = y;
                i += h;
            }
        }
        h /= 3;
    }

    long long l;
    for (l = 0; l < counter; ++l) {
        fprintf(output, "%lli ", arr[l]);
    }

    fclose(input);
    fclose(output);

    return 0;
}