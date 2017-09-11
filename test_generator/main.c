#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    FILE *output = fopen("input.txt", "w");
    unsigned long x, i;
    srand(time(NULL));
    for (i = 0; i < 3000000; ++i) {
        x = rand();
        x <<= 15;
        x ^= rand();
        x %= 1000001;
        fprintf(output, "%li ", x);
    }

//    while (fscanf(output, "%li", &i) != EOF) {
//        if (i == 5115) printf("%li\n", i);
//    }
    fclose(output);
    return 0;
}