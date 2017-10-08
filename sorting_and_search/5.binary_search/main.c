#include <stdio.h>

long long x[1000010];

long long binary_search_1(long long n, long long k) {
    long long a = 1, b = n;
    // check invariant
    if (x[a] > k)
        return 0;
    if (x[a] == k)
        return a;
    if (x[b] < k)
        return 0;
    while (a + 1 < b) {
        long long m = (a + b)/2;
        if (x[m] < k)
            a = m;
        else
            b = m;
    }
    if (x[b] == k)
        return b;
    else
        return 0;
}

long long binary_search_2(long long n, long long k) {
    long long a = 1, b = n;
    if (x[a] > k)
        return 0;
    if (x[b] < k)
        return b;
    if (x[b] == k)
        return b;
    while (a + 1 < b) {
        long long m = (a + b)/2;
        if (x[m] <= k)
            a = m;
        else
            b = m;
    }
    if (x[a] <= k)
        return a;
    else
        return 0;
}

long long binary_search_3(long long n, long long k) {
    long long a = 1, b = n;
    if (x[a] < k)
        return 0;
    if (x[b] > k)
        return b;
    if (x[b] == k)
        return b;
    while (a + 1 < b) {
        long long m = (a + b)/2;
        if (x[m] >= k)
            a = m;
        else
            b = m;
    }
    if (x[a] >= k)
        return a;
    else
        return 0;
}


int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char c;
    long long k, n, counter = 1;
    fscanf(input, "%c %lli", &c, &k);
    while (fscanf(input, "%lli", &n) != EOF) {
        x[counter] = n;
        ++counter;
    }

//    printf("%lli", counter);

    printf("%lli", binary_search_3(counter - 1, k));
//    fprintf(output, "%c %lli", c, k);

    fclose(input);
    fclose(output);
    return 0;
}