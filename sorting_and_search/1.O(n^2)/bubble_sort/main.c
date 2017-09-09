#include <stdio.h>

long long arr[100010];

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long num, counter = 0, i, j, k;

    while (fscanf(input, "%lli", &num) != EOF) {
        arr[counter] = num;
        ++counter;
    }

    for (i = 1; i < counter; ++i) {
        if (arr[i] > arr[i-1])
            continue;
        j = i;
        while ((j > 0) && (arr[j] < arr[j-1])) {
            long long temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            --j;
        }
    }

    for (k = 0; k < counter; ++k)
        fprintf(output, "%lli ", arr[k]);

    fclose(input);
    fclose(output);

    return 0;
}