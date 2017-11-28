#include <stdio.h>
#define MAXSIZE 1000

int N, adj_list[MAXSIZE][MAXSIZE];

typedef struct {
    int status, parent, root;
} vertex;

typedef struct {
    vertex a[MAXSIZE];
} graph;

void init_graph(graph *g) {
    int i;
    for (i = 1; i <= N; ++i) {
        g->a[i].status = 0;
        g->a[i].parent = 0;
        g->a[i].root = 0;
    }
}

void DFS(graph *g, int u, int r) {
    int i;
    g->a[u].status = 1;
    g->a[u].root = r;
    for (i = 1; i <= adj_list[u][0]; ++i) {
        if (adj_list[u][i] == 0)
            continue;
        if (g->a[i].status == 0) {
            g->a[i].parent = u;
            DFS(g, i, r);
        }
    }
    g->a[u].status = 2;
}

int DFS_forest(graph *g) {
    init_graph(g);
    int i, k = 0;
    for (i = 1; i <= N; ++i) {
        if (g->a[i].status == 0) {
            DFS(g, i, i);
            ++k;
        }
    }
    return k;
}

int compare(int a, int b) {
    if (a > b)
        return a;
    return b;
}

void read_graph(FILE *input) {
    int i, u, v;
    fscanf(input, "%d", &N);
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d %d", &u, &v);
        adj_list[u][0] = compare(adj_list[u][0], v);
        adj_list[v][0] = compare(adj_list[v][0], u);
        adj_list[u][v] = 1;
        adj_list[v][u] = 1;
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    graph g;
    read_graph(input);
    fprintf(output, "%d\n", DFS_forest(&g));

    return 0;
}