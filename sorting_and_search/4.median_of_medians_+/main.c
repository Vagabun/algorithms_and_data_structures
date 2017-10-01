#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long arr[1000010];

long long random(long long n) {
    long long x = rand();
    x <<= 15;
    x ^= rand();
    x %= n;
    return x;
}

long long search(long long a, long long b, long long k) {
    if (a == b)
        return arr[a];
    long long m = random(b - a + 1) + a;
    long long pivot = arr[m];
    long long l = a - 1;
    long long r = b + 1;
    while (1) {
        while (1) {
            ++l;
            if (arr[l] >= pivot)
                break;
        }
        while (1) {
            --r;
            if (arr[r] <= pivot)
                break;
        }
        if (l >= r)
            break;
        long long tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
    }
    l = r;
    r += 1;
    if (k <= l)
        return search(a, l, k);
    else
        return search(r, b, k);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, k, counter = 0;
    fscanf(input, "%lli", &k);
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    srand(time(NULL));

    fprintf(output, "%lli", search(0, counter-1, k-1));

    return 0;
}