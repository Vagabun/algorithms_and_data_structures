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
long long hash_f(const char* str) {
    long long hash = 0;
    int j;
    for (j = 0; str[j] != '\0'; ++j) {
        hash += abs(str[j] - '0') * p_pow[j];
//        if (str[j] - '0' > 0)
//            hash += (str[j] - 'a' + 1) * p_pow[j];
//        else
//            hash += (str[j] - 'à' + 1) * p_pow[j];
//        hash += (str[j] - 'à' + 1) * p_pow[j];
    }
    return hash % HASH_SIZE;
}

//think about bool array with filled/empty/delete info
void make_hash_table() {
    int i;
    for (i = 0; i < HASH_SIZE; ++i)
        strcpy(hash_table[i], "EMPTY");
}

//search using linear probing
long long search_f(const char* str) {
    long long i = hash_f(str); //j = 1;
    while (1) {
        if (strcmp(hash_table[i], "EMPTY") == 0)
            return -1;
        if (strcmp(hash_table[i], str) == 0)
            return i;
        i = (i + 1) % HASH_SIZE;
//        ++j;
//        ++i;
    }
}

//add value to hash table
void add_f(const char* str) {
//    if (strcmp(str, "cabaab") == 0) {
//        printf("hello");
//    }
    long long i = hash_f(str); //j = 1;
    while (1) {
        if (strcmp(hash_table[i], "EMPTY") == 0) {
//        if (strcmp(hash_table[i], "EMPTY") == 0 || strcmp(hash_table[i], "_DELETE_") == 0) {
            strcpy(hash_table[i], str);
            return;
        }
        if (strcmp(hash_table[i], str) == 0)
            return;
        i = (i + 1) % HASH_SIZE;
//        ++j;
//        ++i;
    }
}

//delete value from hash table
void delete_f(const char* str) {
    long long i = search_f(str);
    if (i == -1)
        return;
    strcpy(hash_table[i], "_DELETE_");

    //rehashing table
//    while (strcmp(hash_table[i+1], "EMPTY") != 0)
//        strcpy(hash_table[i], hash_table[i+1]);
}

int main() {

    // for correct work with russian symbols in clion //
//    system("chcp 1251");

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    compute_pow();
    make_hash_table();

    char c, word[15];
    int i = 0;
    while (1) {
        fscanf(input, "%c", &c);
        if (c == '+') {
            fscanf(input, "%s", word);
//            if (strcmp(word, "cbaaab") == 0) {
//                ++i;
//                if (i == 3)
//                    printf("hello");
//            }
            add_f(word);
        } else if (c == '-') {
            fscanf(input, "%s", word);
            delete_f(word);
        } else if (c == '?') {
            fscanf(input, "%s", word);
//            if (strcmp(word, "cbaaab") == 0)
//                printf("hello");
            long long s = search_f(word);
            if (s == -1)
                fprintf(output, "-%s\n", word);
            else
                fprintf(output, "+%s\n", hash_table[s]);
        }
        if (c == 'E')
            break;
    }


//    printf("%d", 'd' - 'a');
    fclose(input);
    fclose(output);

    return 0;

}