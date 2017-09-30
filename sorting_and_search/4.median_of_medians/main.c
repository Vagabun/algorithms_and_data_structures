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

void quicksort(long long a, long long b) {
    if (a >= b)
        return;
    //pivot point
    long long m = random(b - a + 1) + a;
    long long k = arr[m];
    long long l = a - 1;
    long long r = b + 1;
    while (1) {
        while (1) {
            ++l;
            if (arr[l] >= k)
                break;
        }
        while (1) {
            --r;
            if (arr[r] <= k)
                break;
        }
        if (l >= r)
            break;
        long long tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
    }
    quicksort(a, r);
    quicksort(r+1, b);
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
    if (k < l)
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

    printf("%lli", search(0, counter-1, k));


//    for (int i = 0; i < counter; ++i)
//        fprintf(output, "%lli ", arr[i]);

//    fclose(input);
//    fclose(output);

    return 0;
}