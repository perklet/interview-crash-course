#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        bool isPalindrome(ListNode* head) {
            if (head == NULL) return false;
            if (head->next == NULL) return true;

            int len = 0;
            while (head != NULL) {
                ++len;
                head = head->next;
            }

            stack<ListNode*> stk;
            ListNode* temp = head;

            int mid = len / 2;
            while(mid--) {
                stk.push(temp);
                temp = temp->next;
            }

            while (temp != NULL) {
                int a = stk.top()->val;
                stk.pop();
                int b = temp->val;
                temp = temp->next;
                if (a != b) {
                    return false;
                }
            }

            return true;
        }
};

int main() {
    return 0;
}
