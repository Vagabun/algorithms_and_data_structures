#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAXSIZE 1010

int adj_list[MAXSIZE][MAXSIZE];
int connected_components_flag[MAXSIZE] = { 0 };
int artic_points[MAXSIZE] = { 0 };
int bc_comp[MAXSIZE] = { 0 };
int bridges_stor[MAXSIZE][MAXSIZE];
int N, tm, artic_points_counter = 0, bridges_counter = 0, bcc_flag = 0;

//stack data type for using in search of biconnected components
typedef struct {
    int data[MAXSIZE];
    int top;
} stack;

int isEmpty(stack *s) {
    if (s->top == -1) return 1;
    else return 0;
}

void push(stack *s, int vrtx) {
    ++s->top;
    s->data[s->top] = vrtx;
}

void pop(stack *s) {
    --s->top;
}

int peek(stack *s) {
    return s->data[s->top];
}

//graph and vertex data type
typedef struct {
    int status, parent, root, art_point, t1, low;
} vertex;

typedef struct {
    vertex data[MAXSIZE];
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

void init_bridges_stor() {
    int i;
    for (i = 1; i <= N; ++i)
        bridges_stor[i][0] = 0;
}

//dfs, bridges, bcc, a points
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
        artic_points[u]++;
        artic_points_counter++;
    }
}

void dfs_bcc(graph *g, stack *s, int u, int r) {
    if (u == 1)
        bcc_flag = 1; //if we have vertex 1 in stack
    g->data[u].status = 1;
    g->data[u].root = r;
    int i;
    for (i = 1; i <= adj_list[u][0]; ++i) {
        if (g->data[adj_list[u][i]].status == 0) {
            g->data[adj_list[u][i]].parent = u;
            push(s, adj_list[u][i]);
            dfs_bcc(g, s, adj_list[u][i], r);
        }
        else if (u == r) {
            return;
        }
    }
}

void bc_components(graph *g_a_points, graph *g_bcc, stack *s) {
    if (artic_points_counter > 0) {
        s->top = -1;
        int i;
        for (i = 1; i <= N; ++i) {
            if (g_a_points->data[i].art_point) {
                push(s, i);
                dfs_bcc(g_bcc, s, i, i);
                if (bcc_flag) {
                    while (!isEmpty(s)) {
                        bc_comp[peek(s)]++;
                        pop(s);
                    }
                    return;
                }
                else
                    s->top = -1;
            }
        }
    }
    else {
        //then all graph is biconnected
        int k;
        for (k = 1; k <= N; ++k)
            bc_comp[k]++;
    }
}

void bridges(graph *g) {
    int i, j;
    init_bridges_stor();
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= adj_list[i][0]; ++j) {
            if (g->data[i].art_point == 1 || g->data[j].art_point == 1) {
                if ((g->data[adj_list[i][j]].low > g->data[i].t1) || (g->data[i].low > g->data[adj_list[i][j]].t1)) {
                    int min = MIN(i, adj_list[i][j]), max = MAX(i, adj_list[i][j]);
                    bridges_stor[min][max]++;
                    bridges_stor[min][0] = MAX(bridges_stor[min][0], max);
                    bridges_counter++;
                }
            }
        }
        if (adj_list[i][0] == 1 && adj_list[adj_list[i][1]][0] == 1) {
            if (connected_components_flag[i] == 0 && connected_components_flag[adj_list[i][1]] == 0) {
                if (g->data[adj_list[i][1]].art_point == 0) {
                    bridges_stor[i][adj_list[i][1]]++;
                    bridges_stor[i][0] = MAX(bridges_stor[i][0], adj_list[i][1]);
                    bridges_counter++;
                }
                connected_components_flag[i]++;
                connected_components_flag[adj_list[i][1]]++;
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

    graph G_a_points, G_bcc;
    stack S;
    read_data(input);
    articulation_points(&G_a_points);
    bridges(&G_a_points);
    bc_components(&G_a_points, &G_bcc, &S);

    int i;
    if (artic_points_counter != 0) {
        for (i = 1; i <= N; ++i) {
            if (artic_points[i])
                fprintf(output, "%d ", i);
        }
        fprintf(output, "\n");
    }

    if (bridges_counter != 0) {
        for (i = 1; i <=N; ++i) {
            if (bridges_stor[i][0] != 0) {
                int j;
                for (j = 1; j <= bridges_stor[i][0]; ++j) {
                    if (bridges_stor[i][j] == 0)
                        continue;
                    fprintf(output, "%d %d\n", i, j);
                }
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        if (bc_comp[i])
            fprintf(output, "%d ", i);
    }

    fclose(input);
    fclose(output);
    return 0;
}