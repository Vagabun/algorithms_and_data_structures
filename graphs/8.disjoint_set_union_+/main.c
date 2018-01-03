#include <stdio.h>

#define MAXSIZE 100010

int N;
int parent[MAXSIZE], descendants[MAXSIZE];

//DSU
void make() {
    int i;
    for (i = 1; i <= N; ++i) {
        parent[i] = 0;
        descendants[i] = 1;
    }
}

int rep(int u) {
    while (parent[u] != 0)
        u = parent[u];
    return u;
}

void uni(int u, int v) {
    int r_1 = rep(u);
    int r_2 = rep(v);
    if (r_1 == r_2)
        return;
    if (descendants[r_1] > descendants[r_2]) {
        parent[r_2] = r_1;
        descendants[r_1] += descendants[r_2];
    }
    else {
        parent[r_1] = r_2;
        descendants[r_2] += descendants[r_1];
    }
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fscanf(input, "%d", &N);
    make();
    int u, v;
    while (fscanf(input, "%d %d", &u, &v) != EOF)
        uni(u, v);

    int i, connected_c = 0;
    for (i = 1; i <= N; ++i) {
        if (parent[i] == 0)
            connected_c++;
    }

    fprintf(output, "%d", connected_c);

    fclose(input);
    fclose(output);

    return 0;
}