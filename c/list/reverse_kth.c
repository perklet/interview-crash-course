#include <stdio.h>
#include <stdlib.h>

struct list_node {
    int val;
    struct list_node* next;
}

void print_list(struct list_node* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    puts("");
}

void create_node(int val) {
    struct list_node* node = malloc(sizeof(struct list_node));
    node->val = val;
    node->next = NULL;
    return node;
}

struct list_node* reverse_kth(struct list_node* head) {
    struct list_node* fast = head;

    for (int i = 0; i < k

