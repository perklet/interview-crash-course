/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     ListNode *next;
 *      *     ListNode(int x) : val(x), next(NULL) {}
 *       * };
 *        */
class Solution {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            if (l1 == NULL) return l2;
            if (l2 == NULL) return l1;
            int shift = 0;
            ListNode* result = new ListNode(0);
            ListNode* p = result;
            while (l1 != NULL || l2 != NULL) {
                ListNode* newNode = new ListNode(0);
                int v1 = l1 != NULL ? l1->val : 0;
                int v2 = l2 != NULL ? l2->val : 0;
                newNode->val = v1 + v2 + shift;
                if (newNode->val > 9) {
                    newNode->val -= 10;
                    shift = 1;
                } else {
                    shift = 0;
                }
                if (l1) {
                    l1 = l1->next;
                }
                if (l2) {
                    l2 = l2->next;
                }
                p->next = newNode;
                p = p->next;
            }

            if (shift == 1) {
                p->next = new ListNode(1);
            }

            return result->next;
        }
};
