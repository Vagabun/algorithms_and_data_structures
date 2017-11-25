#include <stdio.h>
#define MAXSIZE 2000020

int deq[MAXSIZE];

typedef struct {
    int *data;
    int head, tail;
} deque;

void init(deque *inst) {
    inst->data = deq;
    inst->head = (MAXSIZE / 2) - 1;
    inst->tail = (MAXSIZE / 2) - 1;
}

int empty(deque *inst) {
    return inst->head == inst->tail;
}

void push_back(deque *inst, int data) {
    inst->data[inst->tail++] = data;
}

int pop_back(deque *inst) {
    if (empty(inst)) {
        return fprintf(stderr, "underflow\n");
    }
    return inst->data[--inst->tail];
}

void push_front(deque *inst, int data) {
    inst->data[--inst->head] = data;
}

int pop_front(deque *inst) {
    if (empty(inst)) {
        return fprintf(stderr, "underflow\n");
    }
    return inst->data[inst->head++];
}

int main() {
    deque d;
    init(&d);
    push_back(&d, 20);
    push_front(&d, 30);

    printf("test\n");

    return 0;
}