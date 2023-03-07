/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    // no header, apparently
    
    struct ListNode* slow_prev = NULL;
    struct ListNode* fast = head;
    
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    
    while (fast != NULL) {
        if (slow_prev == NULL) slow_prev = head;
        else slow_prev = slow_prev->next;
        fast = fast->next;
    }
    
    if (slow_prev == NULL) {
        struct ListNode* new_head = head->next;
        free(head);
        return new_head;
    } else {
        struct ListNode* temp = slow_prev->next;
        slow_prev->next = temp->next;
        free(temp);
        return head;
    }
}
