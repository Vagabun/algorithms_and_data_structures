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

//compute polynomial hash function
long long hash(const char* str) {
    long long hash = 0;
//    while (c = *str++) {
//        printf("%lli ", c);
//    }
    int j;
    for (j = 0; str[j] != '\0'; ++j)
        hash += (str[j] - 'à' + 1) * p_pow[j];
    return hash % HASH_SIZE;
}

//think about bool array with filled/empty/delete info
void make_hash_table() {
    int i;
    for (i = 0; i < HASH_SIZE; ++i)
        strcpy(hash_table[i], "EMPTY");
}

//search using linear probing
long long search(const char* str) {
    long long i = hash(str), j = 1;
    while (1) {
        if (strcmp(hash_table[i], "EMPTY") == 0)
            return -1;
        if (strcmp(hash_table[i], str) == 0)
            return i;
        i = (i + j) % HASH_SIZE;
        ++j;
    }
}

//add value to hash table
void add(const char* str) {
    long long i = hash(str), j = 1;
    while (1) {
        if (strcmp(hash_table[i], "EMPTY") == 0) {
            strcpy(hash_table[i], str);
            return;
        }
        if (strcmp(hash_table[i], str) == 0)
            return;
        i = (i + j) % HASH_SIZE;
        ++j;
    }
}

//delete value from hash table
void delete(const char* str) {
    long long i = search(str);
    if (i == -1)
        return;
    strcpy(hash_table[i], "EMPTY");
}

int main() {

    system("chcp 1251");
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    compute_pow();
    make_hash_table();

    char c, word[15];
    while (1) {
        fscanf(input, "%c", &c);
        if (c == '+') {
            fscanf(input, "%s", word);
            add(word);
        } else if (c == '-') {
            fscanf(input, "%s", word);
            delete(word);
        } else if (c == '?') {
            fscanf(input, "%s", word);
            long long s = search(word);
            if (s == -1)
                fprintf(output, "-%s\n", word);
            else
                fprintf(output, "+%s\n", hash_table[s]);
        }
        if (c == 'E')
            break;
    }

//    if (strcmp(hash_table[10036], "EMPTY") == 0) printf("halooo");

//    if (hash_table[20] == '') printf("blablabla");
//    long long a = hash(hash_table[3]);
//    printf("%lli", a);

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