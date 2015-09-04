LeetCode Complete
======

0. 说明
------

* 原则上使用 C 做，如果需要用到 Hash, Stack, Queue，或者返回值特别复杂，或者需要大量拼接字符串时，使用 C++。
* 请在了解基本数据结构的基础上阅读，大概是大三的水平吧。


1. 从数组中找出两个数字使得他们的和是给定的数字
------

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
------

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
------

使用动态规划，在一个 Hash 中存储已经出现的字符的上一次出现的索引值，如果索引值存在，则把当前最长子串的左边界更新为改索引值。

注意，当字符有限的时候，比如限定为 ASCII 字符，可以使用一个数组代替 Hash。

``` C

int lengthOfLongestSubstring(char* s) {
    int indices[256];
    for (int i = 0; i < 256; i++) //init the array, memset can only be used for char
        indices[i] = -1;
    int left = 0;
    int longest = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        left = max(left, indices[s[i]] + 1);
        indices[s[i]] = i;
        longest = max(longest, i - left + 1);
    }
    return longest;
}
```

4. 找到两个排序数组的中值
------

这个题好难啊，先放放

5. 最长回文子串
------

解法1：以某个元素为中心，向两边展开，注意处理奇数和偶数两种情况
解法2：Manacher 算法，参见http://taop.marchtea.com/01.05.html

````C
char* longestPalindrome(char* s) {
    if (!s) return NULL;

    int p_length = 0; // length of the longest palindromic string
    int p_start = -1; // start of the lonest palidromic string
    
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        
        // length is odd
        for (int j = 0; (i - j >= 0) && (i + j < len); j++) { 
            if (s[i - j] != s[i + j])
                break;
            if (j * 2 + 1 > p_length) {
                p_length = j * 2 + 1;
                p_start = i - j;
            }
        }
        
        // length is even
        for (int j = 0; (i - j >= 0) && (i + j + 1 < len); j++) {
            if (s[i - j] != s[i + j + 1])
                break;
            if (j * 2 + 2 > p_length) {
                p_length = j * 2 + 2;
                p_start = i - j;
            }
        }
    }
    
    char* result = malloc(sizeof(char) * p_length + 1);
    strncpy(result, s + p_start, p_length);
    result[p_length] = 0;
    
    return result;
}
```

6. ZigZag 字符串，把字符串掰弯，然后再按行输出
------

考察数学，找出规律，按行货的重构后的字符串

``` C
char* convert(char* s, int numRows) {
    int len = strlen(s);
    if (!s || numRows <= 1 || len < numRows) return s;
    
    char* zigzag = malloc(sizeof(char) * len + 1);
    int cur = 0;
    
    for (int i = 0; i < numRows; i++) {
        for (int j = i; j < len; j += 2 * (numRows - 1)) {
            zigzag[cur++] = s[j];
            if (i != 0 && i != numRows - 1) {
                int t = j + 2 * (numRows - 1) - 2 * i;
                if (t < len)
                    zigzag[cur++] = s[t];
            }
        }
    }
    zigzag[cur] = '\0';
    return zigzag;
}
```

7. 翻转数字，溢出返回0
------

注意溢出

```C
int reverse(int x) {
    if (x == INT_MIN) return 0;
    if (x < 0) return -reverse(-x);
    
    long result = 0;
    while (x) {
        result = result * 10 + x % 10;
        x /= 10;
    }
    return result > INT_MAX ? 0 : result;
    
}
```

8. 实现 atoi
------

注意各种特殊情况：

1. 首先过滤空格
2. 判定符号，符号只能出现一次
3  是否溢出，溢出返回 INT_MAX 或者 INT_MIN

```
int myAtoi(char* str) {
    if (!str) return 0;
    int sign = 1;
    int result = 0;
    
    // discarding spaces
    while (isspace(*str))
        str++; 
    
    // determining sign
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        if (*str == '+') sign = 1;
        str++;
    }
    
    // constructing integer
    while (isdigit(*str)) {
        // handling overflow
        if (result > INT_MAX / 10 || result == INT_MAX / 10 && *str - '0' > INT_MAX % 10)
            return sign > 0 ? INT_MAX : INT_MIN;
        result = *str - '0' + result * 10;
        str++;
    }
    
    return result * sign;
}`c
```

9. 是否是回文数字
------

