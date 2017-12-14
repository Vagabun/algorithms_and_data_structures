#include <stdio.h>

int N;
int adj_list[1000][1000];

typedef struct {
    int data[1000];
} graph;

void init_adj_list() {
    int i;
    for (i = 1; i <= N; ++i)
        adj_list[i][0] = 0;
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