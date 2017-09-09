#include <stdio.h>

long long arr[10010];

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, i, j, k, counter = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    for (i = 0; i < counter - 1; ++i) {
        for (j = i + 1; j < counter; ++j) {
            if (arr[i] > arr[j]) {
                long long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (k = 0; k < counter; ++k)
        fprintf(output, "%lli ", arr[k]);

    fclose(input);
    fclose(output);
    return 0;
}