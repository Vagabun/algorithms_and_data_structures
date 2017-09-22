#include <stdio.h>
#include <string.h>

long long arr[3000010] = { 0 };

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

//    memset(arr, 0, 3000010);
    long long n, counter = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        ++arr[n];
        ++counter;
    }
    long long i, j;
    for (i = 0; i <= counter; ++i) {
        if (arr[i] > 0) {
            for (j = 0; j < arr[i]; ++j)
                fprintf(output, "%lli ", i);
        }
    }

    return 0;
}