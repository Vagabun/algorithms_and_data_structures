#include <stdio.h>

long long arr[1000010];

long long ternary_search(long long a, long long b) {
    while (b > a + 2) {
        long long h = (b - a)/3, l = a + h, r = b - h;
        if (arr[l] < arr[r])
            a = l;
        else
            b = r;
    }
    return arr[(a + b)/2];
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 1;
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    fprintf(output, "%lli", ternary_search(0, counter));

    fclose(input);
    fclose(output);
    return 0;
}