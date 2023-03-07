/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || k <= 0) return head;
        
        ListNode* n = head;
        int l = 0;
        while (n) {
            n = n->next;
            ++l;
        }
        
        if (k >= l) k %= l;
        if (k == 0) return head;
        
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast->next && k) {
            fast = fast->next;
            k--;
        }
        
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        fast->next = head;
        ListNode* new_head = slow->next;
        slow->next = NULL;
        return new_head;
    }
};
