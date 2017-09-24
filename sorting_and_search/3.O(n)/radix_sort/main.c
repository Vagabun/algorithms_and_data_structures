#include <stdio.h>
#include <math.h>

long long x[3000010];
int count[10];

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

    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < 10; ++j)
            count[j] = 0;
        for (int l = 0; l < counter; ++l)
            ++count[get_digit(x[l], k)];
//        for (int m = 1; m < 10; ++m)
//            count[m]
    }



//    printf("%d", get_digit(523, 3));
//    printf("%d", k);
    return 0;
}