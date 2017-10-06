#include <stdio.h>

long long x[1000010];

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char c;
    long long k, n, counter = 0;
    fscanf(input, "%c %lli", &c, &k);
//    while (fscanf(input, "%lli", &n) != EOF) {
//        x[counter] = n;
//        ++counter;
//    }
    fprintf(output, "%c %lli", c, k);

    fclose(input);
    fclose(output);
    return 0;
}