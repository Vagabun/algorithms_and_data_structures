#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100100

int N, tm;

//adjacency list type and operations
typedef struct node {
    int vrtx;
    struct node *next;
} node_t;

typedef struct {
    node_t *data[MAXSIZE];
} adj_list;

void init_adj_list(adj_list *l) {
    int i;
    for (i = 1; i <= N; ++i)
        l->data[i] = NULL;
}

void list_insert(adj_list *l, int u, int v) {
    node_t **head = &l->data[u];
    node_t *last = *head;
    node_t *new_node = malloc(sizeof(node_t));

    new_node->vrtx = v;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void free_list(adj_list *l) {
    int i;
    for (i = 1; i <= N; ++i) {
        node_t *tmp;
        node_t *v = l->data[i];
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
    vertex data[MAXSIZE];
} graph;

void init_graph(graph *g) {
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
    node_t *v = l->data[u];
    while (v != NULL) {
        if (g->data[v->vrtx].status == 0) {
            g->data[v->vrtx].parent = u;
            dfs(g, l, v->vrtx, r);
        }
        v = v->next;
    }
    tm++;
    g->data[u].t2 = tm;
    g->data[u].status = 2;
}

void dfs_forest(graph *g, adj_list *l) {
    init_graph(g);
    int i;
    for (i = 1; i <= N; ++i) {
        if (g->data[i].status == 0)
            dfs(g, l, i, i);
    }
}

void read_data(FILE *input, adj_list *l1, adj_list *l2) {
    int i, j, k, v;
    init_adj_list(l1);
    init_adj_list(l2);
    fscanf(input, "%d", &N);
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d", &k);
        for (j = 1; j <= k; ++j) {
            fscanf(input, "%d", &v);
            list_insert(l1, i, v);
            list_insert(l2, v, i);
        }
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    adj_list original;
    adj_list inverted;
    graph g;

    read_data(input, &original, &inverted);
    dfs_forest(&g, &inverted);

    printf("test\n");

    free_list(&original);
    free_list(&inverted);
    fclose(input);
    fclose(output);
    return 0;
}