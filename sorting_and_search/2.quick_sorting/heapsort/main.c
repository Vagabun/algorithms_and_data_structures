#include <stdio.h>

long long heap[3000010];

void lift(long long c) {
    //c - position
    while (c > 1 && heap[c] > heap[c/2]) {
        long long p = c/2;
        long long tmp = heap[c];
        heap[c] = heap[p];
        heap[p] = tmp;
        c = p;
    }
}

void shift(long long p, const long long l) {
    while (p * 2 <= l) {
        long long c = p * 2;
        if (c < l && heap[c+1] > heap[c])
            ++c;
        if (heap[p] >= heap[c])
            break;
        long long tmp = heap[p];
        heap[p] = heap[c];
        heap[c] = tmp;
        p = c;
    }
}

void get(long long *l) {
    long long tmp = heap[1];
    heap[1] = heap[*l];
    heap[*l] = tmp;
    --*l;
    shift(1, *l);
}

void put(long long n, long long *l) {
    ++*l;
    heap[*l] = n;
    lift(*l);
}

void heapsort(long long *l) {
    long long i;
    for (i = *l; i >= 1; --i)
        get(l);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter, l = 0;
    while (fscanf(input, "%lli", &n) != EOF) {
        put(n, &l);
    }
    counter = l;

    heapsort(&l);

    for (int i = 1; i <= counter; ++i) {
        fprintf(output, "%lli ", heap[i]);
    }

    return 0;
}