限定不能用额外空间，所以直接把 x 取余得到的数字作为一个反向作为一个新的数字

```c
bool isPalindrome(int x) {
    // tricky here, for x == k * 10^j
    if (x < 0 || x && (x % 10 == 0)) return false;
    int y = 0;
    while (x > y) {
        y = y * 10 + x % 10;
        x /= 10;
    }

    return x == y || x == y / 10;
}
```
10. 正则表达式
------

实现正则表达式，只需要实现`.`代表任意字符，`*`代表任意重复。

```c
bool isMatch(char* s, char* p) {
    for (char c = *p; c != 0;s++, c = *p) {
        // if next char in pattern is not *
        if (*(p+1) != '*')
            p++;
        // if we got an *, check if we can skip `.*` or `x*`
        else if (isMatch(s, p + 2))
            return true;

        // s ends or p and s differs
        if (*s == 0 || c != '.' && c != *s)
            return false;
    }
    return *s == 0;
}
```
11. Contaier with most water
------

This problem seems to have been chanaged since last time I visited leetcode.

12. 十进制转换为罗马数字
------

直接按每位把罗马数字转换出来在拼接就好了，使用 C 的话，拼接字符串很麻烦。

```c++
string intToRoman(int num) {
    // note, the leading empty string is the trick here
    string thousands[] = {"", "M", "MM", "MMM"};
    string handreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return thousands[num/1000] + handreds[num%1000 / 100] + tens[num % 100 / 10] + ones[num % 10];

}
```

13. 罗马数字转为十进制
------

主要是当前一个数字小于后一个数字的时候，需要添加的是后一个谁和钱一个数字的差


```
// acts like a dict or map
int getVal(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
}

int romanToInt(char* s) {
    int result = 0;
    for (int i = 0; s[i] != 0; ) {
        if (getVal(s[i]) < getVal(s[i+1]))
            result += getVal(s[i+1]) - getVal(s[i]), i += 2;
        else
            result += getVal(s[i]), i++;
    }
    return result;
}
```

14. 最长公共前缀
------

横向遍历，从头到尾，如果，不一致，返回当前子串即可。如果约定不能更改当前字符串的化，最好用
C++做，不然操作字符串太复杂了，没必要出错。

```c
char* longestCommonPrefix(char** strs, int strsSize) {
    if (!strs || !strs[0]) return "";
    if (strsSize == 1) return strs[0];
    int len = strlen(strs[0]);

    for (int i = 0; i < len; i++) {
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != strs[0][i]) {
                strs[0][i] = '\0';
                return strs[0];
            }
        }
    }
    return strs[0];
}
```

15. 从数组中找出三个数使得他们的和是0
------

按照 LeetCode 的要求的话，使用 C 做，返回值太复杂了，所以用 C++ 做了。
首先，把数组排序，然后使用类似 two sum 的方法做就好了

```C++
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i-1])
            continue;
        int k = nums.size() - 1;
        int j = i + 1;
        while (j < k) {
            if (nums[i] + nums[j] + nums[k] > 0)
                k--;
            else if (nums[i] + nums[j] + nums[k] < 0)
                j++;
            else {
                result.push_back({nums[i], nums[j], nums[k]});
                // skipping duplicates
                while (j < k && nums[k] == nums[k - 1])
                    k--;
                while (j < k && nums[j] == nums[j + 1])
                    j++;
                k--;
                j++;
            }
        }
    }
    return result;
}
```

16. 在数组中找到三个数字使得他们得和尽可能的接近给定数字，假设结果唯一
------

和上一题解法类似，在 http://stackoverflow.com/q/2070359 有详尽解释

```C
int cmp(int* a, int* b) {
    return *a - *b;
}

int threeSumClosest(int* nums, int numsSize, int target) {
    if (numsSize <= 3) 
        return nums[0] + nums[1] + nums[2];
    qsort(nums, numsSize, sizeof(int), cmp);

    int result = nums[0] + nums[1] +nums[2];
    for (int i = 0; i < numsSize; i++) {
        int j = i + 1;
        int k = numsSize - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == target)
                return target;
            if (abs(target - sum) < abs(target - result))
                result = sum;
            if (sum > target)
                k--;
            else
                j++;
        }
    }
    return result;
}
```

17. 生成电话键盘按键数字对应的所有可能的字符串，不限制返回结果的顺序
------

