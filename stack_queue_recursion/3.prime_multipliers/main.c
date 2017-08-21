#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10010
//#define MIN(a, b) ((a < b) ? a : b)

struct q {
    unsigned long long int q[MAX_SIZE];
    int top, tail;
};

typedef struct q QUEUE;

void make(QUEUE *inst) {
    inst->top = 1;
    inst->tail = 0;
}

int empty(QUEUE *inst) {
    return (inst->top > inst->tail);
}

unsigned long long int top(QUEUE *inst) {
    return inst->q[inst->top];
}

void enqueue(unsigned long long int data, QUEUE *inst) {
    inst->tail += 1;
    inst->q[inst->tail] = data;
}

void dequeue(QUEUE *inst) {
    inst->top += 1;
}

unsigned long long int min(unsigned long long int a, unsigned long long int b) {
    unsigned long long int m;
    if (a < b) m = a;
    else m = b;
    return m;
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N;
    long int P1, P2, P3;
    fscanf(input, "%d %li %li %li", &N, &P1, &P2, &P3);

    QUEUE Q1, Q2, Q3;

    make(&Q1);
    make(&Q2);
    make(&Q3);

    enqueue(P1, &Q1);
    enqueue(P2, &Q2);
    enqueue(P3, &Q3);

    int n = 1;
    unsigned long long int m;
    while (n < N) {
        m = min(min(top(&Q1), top(&Q2)), top(&Q3));
        n++;
        enqueue(m*P1, &Q1);
        enqueue(m*P2, &Q2);
        enqueue(m*P3, &Q3);
        if (top(&Q1) == m) dequeue(&Q1);
        if (top(&Q2) == m) dequeue(&Q2);
        if (top(&Q3) == m) dequeue(&Q3);
    }

    fprintf(output, "%llu", m);

    fclose(input);
    fclose(output);

    return 0;
}