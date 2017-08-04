#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10010

struct stack {
    char s[MAXSIZE];
    int top;
} st;

//int isFull() {
//    if (st.top >= MAXSIZE - 1) return 1;
//    else return 0;
//}

int isEmpty() {
    if (st.top == -1) return 1;
    else return 0;
}

void push(char data) {
    ++st.top;
    st.s[st.top] = data;
}

void pop() {
    --st.top;
}

char peek() {
    return st.s[st.top];
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    st.top = -1;

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '(' || c == '{' || c == '[') push(c);
        else {
            if ((c == ')' && !isEmpty() && peek() == '(') || (c == '}' && !isEmpty() && peek() == '{') || (c == ']' && !isEmpty() && peek() == '[')) pop();
            else {
                fprintf(output, "no");
                exit(0);
            }
        }
    }

    if (isEmpty()) fprintf(output, "yes");
    else fprintf(output, "no");

    return 0;
}