![键盘](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)
遍历数字，设当前结果为{a, b, c}，下一个数字是`3`，找出对应的字母{d, e, f}，则新的结果是

    { a + {def}, b + {def}, c + {def}}

然后把新获得的数组作为下一轮的初始数组。最开始时，使用空数组开始。

```C++
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return vector<string> {};
    string mapping[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> combinations(1, "");

    for (int i = 0; i < digits.size(); i++) {
        int digit = digits[i] - '0';
        if
            (mapping[digit].empty())
                continue;
        vector<string>
            temp;
        for (auto& c : mapping[digit])
            for (auto& combination : combinations)
                temp.push_back(combination + c);
        swap(combinations, temp);
    }
    return combinations;
} 
```

18. 太难了，先跳过
------

19. 删除链表中倒数第 k 的节点
------

双指针经典题目，一个快指针先走 k 步，另一个慢指针再出发，注意链表长度小于 k 时。
注意：LeetCode 给定的 n 都是有效地，但要求返回头指针，如果头指针被删除需要额外注意，因此采用 dummy head

```C
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy, *fast, *slow;
    dummy.next = fast = head;
    slow = &dummy;

    while (n--)
        fast = fast->next;
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    struct ListNode* next = slow->next;
    slow->next = next->next;
    free(next); // remeber to free memory
    return dummy.next;
}
```

20. 判定给定的字符串是否是合法的括号序列，可能包括大中小三类
------

使用栈的基础题

```C
char opposite(char c) {
    switch (c) {
        case ')' : return '(';
        case ']' : return '[';
        case '}' : return '{';
    }
}

bool isValid(string s) {
    stack<char> stk;
    for (auto& c : s) {
        if (c == '(' || c == '[' || c == '{')
            stk.push(c);
        else if (!stk.empty() && stk.top() == opposite(c))
            stk.pop();
        else
            return false;
    }

    return stk.empty();
}
```

21. 合并两个已经排序的链表
------

考察链表的基本操作，很简单

```C
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    struct ListNode dummy;
    dummy.next == NULL;
    struct ListNode* p = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            p->next = l1;
            l1 = l1->next;
        } else {
            p->next = l2;
            l2 = l2->next;
        }
        
        p = p->next;
    }
    
    if (l1)
        p->next = l1;
    
    if (l2)
        p->next = l2;
    
    return dummy.next;
}
```

22. 给定数字n，生成所有合法的 n 个括号组成的序列
------

解释暂时说不清粗

```C++
vector<string> result;
vector<string> generateParenthesis(int n) {
    gen("", n, n);
    return result;
}

void gen(string s, int left, int right) {
    if (left == 0 && right == 0) {
        result.push_back(s);
        return;
    }
    if (left != 0)
        gen(s + '(', left - 1, right);
    if (left < right)
        gen(s + ')', left, right - 1);
}
```

23. 合并 k 个已经排序的列表
------

把列表看做一个队列，每次拿出两个列表，合并他们后放回到列表中，每次遍历列表的一半，这样每次遍历完一遍，
列表的长度都会减半，直到列表的长度为1， 合并函数使用21题中的合并两个列表的函数

```C
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    // see above
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (!lists || listsSize < 1)
        return NULL;
    if (listsSize == 1)
        return lists[0];
    while (listsSize > 1) {
        // listsize is halfed
        for (int i = 0; i < listsSize / 2; i++)
            // merge i and last i list
            lists[i] = mergeTwoLists(lists[i], lists[listsSize-1-i]);
        listsSize = (listsSize + 1) / 2;
        
    }
    return lists[0];
}
```

23. 给定一个链表，交换两个相邻几点的值
------

最简单的做法显然是直接把前后两个节点的值交换，但是LeetCode规定不能改变节点的值。
主要考察链表的指针操作，注意各种细节，一定要在纸上先把链表画出来。

```
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummy, *temp, *pnext, *p = &dummy;
    dummy.next = head;
    while (p->next && p->next->next) {
        temp = p->next;
        p->next = temp->next;
        temp->next = p->next->next;
        p->next->next = temp;
        p = temp;
    }
    return dummy.next;
}
```

25. 给定一个链表，把相邻的 k 个节点反转
------

和上题一样，同样禁止改变节点的值。比较简单地解法是浪费一点空间，使用
Stack，实现逆转 k 个节点，注意如果 k 较大的话，这种方法是不合适的。

