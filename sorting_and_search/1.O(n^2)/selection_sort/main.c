#include <stdio.h>

long long arr[10010];

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 0, i, j, k, m;
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    for (i = 0; i < counter - 1; ++i) {
        m = i;
        for (j = i + 1; j < counter; ++j) {
            if (arr[j] < arr[m])
                m = j;
        }
        if (m != i) {
            long long temp = arr[m];
            arr[m] = arr[i];
            arr[i] = temp;
        }
    }

    for (k = 0; k < counter; ++k) {
        fprintf(output, "%lli ", arr[k]);
    }

    return 0;
}