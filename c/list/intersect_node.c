/**
 * Beauty of Programming 3.6
 * Determine if two linked list intersect each other, if then, find the first
 * common node
 */


struct list_node {
    int val;
    struct list_node* next;
};

int list_len(struct list_node* head) {
    int c = 0;

    while (head != NULL) {
        head = head->next;
        ++c;
    }

    return c;
}

struct list_node* common_node(struct list_node* l1, struct list_node* l2) {
    int len1 = list_len(l1);
    int len2 = list_len(l2);

    if (len1 > len2) {