```
ListNode* reverseKGroup(ListNode* head, int k) {
    stack<ListNode*> stk;
    ListNode dummy(-1), *p = &dummy, *pp;
    dummy.next = head;
    while (1) {
        pp = p;
        for (int i = 0; i < k; i++) {
            if (pp->next) {
                stk.push(pp->next);
                pp = pp->next;
            } else {
                break;
            }
        }

        if (stk.size() < k)
            return dummy.next;

        pp = stk.top()->next;
        while (!stk.empty()) {
            p->next
                = stk.top();
            stk.pop();
            p = p->next;
        }

        p->next = pp;
    }
}
```

26. 从已排序数组中删除重复元素，并返回新数组的长度
------

in-place的删除重复元素，使用两个指针，一个遍历，一个指向当前的结尾。

PS：这个基础题竟然做了半个小时才做对，⊙﹏⊙b汗，要加强基础啊！

```C
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize <= 1) return numsSize;
    int len = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[len])
            nums[++len] = nums[i];
    }
    return len + 1;
}
```

27. 删除元素
------

和上一题类似，注意细节

```
int removeElement(int* nums, int numsSize, int val) {
    if (!nums || numsSize == 0) return 0;
    int len = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != val)
            nums[len++] = nums[i];
    }
    return len;
}
```

28. 实现 strstr 函数，即查找子串
------

使用暴力算法，时间复杂度O(n)。也可以用 kmp 算法。

```C
/*
 * Brute Force
 */
int strStr(char* haystack, char* needle) {
    int h = strlen(haystack);
    int n = strlen(needle);
    if (strlen(needle) == 0) return 0;
    // note h - n + 1
    for (int i = 0; i < h - n + 1; i++) {
        for (int j = 0; j < n; j++) {
            if (needle[j] != haystack[i+j])
                break;
            if (j == n - 1)
                return i;
        }
    }
    return -1;
}
```

```
/*
 * KMP
 */

int strStr(char* haystack, char* needle) {
    if (strlen(needle) == 0) return 0;
    return kmp(needle, haystack);
}

void construct(char* pattern, int* lps) {

    int n = strlen(pattern);
    lps[0] = 0;
    int i = 1, len = 0;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
}

int kmp(char* needle, char* haystack) {

    int n = strlen(needle);
    int m = strlen(haystack);

    int* lps = malloc(sizeof(int) * n);
    construct(needle, lps);

    int i = 0, j = 0;
    while (i < m) {
        if (haystack[i] == needle[j])
            i++, j++;
        if (j == n) {
            return i - n;
            j = lps[j - 1];
        } else if (i < m && needle[j] != haystack[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    free(lps);
    return -1;
}
```

29. 给定连个整数，不使用乘法和除法计算除法。
------

[这里](https://leetcode.com/discuss/38997/detailed-explained-8ms-c-solution)有一个非常好的算法

```
int divide(int dividend, int divisor) {
    // abs(INT_MIN) == INT_MAX + 1
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) 
        return INT_MAX;
    int sign = (dividend > 0) == (divisor > 0) ? 1 : -1;
    long long n = labs(dividend);
    long long d = labs(divisor);
    
    int result = 0;
    while (n >= d) {
        long long temp = d;
        long long multi = 1;
        while (n >= (temp << 1)) {
            temp <<= 1;
            multi <<= 1;
        }
         n -= temp;
         result += multi;
    }
    
    return sign * result;
}
```

30. 没读懂题目 = =
------

31. 给定一个数组，生成下一个字典序的组合，如果已经是最大，返回最小的组合
------

首先，对于所有的组合，最小的一个一定是按照升序排序的，最大的一定是倒过来，因此
1. 如果我们发现是倒序的，直接翻转就好了；
2. 如果是一般情况，从后向前遍历，找到逆序的数字的边界， 假设是 k。那么我们翻转

```
void nextPermutation(vector<int>& nums) {
    int k = -1;
    for (int i = nums.size() - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            k = i;
            break;
        }
    } 
    if (k == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }
    int l = -1;
    for (int i = nums.size() - 1; i > k; i--) {
        if (nums[i] > nums[k]) {
            l = i;
            break;
        } 
    } 
    swap(nums[k], nums[l]);
    reverse(nums.begin() + k + 1, nums.end()); 
}
```

