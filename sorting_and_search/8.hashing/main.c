#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

char hash_table[10000][20];

int main() {

    system("chcp 1251");
//    SetConsoleOutputCP(CP_UTF8);
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");


    char c, word[15];
    while (1) {
        fscanf(input, "%c", &c);
        if (c == '?' || c == '-' || c == '+') {
            fscanf(input, "%s", word);
            printf("%s\n", word);
        }
        if (c == 'E')
            break;
    }

//    char c, w;
//    char word[15];
//    while (1) {
//        fscanf(input, "%c", &c);
//        if (c == '?' || c == '-' || c == '+') {
//            int i = 0;
//            while (1) {
//                fscanf(input, "%c", &w);
//                if (w == '\n')
//                    break;
//                word[i] = w;
//                ++i;
//            }
//            printf("%s\n", word);
//            memset(word, 0, sizeof(word));
//        }
//        if (c == 'E')
//            break;
//    }

    fclose(input);
    fclose(output);
    return 0;
}