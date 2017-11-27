#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DEQ_MAXSIZE 200020
#define MAXSIZE 100010
#define ZERO 1
#define ONE 2

int deq[DEQ_MAXSIZE];
int edges[MAXSIZE][MAXSIZE];

int N, M;

//deque type and operations
//typedef struct {
//    int *data;
//    int head, tail;
//} deque;
//
//void init_deque(deque *inst) {
//    inst->data = deq;
//    inst->head = (DEQ_MAXSIZE / 2) - 1;
//    inst->tail = (DEQ_MAXSIZE / 2) - 1;
//}
//
//int empty(deque *inst) {
//    return inst->head == inst->tail;
//}
//
//void push_back(deque *inst, int data) {
//    inst->data[inst->tail++] = data;
//}
//
//int pop_back(deque *inst) {
//    if (empty(inst)) {
//        return fprintf(stderr, "underflow\n");
//    }
//    return inst->data[--inst->tail];
//}
//
//void push_front(deque *inst, int data) {
//    inst->data[--inst->head] = data;
//}
//
//int pop_front(deque *inst) {
//    if (empty(inst)) {
//        return fprintf(stderr, "underflow\n");
//    }
//    return inst->data[inst->head++];
//}
//
////graph type and operations
//typedef struct {
//    int dist, parent;
//} vertex;
//
//typedef struct {
//    vertex data[MAXSIZE];
//} graph;
//
//void init_graph(graph *g) {
//    int i;
//    for (i = 1; i <= N; ++i) {
//        g->data[i].parent = 0;
//        g->data[i].dist = INT_MAX;
//    }
//}
//
//void zero_one_BFS(graph *g, int s) {
//    init_graph(g);
//    g->data[s].dist = 0;
//    deque dq;
//    init_deque(&dq);
//    push_back(&dq, s);
//    while (!empty(&dq)) {
//        int u = pop_front(&dq);
//        int k = edges[u][0];
//        int i;
//        for (i = 1; i <= k; ++i) {
//            if (edges[u][i] == ZERO || edges[u][i] == ONE) {
//                if (g->data[i].dist > g->data[u].dist + (edges[u][i] - 1)) {
//                    g->data[i].dist = g->data[u].dist + (edges[u][i] - 1);
//                    g->data[i].parent = u;
//                    if (edges[u][i] == ZERO)
//                        push_front(&dq, i);
//                    else
//                        push_back(&dq, i);
//                }
//            }
//        }
//    }
//}
//
//void read_data(FILE *input) {
//    int i, u, v, d;
//    fscanf(input, "%d %d", &N, &M);
//    for (i = 1; i <= M; ++i) {
//        fscanf(input, "%d %d %d", &u, &v, &d);
//        if (v > edges[u][0])
//            edges[u][0] = v;
//        if (u > edges[v][0])
//            edges[v][0] = u;
//        edges[u][v] = d + 1;
//        edges[v][u] = d + 1;
//    }
//}
//
//void path(graph *g, FILE *output) {
//    if (g->data[1].dist == INT_MAX) {
//        fprintf(output, "%d\n", -1);
//        return;
//    }
//    fprintf(output, "%d\n", g->data[1].dist);
//}

typedef struct node {
    int vertex, weight;
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

    new_node->vertex = v;
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

int main() {

    adj_list adl;
    N = 10;
    init_adj_list(&adl);
    list_insert(&adl, 1, 2, 1);
    list_insert(&adl, 1, 3, 0);
    list_insert(&adl, 1, 4, 1);
//    list_insert(&head, &adl, 1, 2, 1);
//    list_insert(&head, &adl, 1, 3, 0);

//    FILE *input = fopen("input.txt", "r");
//    FILE *output = fopen("output.txt", "w");
//
//    read_data(input);
//    graph g;
//    zero_one_BFS(&g, N);
//    path(&g, output);

//    list a;
//    insert(&a, 2, 1);
//    insert(&a)

//    N = 10;
//    adj_list adl;
//    init_adj_list(&adl);

    return 0;
}