#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 1100

int arr[MAX_SIZE][MAX_SIZE];
int N;

//queue type and operations
typedef struct {
    int q[MAX_SIZE];
    int top, tail;
} queue;

void make(queue *inst) {
    inst->top = 1;
    inst->tail = 0;
}

int empty(queue *inst) {
    return (inst->top > inst->tail);
}

int top(queue *inst) {
    return inst->q[inst->top];
}

void enqueue(int data, queue *inst) {
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
    vertex data[MAX_SIZE];
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
        int n = top(&q);
        dequeue(&q);
        int K = arr[n][0];
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

int BFS_forest(graph *g) {
    init(g);
    int i, comp = 0;
    for (i = 1; i <= N; ++i) {
        if (g->data[i].status == 0) {
            BFS(g, i);
            ++comp;
        }
    }
    return comp;
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

void path(graph *g, int v, FILE *output) {
    int path[MAX_SIZE], i = 1, j;
    if (g->data[v].dist == INT_MAX) {
        fprintf(output, "%d\n", 0);
        return;
    }
    int k = g->data[v].dist;
    int origin_size = g->data[v].dist;
    fprintf(output, "%d ", k);
    while (k >= 0) {
        path[i] = v;
        ++i;
        if (g->data[v].parent == N)
            break;
        else
            v = g->data[v].parent;
        --k;
    }
    for (j = origin_size; j > 0; --j)
        fprintf(output, "%d ", path[j]);
    fprintf(output, "\n");
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    graph G;
    read_data(input);
    init(&G);
    BFS(&G, N);
    int i;
    for (i = 1; i < N; ++i)
        path(&G, i, output);
    fprintf(output, "%d\n", BFS_forest(&G));

    return 0;
}