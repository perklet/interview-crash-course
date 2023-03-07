#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

void split(struct ListNode* source, struct ListNode** frontptr, struct ListNode** backptr);
struct ListNode* sortedMerge(struct ListNode* a, struct ListNode* b);
struct ListNode* mergeSort(struct ListNode* head);

// fast and slow pointers strategy
void split(struct ListNode* source, struct ListNode** frontptr, struct ListNode** backptr) {
    struct ListNode* fast;
    struct ListNode* slow;

    if (source == NULL || source->next == NULL) {
        *frontptr = source;
        *backptr = source;
    } else {
        slow = source;
        fast = source->next;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontptr = source;
        *backptr = slow->next;
        slow->next = NULL;
    }
}

struct ListNode* sortedMerge(struct ListNode* a, struct ListNode* b) {
    struct ListNode* result = NULL;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->val < b->val) {
        result = a;
        a->next = sortedMerge(a->next, b);
    } else {
        result = b;
        b->next = sortedMerge(a, b->next);
    }

    return result;
}

struct ListNode* mergeSort(struct ListNode* head) {
    struct ListNode* front;
    struct ListNode* back;

    if (head == NULL || head->next == NULL)
        return head;

    split(head, &front, &back);

    front = mergeSort(front);
    back = mergeSort(back);

    head = sortedMerge(front, back);

    return head;
}

void append(struct ListNode* head, int val) {
    struct ListNode* newListNode = malloc(sizeof(struct ListNode));
    newListNode->val = val;
    newListNode->next = NULL;
    head->next = newListNode;
}



int main() {

    struct ListNode* head = malloc(sizeof(struct ListNode));
    append(head, 90);
    append(head->next, 0);
    append(head->next)



    return 0;
}
