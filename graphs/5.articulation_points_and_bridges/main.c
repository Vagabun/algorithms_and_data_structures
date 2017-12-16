#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int adj_list[1010][1010];
int connected_components[1010] = { 0 };
int N, tm;

typedef struct {
    int status, parent, root, art_point, t1, low;
} vertex;

typedef struct {
    vertex data[1010];
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
    g->data[u].low = g->data[u].t1;
    int l_max = 0;
    int pow = 0;
    int i;
    for (i = 1; i <= adj_list[u][0]; ++i) {
        if (g->data[adj_list[u][i]].status == 0) {
            pow = pow + 1;
            g->data[adj_list[u][i]].parent = u;
            dfs(g, adj_list[u][i], r);
            g->data[u].low = MIN(g->data[u].low, g->data[adj_list[u][i]].low);
            l_max = MAX(l_max, g->data[adj_list[u][i]].low);
        }
        else if (g->data[u].parent != adj_list[u][i])
           g->data[u].low = MIN(g->data[u].low, g->data[adj_list[u][i]].t1);
    }
    if ((u == g->data[u].root && pow > 1) || (u != g->data[u].root && l_max >= g->data[u].t1)) {
        g->data[u].art_point = 1;
        printf("%d - art point\n", u);
    }
}

void bridges(graph *g) {
    int i, j;
    for (i = 1; i <= N; ++i) {
        if (g->data[i].art_point == 1) {
            for (j = 1; j <= adj_list[i][0]; ++j) {
                if (g->data[adj_list[i][j]].low > g->data[i].t1)
                    printf("%d %d - bridge\n", i, adj_list[i][j]);
            }
        }
        else if (adj_list[i][0] == 1 && adj_list[adj_list[i][1]][0] == 1) {
            if (connected_components[i] == 0 && connected_components[adj_list[i][1]] == 0) {
                if (g->data[adj_list[i][1]].art_point == 0)
                    printf("%d %d - bridge\n", i, adj_list[i][1]);
                connected_components[i]++;
                connected_components[adj_list[i][1]]++;
            }
        }
    }
}

void articulation_points(graph *g) {
    init_graph(g);
    tm = 0;
    int i;
    for (i = 1; i <= N; ++i) {
        if (g->data[i].status == 0)
            dfs(g, i, i);
    }
}

void read_data(FILE *input) {
    fscanf(input, "%d", &N);
    init_adj_list();
    int u, v;
    while (fscanf(input, "%d %d", &u, &v) != EOF) {
       adj_list[u][++adj_list[u][0]] = v;
       adj_list[v][++adj_list[v][0]] = u;
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    graph G;
    read_data(input);
    articulation_points(&G);
    bridges(&G);
    printf("test\n");
    return 0;
}