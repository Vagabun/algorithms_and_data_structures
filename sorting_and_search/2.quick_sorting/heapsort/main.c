#include <stdio.h>
#include <stdlib.h>

struct h {
    long long l;
    long long *h = malloc(3000010 * sizeof(long long));
};

typedef struct h HEAP;

void make(HEAP *instance) {
    instance->l = 0;
}

void lift(HEAP *instance, long long c) {
    while (c > 1 && instance->h[c] > instance->h[c/2]) {
        long long p = c/2;
        long long tmp = instance->h[c];
        instance->h[c] = instance->h[p];
        instance->h[p] = tmp;
        c = p;
    }
}

void put(HEAP *instance, long long n) {
    ++instance->l;
    instance->h[instance->l] = n;
    lift(instance, instance->l);
}



int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    HEAP H;
    make(&H);

    long long n, counter = 1;
    while (fscanf(input, "%lli", &n) != EOF) {
        put(&H, n);
        ++counter;
    }

    return 0;
}