LeetCode Complete
======


1. 从数组中找出两个数字使得他们的和是给定的数字

使用一个散列，存储数字和他对应的索引。然后遍历数组，如果另一半在散列当中，那么返回
这两个数的索引，程序结束；如果不在，把当前数字加入到散列中。

``` C++
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash;
    vector<int> result(2);
    for (int i = 0; i != nums.size(); ++i) {
        int reminder = target - nums[i];
        if (hash.find(reminder) !=
                hash.end()) {
            result[0] = hash[reminder] + 1;
            result[1] = i + 1;
            return result;
        }
        hash[nums[i]] = i;
    }
    return result;
}
```

2. 给两个列表，数字在其中按低位到高位存储，求他们的和

直接迭代遍历数组，考察细节操作。注意 dummy head 的使用。

``` C
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy, *p = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int v1 = l1 ? l1->val: 0;
        int v2 = l2 ? l2->val: 0;
        int v = v1 + v2 + carry;
        p->next = malloc(sizeof(struct ListNode));
        p = p->next;
        p->val = v % 10;
        p->next = NULL;
        carry = v / 10;
        
        l1 = l1 ? l1->next: NULL;
        l2 = l2 ? l2->next: NULL;
    }
    return dummy.next;
}
```

3. 最长不重复子串

使用动态规划


