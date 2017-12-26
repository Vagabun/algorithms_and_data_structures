#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100010

int N, M;

//stack data type and operations
typedef struct {
    int data[MAXSIZE];
    int top;
} stack;

int isEmpty(stack *st) {
    if (st->top == -1) return 1;
    else return 0;
}

void push(stack *st, int v) {
    ++st->top;
    st->data[st->top] = v;
}

void pop(stack *st) {
    --st->top;
}

int peek(stack *st) {
    return st->data[st->top];
}

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
    a_list->array = malloc((N + 10) * sizeof(adj_list_data));
    int i;
    for (i = 1; i <= N; ++i)
        a_list->array[i].head = NULL;
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
    free(l->array);
}

void adj_list_insert(adj_list *a_list, int source, int destination) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->vrtx = destination;
    new_node->next = a_list->array[source].head;
    a_list->array[source].head = new_node;
}

//graph type and operations
typedef struct {
    int status;
} vertex;

typedef struct {
    vertex data[MAXSIZE];
} graph;

void init_graph(graph *g) {
    int i;
    for (i = 1; i <= N; ++i)
        g->data[i].status = 0;
}

int dfs(graph *g, adj_list *a, stack *s, int u) {
    g->data[u].status = 1;
    node_t *v = a->array[u].head;
    while (v != NULL) {
        if (g->data[v->vrtx].status == 1)
            return 0;
        if (g->data[v->vrtx].status == 0) {
            if (!dfs(g, a, s, v->vrtx))
                return 0;
        }
        v = v->next;
    }
    g->data[u].status = 2;
    push(s, u);
    return 1;
}

void topsort(graph *g, adj_list *a, FILE *output) {
    init_graph(g);
    stack S;
    S.top = -1;
    int u;
    for (u = 1; u <= N; ++u) {
        if (g->data[u].status == 0) {
            if (!dfs(g, a, &S, u)) {
                fprintf(output, "-1");
                return;
            }
        }
    }
    while (!isEmpty(&S)) {
        fprintf(output, "%d ", peek(&S));
        pop(&S);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fscanf(input, "%d %d", &N, &M);

    adj_list *original = malloc(sizeof(adj_list));
    init_adj_list(original);

    int i, u, v;
    for (i = 1; i <= M; ++i) {
        fscanf(input, "%d %d", &u, &v);
        adj_list_insert(original, u, v);
    }

    graph G;
    topsort(&G, original, output);

    free_list(original);
    free(original);

    fclose(input);
    fclose(output);

    return 0;
}