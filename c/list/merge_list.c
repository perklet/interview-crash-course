#include <stdio.h>
#include <stdlib.h>

struct list_node {
    int val;
    struct list_node* next;
};

struct list_node* merge_list(struct list_node* h1, struct list_node* h2) {

    struct list_node dummy;
    dummy.next = NULL;
    struct list_node* current = &dummy;

    while (h1 != NULL && h2 != NULL) {
        if (h1->val < h2->val) {
            current->next = h1;
            h1 = h1->next;
            current = current->next;
        } else {
            current->next = h2;
            h2 = h2->next;
            current = current->next;
        }
    }

    if (h1 != NULL) {
        current->next = h1;
    }

    if (h2 != NULL) {
        current->next = h2;
    }

    return dummy.next;
}

struct list_node* make_list() {

    int n;
    scanf("%d", &n);
    struct list_node dummy;
    dummy.next = NULL;
    struct list_node* current = &dummy;
    printf("%d List elements: ", n);
    int val;
    while (n--) {
        scanf("%d", &val);
        struct list_node* node = malloc(sizeof(struct list_node));
        node->val = val;
        node->next = NULL;
        current->next = node;
        current = node;
    }
    puts("list constructed");
    fflush(stdin);

    return dummy.next;
}

void print_list(struct list_node* head) {

    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }

    puts("");
}


void free_list(struct list_node* head) {

    struct list_node* temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}


int main() {

    struct list_node* l1, *l2;

    l1 = make_list();
    l2 = make_list();

    struct list_node* merged = merge_list(l1, l2);
    
    printf("Merged list ");
    print_list(merged);

    free_list(merged);

    return 0;
}



