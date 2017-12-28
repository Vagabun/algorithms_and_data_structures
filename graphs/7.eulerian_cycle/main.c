#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100010

int N;

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

void cycle(adj_list *l, stack *st, int u) {
    node_t *v = l->array[u].head;
    while (v != NULL) {
        if (v->vrtx != 0) {
            int vrtx_v = v->vrtx;
            v->vrtx = 0;
            cycle(l, st, vrtx_v);
        }
        v = v->next;
    }
    push(st, u);
}

void euler(adj_list *l, stack *st, int u) {
    cycle(l, st, u);
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    adj_list *original = malloc(sizeof(adj_list));
    stack S;

    int i, j, k, v;
    fscanf(input, "%d", &N);
    init_adj_list(original);
    for (i = 1; i <= N; ++i) {
        fscanf(input, "%d", &k);
        for (j = 1; j <= k; ++j) {
            fscanf(input, "%d", &v);
            adj_list_insert(original, i, v);
        }
    }

    S.top = -1;
    euler(original, &S, 1);

    if (isEmpty(&S))
        fprintf(output, "-1");
    else {
        while (!isEmpty(&S)) {
            fprintf(output, "%d ", peek(&S));
            pop(&S);
        }
    }

    free_list(original);
    free(original);

    fclose(input);
    fclose(output);

    return 0;
}