#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX 1024

struct stack {
    char* elements;
    int top;
};

void push(struct stack* s, char c) {
    s->elements[++s->top] = c;
}

void pop(struct stack* s) {
    if (s->top >= 0) {
        s->top--;
    }
}

char top(struct stack* s) {
    return (s->top >= 0) ? s->elements[s->top] : '_';
}

bool isEmpty(struct stack* s) {
    return s->top == -1;
}


bool isValid(char* s) {

    char elements[MAX]; // no need to free, ha!
    struct stack stk;
    stk.elements = elements;
    stk.top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        switch(s[i]) {
        case '(':
        case '[':
        case '{':
            push(&stk, s[i]);
            break;
        case ')':
            if (top(&stk) == '(') {
                pop(&stk);
            } else {
                push(&stk, s[i]);
            }
            break;
        case ']':
            if (top(&stk) == '[') {
                pop(&stk);
            } else {
                push(&stk, s[i]);
            }
            break;
        case '}':
            if (top(&stk) == '{') {
                pop(&stk);
            } else {
                push(&stk, s[i]);
            }
            break;
        default:
            break;
        }
    }

    return isEmpty(&stk);
}





