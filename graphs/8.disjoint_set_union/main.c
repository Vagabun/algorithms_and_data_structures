#include <stdio.h>

#define MAXSIZE 100010

int N;
int representatives[MAXSIZE], cc[MAXSIZE] = { 0 };

//DSU
void make() {
    int i;
    for (i = 1; i <= N; ++i)
        representatives[i] = i;
}

int rep(int u) {
    return representatives[u];
}

void uni(int u, int v) {
    int r_1 = rep(u);
    int r_2 = rep(v);
    int i;
    for (i = 1; i <= N; ++i) {
        if (rep(i) == r_1)
            representatives[i] = r_2;
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

    int i;
    for (i = 1; i <= N; ++i) {
        cc[representatives[i]]++;
    }

    int counter = 0;
    for (i = 1; i <= N; ++i) {
        if (cc[i] != 0)
            counter++;
    }

    fprintf(output, "%d", counter);

    fclose(input);
    fclose(output);

    return 0;
}