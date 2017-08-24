#include <stdio.h>

struct array{
    int a[40][40];
} arr;

struct array multiply_arr(struct array a, struct array b, int size) {
    struct array c;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
//            c.a[i][j] = a.a[i][j] * b.a[i][j] + a.a[i][j+1] * b.a[i+1][j];
            int sum = 0;
            for (int k = 0; k < size; ++k) {
                sum = sum + a.a[i][k] * b.a[k][j];
//                c.a[i][j] += a.a[i][k] * b.a[k][j];
            }
            c.a[i][j] = sum;
        }
    }
    return c;
}


struct array pow(struct array x, long long int n) {
    if (n == 1) return x;
    if (n % 2 == 0) return pow(multiply_arr(x, x, 2), n/2);
    else return multiply_arr(x, pow(x, n - 1), 2);
}

int main() {

//    long long int N;
//    int P;
//
//    int a[40][40];
    struct array a1;
    a1.a[0][0] = 1;
    a1.a[0][1] = 2;
    a1.a[1][0] = 3;
    a1.a[1][1] = 4;

//    printf("%d", a1.a[1][1]);

    struct array a2 = pow(a1, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", a2.a[i][j]);
        }
        printf("\n");
    }

//    printf("%.6f", pow(a, 20));
    return 0;
}