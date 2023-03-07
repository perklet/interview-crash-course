#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct stack {
    void** vals;
    int capacity;
    int top;
};

struct stack* create_stack(int capacity) {
    struct stack* s = malloc(sizeof(struct stack));
    s->vals = malloc(sizeof(int) * capacity);
    s->capacity = capacity;
    s->top = -1;
    return s;
}

bool is_full_stack(struct stack* s) {
    return s->top >= s->capacity;
}

bool is_empty_stack(struct stack* s) {
    return s->top < 0;
}

void push_stack(struct stack* s, void* val) {
    if (!is_full_stack(s))
        s->vals[++s->top] = val;
}

void pop_stack(struct stack* s) {
    if (!is_empty_stack(s))
        --s->top;
}

void* top_stack(struct stack* s) {
    if (!is_empty_stack(s)) 
        return s->vals[s->top];
}

void free_stack(struct stack* s) {
    free(s->vals);
    free(s);
}
