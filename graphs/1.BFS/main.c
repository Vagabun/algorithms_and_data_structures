#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 10010

int arr[1100][1100];
int N;

//queue type and operations
typedef struct {
    long long q[MAX_SIZE];
    int top, tail;
} queue;

void make(queue *inst) {
    inst->top = 1;
    inst->tail = 0;
}

int empty(queue *inst) {
    return (inst->top > inst->tail);
}

long long top(queue *inst) {
    return inst->q[inst->top];
}

void enqueue(long long data, queue *inst) {
    inst->tail += 1;
    inst->q[inst->tail] = data;
}

void dequeue(queue *inst) {
    inst->top += 1;
}

//graph type and operations
typedef struct {
    int status;
    int dist;
    int parent;
    int root;
} vertex;

typedef struct {
    vertex data[1100];
} graph;

void init(graph *g) {
    int i;
    for (i = 1; i <= N; ++i) {
        g->data[i].status = 0;
        g->data[i].dist = INT_MAX;
        g->data[i].parent = 0;
        g->data[i].root = 0;
    }
}

void BFS(graph *g, int s) {
    g->data[s].status = 1;
    g->data[s].dist = 0;
    g->data[s].root = s;
    queue q;
    make(&q);
    enqueue(s, &q);
    while (!empty(&q)) {
        long long n = top(&q);
        dequeue(&q);
        long long K = arr[n][0];
        int i;
        for (i = 1; i <= K; ++i) {
            if (arr[n][i] == 0) // arr[n][i] ~ v
                break;
            else if (g->data[arr[n][i]].status == 0) {
                g->data[arr[n][i]].status = 1;
                g->data[arr[n][i]].dist = g->data[n].dist + 1;
                g->data[arr[n][i]].parent = n;
                g->data[arr[n][i]].root = s;
                enqueue(arr[n][i], &q);
            }
        }
    }
}

void read_data(FILE *input) {
    fscanf(input, "%d", &N);
    int i, j, K;
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d", &K);
        arr[i][0] = K;
        for (j = 1; j <= K; ++j)
            fscanf(input, "%d", &arr[i][j]);
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    graph G;
    read_data(input);
    init(&G);
    BFS(&G, N);
    printf("\n");


//
//    graph g;
//    init(&g);
//    int N;
//    int i, j, K;
//    for (i = 1; i <= N; ++i) {
//        fscanf(input, "%d", &K);
//        arr[i][0] = K;
//        for (j = 1; j <= K; ++j)
//            fscanf(input, "%d", &arr[i][j]);
//    }
//    printf("\n");
    return 0;
}