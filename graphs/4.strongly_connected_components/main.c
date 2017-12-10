#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100100

int vertices[MAXSIZE] = {0};

int N, tm, inverted_bfs_flag = 0;

//adjacency list type and operations
typedef struct node {
    int vrtx;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
} adj_list_data;

typedef struct {
    adj_list_data *array;
} adj_list;

void init_adj_list(adj_list *a_list) {
    a_list->array = malloc(N * sizeof(adj_list_data));
    int i;
    for (i = 1; i <= N; ++i)
        a_list->array[i].head = NULL;
}

void adj_list_insert(adj_list *a_list, int source, int destination) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->vrtx = destination;
    new_node->next = a_list->array[source].head;
    a_list->array[source].head = new_node;
}

void free_list(adj_list *l) {
    int i;
    for (i = 1; i <= N; ++i) {
        node_t *tmp;
        node_t *v = l->array[i].head;
        while (v != NULL) {
            tmp = v;
            v = v->next;
            free(tmp);
        }
    }
}

//graph type and operations
typedef struct {
    int status, parent, root, t1, t2;
} vertex;

typedef struct {
    vertex *data;
} graph;

void init_graph(graph *g) {
    g->data = malloc(N * sizeof(vertex));
    int i;
    for (i = 1; i <= N; ++i) {
        g->data[i].status = 0;
        g->data[i].parent = 0;
        g->data[i].root = 0;
    }
    tm = 0;
}

void dfs(graph *g, adj_list *l, int u, int r) {
    g->data[u].status = 1;
    tm++;
    g->data[u].t1 = tm;
    g->data[u].root = r;
    node_t *v = l->array[u].head;
    while (v != NULL) {
        if (g->data[v->vrtx].status == 0) {
            g->data[v->vrtx].parent = u;
            dfs(g, l, v->vrtx, r);
        }
        v = v->next;
    }
    tm++;
    g->data[u].t2 = tm;
    if (inverted_bfs_flag != 1) {
        vertices[0]++;
        vertices[vertices[0]] = u;
    }
    g->data[u].status = 2;
}

void dfs_forest_inverted(graph *g, adj_list *l) {
    init_graph(g);
    int i;
    for (i = 1; i <= N; ++i) {
        if (g->data[i].status == 0)
            dfs(g, l, i, i);
    }
    inverted_bfs_flag = 1;
}

int dfs_forest_original(graph *g, adj_list *l) {
    init_graph(g);
    int i, k = 0;
    for (i = vertices[0]; i >= 1; --i) {
        if (g->data[vertices[i]].status == 0) {
            dfs(g, l, vertices[i], vertices[i]);
            k++;
        }
    }
    return k;
}

void read_data(FILE *input, adj_list *l1, adj_list *l2) {
    int i, j, k, v;
    fscanf(input, "%d", &N);
    init_adj_list(l1);
    init_adj_list(l2);
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d", &k);
        for (j = 1; j <= k; ++j) {
            fscanf(input, "%d", &v);
            adj_list_insert(l1, i, v);
            adj_list_insert(l2, v, i);
        }
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    adj_list *original = malloc(sizeof(adj_list));
    adj_list *inverted = malloc(sizeof(adj_list));
    graph *g_inv = malloc(sizeof(graph));
    graph *g_orig = malloc(sizeof(graph));

    read_data(input, original, inverted);
//    printf("hello\n");
    dfs_forest_inverted(g_inv, inverted);
//
    fprintf(output, "%d\n", dfs_forest_original(g_orig, original));

//    free_list(&original);
//    free_list(&inverted);
//    free(g_inv);
//    free(g_orig);

    fclose(input);
    fclose(output);
    return 0;
}