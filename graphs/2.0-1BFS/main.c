#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DEQ_MAXSIZE 2000020
#define MAXSIZE 100010
#define ZERO 1
#define ONE 2

int deq[DEQ_MAXSIZE];
int edges[MAXSIZE][MAXSIZE];
//int vertices[MAXSIZE][MAXSIZE];
int vertices[MAXSIZE];
//int temporar[MAXSIZE][MAXSIZE];
//int tem[100000][10000];

int N, M;

//deque type and operations
typedef struct {
    int *data;
    int head, tail;
} deque;

void init_deque(deque *inst) {
    inst->data = deq;
    inst->head = (DEQ_MAXSIZE / 2) - 1;
    inst->tail = (DEQ_MAXSIZE / 2) - 1;
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

//graph type and operations
typedef struct {
    int dist, parent;
} vertex;

typedef struct {
    vertex data[MAXSIZE];
} graph;

void init_graph(graph *g) {
    int i;
//    g->data = (vertex*)vertices;
    for (i = 1; i <= N; ++i) {
        g->data[i].parent = 0;
        g->data[i].dist = INT_MAX;
    }
}

void read_data(FILE *input) {
    int i, u, v, d;
    fscanf(input, "%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        fscanf(input, "%d %d %d", &u, &v, &d);
        if (v > edges[u][0])
            edges[u][0] = v;
        edges[u][v] = d + 1;
    }
}

int main() {
//    deque d;
//    init_deque(&d);
//    push_back(&d, 20);
//    push_front(&d, 30);

//    edges = malloc(sizeof(int*) * MAXSIZE);
//    int i;
//    for (i = 0; i < MAXSIZE; ++i)
//        edges[i] = malloc(sizeof(int) * MAXSIZE);

//    graph g;
//    N = 10;
//    init_graph(&g);
//    edges[1][0] = 6;
//    int i;
//    for (i = 1; i <= MAXSIZE; ++i)
//        edges[i] = -1;

    FILE *input = fopen("input.txt", "r");
    read_data(input);

    printf("test\n");

    return 0;
}