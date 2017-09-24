#include <stdio.h>
#include <math.h>

long long x[3000010];
long long y[3000010];
long long count[10];

int get_digit(long long n, int i) {
    return (int)(n/pow(10, i-1)) % 10;
}

int main() {

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    long long n, counter = 0, max = -1;
    while (fscanf(input, "%lli", &n) != EOF) {
        if (n > max)
            max = n;
        x[counter] = n;
        ++counter;
    }

    

    int k = 0;
    while (max > 0) {
        ++k;
        max /= 10;
    }

    int i;
    long long j, l, m;
    for (i = 1; i <= k; ++i) {
        for (j = 0; j < 10; ++j)
            count[j] = 0;
        for (l = 0; l < counter; ++l)
            ++count[get_digit(x[l], i)];
        long long sum = 0;
        for (m = 0; m < 10; ++m) {
            long long tmp = count[m];
            count[m] = sum;
            sum += tmp;
        }
        for (int i1 = 0; i1 < counter; ++i1) {
            int d = get_digit(x[i1], i);
            y[count[d]] = x[i1];
            ++count[d];
        }
        for (int k1 = 0; k1 < counter; ++k1)
            x[k1] = y[k1];
    }

    for (int l1 = 0; l1 < counter; ++l1)
        fprintf(output, "%lli ", x[l1]);



//    printf("%d", get_digit(523, 3));
//    printf("%d", k);
    return 0;
}