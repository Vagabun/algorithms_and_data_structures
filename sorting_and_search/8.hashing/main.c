#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10037
#define STRING_SIZE 11

//hash size should be a prime number
char hash_table[HASH_SIZE][STRING_SIZE];
unsigned long long p_pow[STRING_SIZE];

//compute max power for polynomial hash
void compute_pow() {
    const unsigned long long p = 37;
    p_pow[0] = 1;
    int i;
    for (i = 1; i <= STRING_SIZE; ++i)
        p_pow[i] = p_pow[i-1] * p;
}

long long hash(const char* str) {
    long long hash = 0;
//    while (c = *str++) {
//        printf("%lli ", c);
//    }
    int j;
    for (j = 0; str[j] != '\0'; ++j) {
        hash += (str[j] - 'à' + 1) * p_pow[j];
//        printf("%d ", str[j] - 'à' + 1);
    }
//    printf("%lli", p_pow);
    return hash % HASH_SIZE;
}

int main() {

    system("chcp 1251");
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int i = 0;
    char c, word[15];
    while (1) {
        fscanf(input, "%c", &c);
        if (c == '?' || c == '-' || c == '+') {
            fscanf(input, "%s", word);
            strcpy(hash_table[i], word);
            ++i;
        }
        if (c == 'E')
            break;
    }

    compute_pow();
    long long a = hash(hash_table[3]);
    printf("%lli", a);

//    int j = 0;
//    while (j < i) {
//        printf("%s\n", hash_table[j]);
//        ++j;
//    }

//    hash_table[0] = 'hello';
//    char s[15];
//    fscanf(input, "%s", s);
//    strcpy(hash_table[0], s);
//    hash_table[0] = *s;

//    fscanf(input, "%s", s);
//    strcpy(hash_table[1], s);

//    hash_table[1] = *s;
//    hash_table[0] = "hey";
//    printf("%s %s", hash_table[0], hash_table[1]);

    fclose(input);
    fclose(output);
    return 0;
}