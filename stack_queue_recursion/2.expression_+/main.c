#include <stdio.h>
#define MAXSIZE 1010

struct operations {
    char o[MAXSIZE];
    int top;
} op;

struct numbers {
    long int n[MAXSIZE];
    int top;
} num;

void push_op(char data) {
    ++op.top;
    op.o[op.top] = data;
}

void push_num(long int data) {
    ++num.top;
    num.n[num.top] = data;
}

void pop_op() {
    --op.top;
}

void pop_num() {
    --num.top;
}

int isEmpty() {
    if (op.top == -1) return 1;
    return 0;
}

int ifNumber (char n) {
    n -= '0';
    return (n >= 0 && n <= 9);
}

int ifOperation (char op) {
    return (op == '+' || op == '-' || op == '*');
}

int priority(char data) {
    if (data == '+' || data == '-') return 1;
    if (data == '*') return 2;
}

void res(char op) {
    long int l, r;
    r = num.n[num.top];
    pop_num();
    l = num.n[num.top];
    pop_num();
    switch (op) {
        case '+': push_num(l+r); break;
        case '-': push_num(l-r); break;
        case '*': push_num(l*r); break;
    }
}

int main() {
//    initialize stacks
    op.top = -1;
    num.top = -1;

    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char s, curr_op;
    int curr_pr;

    while (fscanf(input, "%c", &s) != EOF) {
        if (s != '\n') {
            if (ifNumber(s)) {
                int full_num = s - '0';
                while ((fscanf(input, "%c", &s) != EOF) && ifNumber(s)) {
                    full_num = full_num * 10 + (s - '0');
                }
                push_num(full_num);
                if (!ifNumber(s)) ungetc(s, input);
            }
            else if (ifOperation(s)) {
                curr_op = s;
                curr_pr = priority(curr_op);
                while (!isEmpty() && ifOperation(op.o[op.top]) && priority(op.o[op.top]) >= curr_pr) {
                    res(op.o[op.top]);
                    pop_op();
                }
                push_op(curr_op);
            }
        }
    }
    while (!isEmpty()) {
        res(op.o[op.top]);
        pop_op();
    }

    fprintf(output, "%li", num.n[num.top]);

    fclose(input);
    fclose(output);

    return 0;
}