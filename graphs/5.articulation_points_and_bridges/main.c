#include <stdio.h>

int adj_list[1000][1000];
int N, tm;

typedef struct {
    int status, parent, root, art_point, t1, t2;
} vertex;

typedef struct {
    vertex data[1000];
} graph;

void init_adj_list() {
    int i;
    for (i = 1; i <= N; ++i)
        adj_list[i][0] = 0;
}

void init_graph(graph *g) {
    int i;
    for (i = 1; i <= N; ++i) {
        g->data[i].status = 0;
        g->data[i].parent = 0;
        g->data[i].art_point = 0;
    }
}

void dfs(graph *g, int u, int r) {
    tm = tm + 1;
    g->data[u].t1 = tm;
    g->data[u].status = 1;
    g->data[u].root = r;
}

void read_data(FILE *input) {
    fscanf(input, "%d", &N);
    int i, u, v;
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d %d", &u, &v);
        adj_list[u][++adj_list[u][0]] = v;
        adj_list[v][++adj_list[v][0]] = u;
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    init_adj_list();
    read_data(input);
    printf("test\n");
    return 0;
}