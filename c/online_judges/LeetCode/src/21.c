/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* a, struct ListNode* b) {
    struct ListNode* result = NULL;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->val < b->val) {
        result = a;
        a->next = mergeTwoLists(a->next, b);
    } else {
        result = b;
        b->next = mergeTwoLists(a, b->next);
    }

    return result;
}
