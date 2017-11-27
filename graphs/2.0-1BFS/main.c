#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DEQ_MAXSIZE 200020
#define MAXSIZE 100010

int deq[DEQ_MAXSIZE];

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

//adjacency list type and operations
typedef struct node {
    int vert, weight;
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

void list_insert(adj_list *l, int u, int v, int d) {
    node_t **head = &l->data[u];
    node_t *last = *head;
    node_t *new_node = malloc(sizeof(node_t));

    new_node->vert = v;
    new_node->weight = d;
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
    int dist, parent;
} vertex;

typedef struct {
    vertex data[MAXSIZE];
} graph;

void init_graph(graph *g) {
    int i;
    for (i = 1; i <= N; ++i) {
        g->data[i].parent = 0;
        g->data[i].dist = INT_MAX;
    }
}

void zero_one_BFS(graph *g, adj_list *l, int s) {
    init_graph(g);
    g->data[s].dist = 0;
    deque dq;
    init_deque(&dq);
    push_back(&dq, s);
    while (!empty(&dq)) {
        int u = pop_front(&dq);
        node_t *v = l->data[u];
        while (v != NULL) {
            if (g->data[v->vert].dist > g->data[u].dist + v->weight) {
                g->data[v->vert].dist = g->data[u].dist + v->weight;
                g->data[v->vert].parent = u;
                if (v->weight == 0)
                    push_front(&dq, v->vert);
                else
                    push_back(&dq, v->vert);
            }
            v = v->next;
        }
    }
}

void path(graph *g, FILE *output) {
    if (g->data[1].dist == INT_MAX) {
        fprintf(output, "%d\n", -1);
        return;
    }
    fprintf(output, "%d\n", g->data[1].dist);
}

void read_data(FILE *input, adj_list *l) {
    int i, u, v, d;
    fscanf(input, "%d %d", &N, &M);
    init_adj_list(l);
    for (i = 1; i <= M; ++i) {
        fscanf(input, "%d %d %d", &u, &v, &d);
        list_insert(l, u, v, d);
        list_insert(l, v, u, d);
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    adj_list adl;
    graph g;
    read_data(input, &adl);
    zero_one_BFS(&g, &adl, N);
    path(&g, output);

    free_list(&adl);

    fclose(input);
    fclose(output);

    return 0;
}