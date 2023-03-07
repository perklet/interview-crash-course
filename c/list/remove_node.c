/**
 * Beauty of Programming 3.4
 * remove one node from a list without head
 */
#include <stdio.h>
#include <stdlib.h>

struct list_node {
    int val;
    struct list_node* next;
};

struct list_node* create_node(int val) {
    struct list_node* node = malloc(sizeof(struct list_node));
    node->val = val;
    node->next = NULL;
    return node;
}

void remove_node(struct list_node* current) {
    struct list_node* next = current->next;
    *current = *(current->next);
    free(next);
}

void print_list(struct list_node* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    puts("");
}

int main() {

    struct list_node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    print_list(head);

    remove_node(head);

    print_list(head);

    return 0;
}
