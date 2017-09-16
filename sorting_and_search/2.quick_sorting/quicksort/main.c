#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long arr[3000010];

long long random(long long n) {
    long long x = rand();
    x <<= 15;
    x ^= rand();
    x %= n;
    return x;
}

void quicksort(long long a, long long b) {
    if (a >= b)
        return;
    long long m = random(b-a+1)+a;
//    long long m = (a + b)/2;
    //pivot point
    long long k = arr[m];
    long long l = a - 1;
    long long r = b + 1;
    while (1) {
        do {
            ++l;
            if (arr[l] >= k)
                break;
        }
        while (arr[l] >= k);
        do {
            --r;
            if (arr[r] <= k)
                break;
        }
        while (arr[r] <= k);
        if (l >= r)
            break;
        long long tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
    }
    quicksort(a, r);
    quicksort(r+1, b);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        arr[counter] = n;
        ++counter;
    }

    srand(time(NULL));
    quicksort(0, counter-1);

    for (int i = 0; i < counter; ++i)
        fprintf(output, "%lli ", arr[i]);

    return 0;
}