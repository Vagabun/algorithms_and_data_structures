#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 3000010

void merge_sort(long long *arr, long long a, long long b) {
    long long k;
    if (a >= b)
        return;
    long long mid = (a + b) / 2;
    merge_sort(arr, a, mid);
    merge_sort(arr, mid + 1, b);
    long long i = a;
    long long j = mid + 1;
    long long *buff = malloc(MAXSIZE * sizeof(long long));
    for (k = a; k <= b; ++k) {
        if ((j > b) || (i <= mid && arr[i] < arr[j])) {
            buff[k] = arr[i];
            ++i;
        } else {
            buff[k] = arr[j];
            ++j;
        }
    }
    for (k = a; k <= b; ++k)
        arr[k] = buff[k];
    free(buff);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long i, n, counter = 0;
    long long *x = malloc(MAXSIZE * sizeof(long long));
    while (fscanf(input, "%lli", &n) != EOF) {
        x[counter] = n;
        ++counter;
    }

    merge_sort(x, 0, counter - 1);

    for (i = 0; i < counter; ++i)
        fprintf(output, "%lli ", x[i]);

    free(x);
    fclose(input);
    fclose(output);

    return 0;
}