#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10010

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

int main() {

    QUEUE Q1, Q2, Q3;

    make(&Q1);

    printf("%d", Q1.top);

    return 0;
}