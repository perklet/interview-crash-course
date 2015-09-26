LeetCode Complete
======

0. 说明
------

* 欢迎 Star/Fork/Pull request，不理解的也可以加我QQ：860220736（仅限学妹）。
* 原则上使用 C 做, 如果需要用到 Hash, Stack, Queue, 或者返回值特别复杂, 或者需要大量拼接字符串时, 使用 C++。
* 这份文档的目的是复习用的，并不是教如何解题的，因此只有简略介绍，适合面试前查漏补缺复习
* 请在了解基本数据结构的基础上阅读, 大概是大三的水平吧。

Let the hack begin!

1. 从数组中找出两个数字使得他们的和是给定的数字
------

使用一个散列, 存储数字和他对应的索引。然后遍历数组, 如果另一半在散列当中, 那么返回
这两个数的索引, 程序结束；如果不在, 把当前数字加入到散列中。

``` C++
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash;
    vector<int> result(2);
    for (int i = 0; i != nums.size(); ++i) {
        int reminder = target - nums[i];
        if (hash.find(reminder) != hash.end()) {
            result[0] = hash[reminder] + 1;
            result[1] = i + 1;
            return result;
        }
        hash[nums[i]] = i;
    }
    return result;
}
```

2. 给两个列表, 数字在其中按低位到高位存储, 求他们的和
------

直接迭代遍历数组, 考察细节操作。注意 dummy head 的使用。

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

使用动态规划, 在一个 Hash 中存储已经出现的字符的上一次出现的索引值, 如果索引值存在, 则把当前最长子串的左边界更新为改索引值。

注意, 当字符有限的时候, 比如限定为 ASCII 字符, 可以使用一个数组代替 Hash。

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

4. 找到两个排序数组的中位数
------

解法在[这里](https://leetcode.com/discuss/15790/share-my-o-log-min-m-n-solution-with-explanation)
把 AB 分成两份，比如 A[0..i], B[0..j] 和 A[i, m], B[j, n]，这样我们只需要下面两个条件就可以了

1. i+j = m-i + n-j
2. B[j-1] <= A[i] && A[i-1] <= B[j]

这时候我们就得到了A[i]就是我们的中位数，或者之一。
i 的初始值在0到 m 指尖，然后我们二分搜索 `i = (imin + imax) / 2, j = mid - i`。

```C
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
double findMedianSortedArrays(int* A, int m, int* B, int n) {
    if (m > n) return findMedianSortedArrays(B, n, A, m);
    int imin = 0, maxidx = m, i, j, num1, mid = (m + n + 1) >> 1,num2;
    while (imin <= maxidx) {
        i = (imin + maxidx) >> 1;
        j = mid - i;
        if (i < m && j > 0 && B[j-1] > A[i]) // B中的数字偏大
            imin = i + 1;
        else if (i > 0 && j < n && B[j] < A[i-1]) // A中的数字偏大
            maxidx = i - 1;
        else {
            if (i == 0) num1 = B[j-1];
            else if (j == 0) num1 = A[i - 1];
            else num1 = max(A[i-1],B[j-1]); // 普通情况
            break;
        }
    }
    if ((m + n) & 0x1) // odd
        return num1;
    if (i == m)
        num2 = B[j];
    else if (j == n)
        num2 = A[i];
    else 
        num2 = min(A[i], B[j]); // 普通情况
    return (num1 + num2) / 2.0; // 注意整数除法
}
```

5. 最长回文子串
------

1. 以某个元素为中心, 向两边展开, 注意处理奇数和偶数两种情况
2. Manacher 算法, 参见http://taop.marchtea.com/01.05.html

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

6. ZigZag 字符串, 把字符串掰弯, 然后再按行输出
------

考察数学, 找出规律, 所以实际上并不是 Z 子形，而是由 V 组成的，然后组合按行号重构后的字符串即可。

``` C
char* convert(char* s, int numRows) {
    int len = strlen(s);
    if (!s || numRows <= 1 || len < numRows) return s; // no need to convert

    char* zigzag = malloc(sizeof(char) * (len + 1));
    int cur = 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = i; j < len; j += 2 * (numRows - 1)) { // 每个 v 字型长度
            zigzag[cur++] = s[j];
            if (i != 0 && i != numRows - 1) { // 中间行有斜线
                int t = j + 2 * (numRows - 1) - 2 * i; // V 的第二笔
                if (t < len)
                    zigzag[cur++] = s[t];
            }
        }
    }
    zigzag[cur] = '\0';
    return zigzag;
}
```

7. 翻转数字, 溢出返回0
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
2. 判定符号, 符号只能出现一次
3. 是否溢出, 溢出返回 INT_MAX 或者 INT_MIN

```C
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
}
```

9. 是否是回文数字
------

限定不能用额外空间, 所以直接把 x 取余得到的数字作为一个反向作为一个新的数字

```c
bool isPalindrome(int x) {
    // tricky here, for x == k * 10^j
    if (x < 0 || x && (x % 10 == 0)) return false;
    int y = 0;
    while (x > y) {
        y = y * 10 + x % 10;
        x /= 10;
    }

    return x == y || x == y / 10; // 注意 x 可能是奇数长度也可能是偶数
}
```
10. 正则表达式
------

实现正则表达式, 只需要实现`.`代表任意字符, `*`代表任意重复。只需要特殊处理`*`，如果遇到了`*`，贪婪地向后匹配。
和通配符的不同之处在于，正则表达式需要两个字母组成模式，`*`是对前一个字母的修饰。

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

还是看不懂题


12. 十进制转换为罗马数字
------

直接按每位把罗马数字转换出来在拼接就好了, 使用 C 的话, 拼接字符串很麻烦。

```c++
string intToRoman(int num) {
    // note, the leading empty string is the trick here
    string thousands[] = {"", "M", "MM", "MMM"};
    string handreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return thousands[num / 1000] + handreds[num % 1000 / 100] + tens[num % 100 / 10] + ones[num % 10];

}
```

13. 罗马数字转为十进制
------

主要是当前一个数字小于后一个数字的时候, 需要添加的是后一个谁和钱一个数字的差


```C
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

横向遍历, 从头到尾, 如果, 不一致, 返回当前子串即可。如果约定不能更改当前字符串的化, 最好用
C++做, 不然操作字符串太复杂了, 没必要出错。

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

按照 LeetCode 的要求的话, 使用 C 做, 返回值太复杂了, 所以用 C++ 做了。
首先, 把数组排序, 然后使用类似 two sum 的方法做就好了

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
                k--; // 别忘了这里，还要继续寻找下一组
                j++;
            }
        }
    }
    return result;
}
```

16. 在数组中找到三个数字使得他们得和尽可能的接近给定数字, 假设结果唯一
------

和上一题解法类似, 在 http://stackoverflow.com/q/2070359 有详尽解释

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

 E17. 生成电话键盘按键数字对应的所有可能的字符串, 不限制返回结果的顺序
------

![键盘](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)

遍历数字, 设当前结果为`{a, b, c}`, 下一个数字是`3`, 找出对应的字母`{d, e, f}`, 则新的结果是

{ a + {def}, b + {def}, c + {def}}

然后把新获得的数组作为下一轮的初始数组。最开始时, 使用空数组开始。

```C++
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return vector<string> {};
    string mapping[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> combinations(1, ""); // 注意使用空字符串作为种子

    for (int i = 0; i < digits.size(); i++) {
        int digit = digits[i] - '0';
        if (mapping[digit].empty())
            continue;
        vector<string> temp;
        for (auto& c : mapping[digit])
            for (auto& combination : combinations)
                temp.push_back(combination + c);
        swap(combinations, temp);
    }
    return combinations;
}
```

18. 
------

E19. 删除链表中倒数第 k 的节点
------

双指针经典题目, 一个快指针先走 k 步, 另一个慢指针再出发, 注意链表长度小于 k 时。
注意：LeetCode 给定的 n 都是有效地, 但要求返回头指针, 如果头指针被删除需要额外注意, 因此采用 dummy head

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

E20. 判定给定的字符串是否是合法的括号序列, 可能包括大中小三类
------

使用栈的基础题，注意逻辑简化

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

    return stk.empty(); // 注意为空的条件
}
```

E21. 合并两个已经排序的链表
------

考察链表的基本操作, 很简单

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

H22. 给定数字n, 生成所有合法的 n 个括号组成的序列
------

解释暂时说不清粗

```C++
vector<string> result;
vector<string> generateParenthesis(int n) {
    gen("", n, n);
    return result;
}

// left 剩下的左括号，right 剩下的右括号
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

M23. 合并 k 个已经排序的列表
------

把列表看做一个队列, 每次拿出两个列表, 合并他们后放回到列表中, 每次遍历列表的一半, 这样每次遍历完一遍, 
    列表的长度都会减半, 直到列表的长度为1,  合并函数使用21题中的合并两个列表的函数

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
        listsSize = (listsSize + 1) / 2; // 注意这里！

    }
    return lists[0];
}
```

24. 给定一个链表, 交换两个相邻节点的值
------

最简单的做法显然是直接把前后两个节点的值交换, 但是LeetCode规定不能改变节点的值。
主要考察链表的指针操作, 注意各种细节, 一定要在纸上先把链表画出来。

```C
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

25. 给定一个链表, 把相邻的 k 个节点反转
------

和上题一样, 同样禁止改变节点的值。比较简单地解法是浪费一点空间, 使用
Stack, 实现逆转 k 个节点, 注意如果 k 较大的话, 这种方法是不合适的。

```C++
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

        if (stk.size() < k) // 剩下的节点不够 k 个了
            return dummy.next;

        pp = stk.top()->next; // 下一组中的第一个
        while (!stk.empty()) {
            p->next = stk.top();
            stk.pop();
            p = p->next;
        }

        p->next = pp;
    }
}
```

26. 从已排序数组中删除重复元素, 并返回新数组的长度
------

in-place的删除重复元素, 使用两个指针, 一个遍历, 一个指向当前的结尾。

PS：这个基础题竟然做了半个小时才做对, ⊙﹏⊙b汗, 要加强基础啊！

```C
int removeDuplicates(int* nums, int numsSize) {
    if (!nums || numsSize <= 1) return numsSize;
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

和上一题类似, 注意细节

```C
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

28. 实现 strstr 函数, 即查找子串
------

使用暴力算法, 时间复杂度O(n)。也可以用 kmp 算法。

```C
/*
 * Brute Force
 */
int strStr(char* haystack, char* needle) {
    int h = strlen(haystack);
    int n = strlen(needle);
    if (n == 0) return 0;
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

```C
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

29. 给定连个整数, 不使用乘法和除法计算除法。
------

[这里](https://leetcode.com/discuss/38997/detailed-explained-8ms-c-solution)有一个非常好的算法

计算可以从被除数中减去除数的次数

```c
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

31. 给定一个数组, 生成下一个字典序的组合, 如果已经是最大, 返回最小的组合
------

首先, 对于所有的组合, 最小的一个一定是按照升序排序的, 最大的一定是倒过来, 因此

1. 如果我们发现是倒序的, 直接翻转就好了；
2. 如果是一般情况, 从后向前遍历, 找到逆序的数字的边界,  假设是 k。那么我们翻转

```C++
void nextPermutation(vector<int>& nums) {
    int k = -1;
    for (int i = nums.size() - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            k = i;
            break;
        }
    }
    // 完全是逆序的，直接返回第一个，也就是升序排列
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

32. 从一个括号构成的字符串中找出最长的合法括号序列
------

显然判定合法括号顺序的题都可以用栈来做, 但是不妨使用动态规划来尝试一下 😄

动态规划: 见注释

```C
int longestValidParentheses(char* s) {
    int len = strlen(s);
    // 遍历到当前位置时的最长序列
    int* dp = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        dp[i] = 0;
    int longest = 0;
    // 从倒数第二个位置开始遍历
    for (int i = len - 2; i >= 0; i--) {
        // 尝试把上一个序列包围住
        int match = i + dp[i+1] + 1;
        if (s[i] == '(' && match < len && s[match] == ')') {
            dp[i] = dp[i+1] + 2;
            // 拼接合法序列，注意 match + 1
            if (match + 1 < len)
                dp[i] += dp[match + 1];
        }
        longest = longest > dp[i] ? longest : dp[i];
    }
    free(dp);
    return longest;
}
```

33. 在排序后又被反转的数组中搜索
------

既然是部分有序的,自然还是使用二分搜索了,注意终止条件.
不同于普通二分搜索的两种情况, 我们有了四种情况:

1. 前半部分有序, 并且在前半部分当中, 
2. 前半部分有序, 但是不在前半部分
3. 后半部分有序, 并且在后半部分
4. 后半部分有序, 但是不在后半部分

```C
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;

    // plain old binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;

        // left half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
            // right half is sorted
        } else {
            if (nums[mid] < target && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    return -1;
}
```

34. 查找数组中一个重复出现数字的下界和上界, 数组已排序
------

在 C++的标准库中包含了这两个函数, 分别是`std::lower_bound`和`std::upper_bound`. 


```C++
vector<int> searchRange(vector<int>& nums, int target) {
    return vector<int> {lower(nums, target), upper(nums, target)}; 
}

int lower(vector<int>& nums, int target) {
    int first = 0, last = nums.size();
    while (first < last) {
        int middle = first + (last - first) / 2;
        if (target > nums[middle]) // 寻找下界
            first = middle + 1;
        else
            last = middle;
    }
    return nums[first] == target ? first : -1;
}

int upper(vector<int>& nums, int target) {
    int first = 0, last = nums.size();
    while (first < last) {
        int middle = first + (last - first) / 2;
        if (target >= nums[middle]) // 寻找上界only difference with lower
            first = middle + 1;
        else
            last = middle;
    }

    // note: std::upper_bound return offset by 1
    return nums[first - 1] == target ? first - 1 : -1;
}
```

35. 二分查找数字, 如果没有找到, 返回应该插入的位置
------

36. 合法数独, 给定一个数独表,判定当前是否合法
------

37. 求解数独
------

38. 数数并说出来
------

不太理解这道题有什么意义,直接暴力做出来了

```C++
string countAndSay(int n) {
    string result = "1";
    for (int i = 0; i < n -1; i++) {
        string temp;
        for (int j = 0; j < result.size(); j++) {
            int count = 1;
            while (j + 1 < result.size() && result[j+1] == result[j]) {
                j++; count++;
            }
            temp += count + '0';
            temp += result[j];
        }
        result = temp;
    }
    return result;
}
```

39. 
------

41. 给定一个数组,找到第一个缺失的正数
------

显然,结果的范围是[1..n+1]. 而数组的长度为 n 我们把每个位置都放上 i+1,
这样如果有位置不是 i+1, 则找到了结果, 如果都相等则是 n+1.

```c
void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++)
        // 注意此处的 while
        while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1])
            swap(&nums[i], &nums[nums[i] - 1]);
    
    for (int i = 0; i < numsSize; i++)
        if (nums[i] != i + 1)
            return i + 1;
    
    return numsSize + 1;
}
```

42. 给定一个数组表示柱子的高度，求能存贮的雨水的总量
------

从两边向中间收拢

```C
int trap(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int water = 0;
    int max_left = 0, max_right = 0;
    
    // 从两侧向中间缩小, 可以算作是两个指针吧
    while (left <= right) {
        if (height[left] <= height[right]) {
            if (height[left] >= max_left)
                max_left = height[left];
            else
                water += max_left - height[left];
            left++;
        } else {
            if (height[right] >= max_right)
                max_right = height[right];
            else
                water += max_right - height[right];
            right--;
        }
    }
    return water;
}
```

43. 给定两个任意长的字符串，返回一个字符串，代表他们相乘的结果
------

按整数除法运算即可，重点是下标的表示

```C
#define tonum(c) (c - '0')
#define tochar(i) (i + '0')

char* multiply(char* num1, char* num2) {
    // 结果的长度不会超过 m+n,
    // 假设某个数是 n 位的9, 则结果比另一个数结尾加上 n 个 0还小
    int n = strlen(num1), m = strlen(num2);
    int len = m+n;
    char* result = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        result[i] = '0';
    result[len] = '\0';

    for (int i = n - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = m - 1; j >= 0; j--) {
            int v = tonum(result[i+j+1]) +  tonum(num1[i]) * tonum(num2[j]) + carry;
            result[i+j+1] = tochar(v % 10);
            carry = v / 10;
        }
        result[i] += carry;
    }
    
    for (int i = 0; i < len; i++)
        if (result[i] != '0')
            return result+i;
    
    return "0";
}
```

44. 通配符匹配，`?` 代表任意一个字符，`*`代表任意一个或多个字符
------

注意和正则表达式的区别，要求完全匹配。这道题的关键在于对星号的处理, 如果出现星号的时候, 我们记录当时的p 和 s 的值, 如果发生了不匹配的话, 我们尝试回到该位置的下一个位置开始匹配

```C

bool isMatch(char* s, char* p) {
    char* star = NULL;
    char* revert = s;
    while (*s) {
        if (*s == *p || *p == '?')
            s++, p++;
        else if (*p == '*')
            star = p++, revert = s;
        else if (star) 
            p = star + 1, s = ++revert;
        else
            return false;
    }
    
    // 如果剩下了 p, 那应该全都是*才对
    while (*p) {
        if (*p++ != '*')
            return false;
    }
    
    return true;
}
```

45. 跳跃游戏，给定一个数组，每个数字是在该位置可以向前移动的距离，返回最少需要多少次才能到达终点
------

比较简单，看注释吧

```C
int jump(int* nums, int numsSize) {
    int steps = 0;
    int last = 0; // last range
    int cur = 0; // current range
    
    for (int i = 0; i < numsSize; i++) {
        // beyond range, make another jump
        if (i > last)
            last = cur, steps++;
        // if we could reach longer?
        if (nums[i] + i > cur)
            cur = nums[i] + i;
    }
    return steps;
}
```

48. 给定一个`n*n`的图像旋转图像，顺时针旋转90度
------

做法显然是从里到外，一层一层的旋转，这道题主要考察下标的操作

```C
void rotate(int** matrix, int m, int n) {
    for (int layer = 0; layer < n / 2; layer++) {
        int first  = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int top = matrix[first][i];
            // up <- left
            matrix[first][i] = matrix[last-offset][first];
            // left <- down
            matrix[last-offset][first] = matrix[last][last-offset];
            // down <- right
            matrix[last][last-offset] = matrix[i][last];
            // right <- up
            matrix[i][last] = top;
        }
    }
}
```

49. LeetCode 题目改了
------

回头再写

50. 实现pow(x, n)
------

显然不能直接阶乘过去，分治法

```C
double myPow(double x, int n) {
    if (n == INT_MIN) return myPow(x, n - 1) * x;
    if (n < 0) return 1 / myPow(x, -n);
    if (n == 0) return 1;
    if (n == 1) return x;
    double y = myPow(x, n / 2);
    if (n & 0x1) 
        return y * y * x;
    else
        return y * y;
}
```

51. N 皇后问题
------

52. N 皇后一共有多少个解
------

53. 最大子序列和
------

动态规划经典题目，遍历数组，如果已经当前子序列已经小于0了，抛弃并置 sum = 0
如果比当前和更大，更新

`dp[n+1] = max(dp[n], dp[n] + A[n+1])`

```C
int maxSubArray(int* nums, int numsSize) {
    int sum = 0;
    int m = INT_MIN;
    
    for (int i =0; i< numsSize; i++) {
        sum += nums[i];
        if (sum > m)
            m = sum;
        if (sum < 0)
            sum = 0;
    }
    return m;
}
```

54. 顺时针螺旋打印矩阵
------

一圈一圈地打印就好了

```C
int* spiralOrder(int** matrix, int row, int col) {
    if (row == 0 || col == 0) return NULL;
    int top = 0, right = col - 1, down = row - 1, left = 0;
    int index = 0;
    int* result = malloc(sizeof(int) * row * col);
    while (top <= down && left <= right) {
        for (int i = left; i <= right; i++)
            result[index++] = matrix[top][i];
        top++; //
        for (int i = top; i <= down; i++)
            result[index++] = matrix[i][right];
        right--; // 
        // 注意这个 if 语句
        if (top <= down)
            for (int i = right; i >= left; i--)
                result[index++] = matrix[down][i];
        down--; // 
        // 注意这个 if 语句
        if (left <= right)
            for (int i = down; i >= top; i--)
                result[index++] = matrix[i][left];
        left++; // 
    }
    return result;
}
```

55. 给定一个数组，每个数字表示在当前步可以移动的距离，返回是不是能够到达终点
------

使用动态规划求解，如果当前距离大于最远距离，更新最远距离，如果已经超过了最远距离，跳出

```C
bool canJump(int* nums, int numsSize) {
    int i;
    int reach = 0;
    for (i = 0; i < numsSize && i <= reach; i++)
        if (nums[i] + i > reach)
            reach = nums[i] + i;
    return i == numsSize;
}
```

56. 合并序列，给定一组序列，把其中重叠的序列合并
------

这道题用 Python 做竟然比用 C++ 还要快

```Python
"""
class Interval(object):
    def __init__(self, start=0, end=0):
        self.start = start
        self.end= end
"""

def merge(intervals):
    intervals.sort(key=lambda x: x.start)
    combined = []
    for interval in intervals:
        if combined and interval.start <= combined[-1].end:
            combined[-1].end = max(combined[-1].end, interval.end)
        else:
            combined.append(interval)
    return combined
```

57. 添加序列，给定一组已经排序的序列，向其中插入一个序列，需要合并的合并
------

这道题inplace 的做法感觉没有什么意义，因为如果在中间插入的话，后半部分还是要被拷贝

```Python
def insert(self, intervals, newInterval):
    result = []
    start = newInterval.start
    end = newInterval.end
    remainder = 0
    for interval in intervals:
        if start <= interval.end:
            if end < interval.start:
                break
            start = min(start, interval.start)
            end = max(end, interval.end)
        else:
            result.append(interval)
        remainder += 1
    result.append(Interval(start, end))
    result += intervals[remainder:]
    return result
```

58. 给定一个字符串，求其中最后一个单词的长度
------

显然这道题可以用 strlen 求出长度然后从后往前数，但是，这样相当于多遍历了一次
直接从后往前可以保证只遍历一次

```C
int lengthOfLastWord(char* s) {
    int len = 0;
    bool inWord = false;
    while (*s) {
        if (isspace(*s)) {
            inWord = false;
        } else {
            if (!inWord) {
                len = 1;
                inWord = true;
            } else {
                len++;
            }
        }
        s++;
    }
    return len;
}
```

59. 给定 n，把1, 2, 3 ...螺旋打印到矩阵中
------

和上一个完全一样的思路，只是这次是打印罢了

```C
/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n) {
    int** matrix = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        matrix[i] = malloc(sizeof(int) * n);
        
    int top = 0, left = 0, down = n - 1, right = n - 1;
    int a = 1;
    while (top <= down && left <= right) {
        for (int i = left; i <=right; i++)
            matrix[top][i] = a++;
        top++;
        for (int i = top; i <= down; i++) {
            matrix[i][right] = a++;
        }
        right--;
        if (top <= down)
            for (int i = right; i >= left; i--)
                matrix[down][i] = a++;
        down--;
        if (left <= right)
            for (int i = down; i >= top; i--)
                matrix[i][left] = a++;
        left++;
    }
    return matrix;
}
```

60. 
------

61. 把列表旋转到倒数第 k 位
------

需要注意的是 k 大于列表长度的情况，这时候需要取余

```C
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || k <= 0) return head;
    
    int l = 1;
    struct ListNode* n = head;
    while (n->next) {
        n = n->next;
        l++;
    }
    // n is now the tail!
    
    if (k >= l) k %= l;
    if (k == 0) return head;
    
    struct ListNode dummy, *p = &dummy;
    dummy.next = head;
    int i = l - k;
    while (i--)
        p = p->next;
    
    dummy.next = p->next;
    p->next = NULL;
    n->next = head;
    
    return dummy.next;
}
```

62. 给定一个`m*n`的矩阵，有多少种方法从左上角移动到右下角
------

显然可以使用组合数学直接求出来解，但是容易溢出。而且这是一道经典的动态规划题目，对于
每个格子，可以从他的上部或者左面移动过来。

```C++
int uniquePaths(int m, int n) {
    vector<vector<int>> grid(m, vector<int> (n, 1));
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
    return grid[m - 1][n - 1];
}
```

63. 同上题，区别是在一些位置是有障碍物的
------

经过分析可知，递推关系是一样的，只需要把有障碍格子的到达方法设定为0。这个主要是实现上的一些技巧，
见注释。

```C++
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    // 注意设定长宽均 +1，但是初始化为0，边界就成了障碍
    vector<vector<int>> pathes(m + 1, vector<int> (n + 1, 0));
    pathes[0][1] = 1; // 给定一个入口
    for (int i = 1; i < m + 1; i++)
        for (int j = 1; j < n + 1; j++)
            // 注意此处的偏移
            if (obstacleGrid[i-1][j-1] == 1)
                pathes[i][j] = 0;
            else
                pathes[i][j] = pathes[i-1][j] + pathes[i][j-1];
    return pathes[m][n]; 
}
```

64. 给定一个`m*n`矩阵，每个数字代表经过该处的耗费，找出一条耗费最小的路径
------

依然是动态规划

```C++
inline int min(int a, int b) {
    return a < b ? a : b;
}
int minPathSum(vector<vector<int>>& grid) {
    // if modifying the grid is disallowed, copy it 
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
            if (i == 0 && j == 0)
                continue;
            else if (i == 0 && j != 0)
                grid[i][j] += grid[i][j-1];
            else if (i != 0 && j == 0)
                grid[i][j] += grid[i-1][j];
            else
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
    return grid[grid.size()-1][grid[0].size()-1];
}
```

65. 判定一个字符串是否是合法的数字，包括了正负号，小数点，`e`等
------

一些例子：

    "0" => true
    " 0.1 " => true
    "abc" => false
    "1 a" => false
    "2e10" => true

这道题就是细节题，用 C 处理字符串太蛋疼了，直接上 Python 了

```Python
def isNumber(self, s):
    BEFORE = 0 # before dot
    AFTER = 1 # after dot
    EXP = 2 # after e
    phase = BEFORE
    allow_sign = True

    s = s.strip()

    if not any([c.isdigit() for c in s]):
        return False

    if s == '' or s[0] == 'e' or s[-1] == 'e' or s == '.':
        return False
    if s[0] == '.' and s[1] == 'e':
        return False
    if s[0] == '-' and s[1] == 'e':
        return False

    for c in s:
        if '0' <= c <= '9':
            allow_sign = False
        elif c == '.':
            allow_sign = False
            if phase == EXP or phase == AFTER:
                return False
            else:
                phase = AFTER
        elif c == 'e':
            if phase == EXP:
                return False
            allow_sign = True
            phase = EXP

        elif c == '-' or c == '+':
            if not allow_sign:
                return False
            allow_sign = False
        else:
            return False

    if phase == EXP:
        return s[-1].isdigit()

    return True
```

66. 给定一个字符串代表的数字，返回加1后的数字
------

我们知道只有当数字是999....999的时候，才会使得数字的长度+1变为1000...000。

```C++
vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] == 9) {
            digits[i] = 0;
        } else {
            digits[i]++;
            return digits;
        }
    }
    // real trick here, we know that the number is 999...999
    digits[0] = 1;
    digits.push_back(0);
    return digits;
}
```

67. 给定两个字符串代表的二进制数字，返回他们相加的和
------

和上一题一样，按照加法定义做就好了

```C
#define tonum(c) (c - '0')
#define tochar(i) (i + '0')

char* addBinary(char* a, char* b) {
    int m = strlen(a), n = strlen(b);
    int len = (m > n ? m : n) + 1; // strlen(c)
    char* c = malloc(sizeof(char) * len + 1); // with ending null
    memset(c, '0', len+1);
    c[len] = 0;
    int carry = 0;
    for (int i = 1; i <= len; i++) {
         c[len-i] = tochar((i <= m ? tonum(a[m-i]) : 0) ^ (i <= n ? tonum(b[n-i]) : 0) ^ carry);
         carry = ((i <= m ? tonum(a[m-i]) : 0) + (i <= n ? tonum(b[n-i]) : 0) + carry) >> 1;
    }
    return c[0] == '0' ? c+1 : c;
}
```

68. 文字对齐
------

待研究

```C++
vector<string> fullJustify(vector<string>& words, int L) {
    vector<string> res;
    for(int i = 0, k, l; i < words.size(); i += k) {
        for(k = l = 0; i + k < words.size() and l + words[i+k].size() <= L - k; k++) {
            l += words[i+k].size();
        }
        string tmp = words[i];
        for(int j = 0; j < k - 1; j++) {
            if(i + k >= words.size()) tmp += " ";
            else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
            tmp += words[i+j+1];
        }
        tmp += string(L - tmp.size(), ' ');
        res.push_back(tmp);
    }
    return res;
}
```

69. 给定整数x，求 sqrt(x)
------

比较坑的是 LeetCode 要求的是 `y*y < x` 的最大整数

```C
int mySqrt(int x) {
    if (x <= 1) return x;
    const double EPS = x * 0.0001;
    double y = x / 2; // initial guess
    while (fabs(y * y - x) > EPS) {
        y = (y + x / y) / 2;
    }
     
    long z = (long) y;
    while (z * z > x) z--;
    return z;
}
```

70. 爬梯子，一次可以爬一步或者两步，有几种方法爬完梯子
------

斐波那契数列，也可以理解为动态规划

```C
int climbStairs(int n) {
    int a = 1, b = 1, t;
    for (int i = 1; i < n; i++)
        t = b, b += a, a = t;
    return b;
}
```

71. 简化 Unix 路径，需要处理`.`, `..` 和多个斜杠等情况
------

没有什么需要注意的，主要是使用 stringstream 用作string.split

```C++
string simplifyPath(string& path) {
    vector<string> dirs;
    stringstream ss(path);
    string dir;
    while (getline(ss, dir, '/')) {
        if (dir == "." || dir == "")
            continue;
        else if (dir == "..") {
            if (!dirs.empty())
            dirs.pop_back();
        } else
            dirs.push_back(dir);
    }
    string result;
    for (auto& dir : dirs)
        if (!dir.empty())
            result += "/" + dir;
    return result.size() ? result : "/";
}
```

72. 编辑距离
------

73. 给定一个矩阵，如果某个元素为零，把所在的行和所在的列都设为零
------

一种可以接受的方法是使用O(m+n)的空间，记录哪行哪列需要设为零

```C++
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0) return;
    int n = matrix[0].size();
    if (n == 0) return;
    
    vector<bool> row(m), column(n);
    
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] == 0)
                row[i] = true, column[j] = true;
    
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (row[i] || column[j])
                matrix[i][j] = 0;
}
```

74. 搜索矩阵，矩阵每行从左到右依次增大，每行都比上一行大
------

当做数组直接二分搜索就可以了

```C++
bool searchMatrix(int** matrix, int row, int col, int target) {
    int left = 0, right = row * col - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (matrix[mid/col][mid%col] < target)
            left = mid + 1;
        else if (matrix[mid/col][mid%col] == target)
            return true;
        else
            right = mid - 1;
    }
    return false;
}
```

75. 颜色排序，每个物体有颜色属性，把他们按照RGB的顺序排序
------

一种方法是简单地2 pass解法，遍历一遍计数再输出。另一种方法是把红色往前交换，蓝色往后交换

```

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void sortColors(int* nums, int numsSize) {
    const int RED = 0, GREEN = 1, BLUE = 2;
    int reds = 0,  blues = numsSize - 1;
    for (int i = 0; i <= blues; i++) {
        while (nums[i] == BLUE && i < blues) swap(&nums[i], &nums[blues--]);
        while (nums[i] == RED && i > reds) swap(&nums[i], &nums[reds++]);
    }
}
```

76. 跳过
------

77. 给定数字 n 和 k，生成从 n 中取出 k 个数字的所有情况
------

数学上的组合，使用回溯来做，对状态空间进行深度搜索。

回溯方法通常适合对状态空间树的深度优先搜索相结合的，当一个解已经不满足条件时，剪枝；
如果满足条件，直到找到完全解未知。

```C++
// 组合是不要求顺序的
vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    if (n < k)
        return result;
    vector<int> temp(0, k);
    combine(result, temp, 0, 0, n, k);
    return result;
}

void combine(vector<vector<int>>& result, vector<int>& temp, int start, int count, int n, int k) {
    // 1. 回溯条件，找到了一个解
    if (count == k) {
        result.push_back(temp);
        return;
    }
    // 2. 深度优先搜索
    for (int i = start; i < n; i++) {
        temp.push_back(i + 1);
        // 只搜索比 i 大的即可
        combine(result, temp, i+ 1, count+1, n, k);
        temp.pop_back();
    }
}
```

78. 给定一个集合，找到它的所有子集
------

我们知道对于 n 个元素的集合，有2^n个子集，通过每个元素在不在子集中构造一个状态空间树

```C++
// use backtracking and do a dfs search
    
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    if (nums.empty()) return result;
    sort(nums.begin(), nums.end());
    vector<int> temp;
    subsets(nums, result, temp, 0);
    return result;
}

// for each solution, the can be divided into two sub solutions: in or out
void subsets(vector<int>& nums, vector<vector<int>>& result, vector<int> temp, int i) {
    if (i == nums.size()) {
        result.push_back(temp);
        return;
    }
    
    vector<int> t = temp;
    subsets(nums, result, temp, i + 1);
    temp.push_back(nums[i]);
    subsets(nums, result, temp, i + 1);
}
```

79. 给定一个二维字符数组，查找一个单词是否能够有连续的字母构成，不能交叉
------

也是深度优先的做法，首先找到开始的字母，然后依次向上下左右查找，注意还需要统计有没有访问过

```C++
bool exist(vector<vector<char>>& board, string word) {
    int row = board.size();
    int col = board[0].size();
    vector<vector<bool>> visited(row, vector<bool> (col, false));
    
    bool found = false;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == word[0]) {
                if (findNext(board, word, visited, i, j, 0))
                    found = true;
            }
        }
    }
    return found;
}

bool findNext(vector<vector<char>>& board, string& word, vector<vector<bool>>& visited, int m, int n, int i) {
    
    if (i == word.size())
        return true;
    if (m >= board.size() || n >= board[0].size() || m < 0 || n < 0|| visited[m][n] || board[m][n] != word[i])
        return false;
    char temp = board[m][n];
    board[m][n] = -1;
     
    bool exist = findNext(board, word, visited, m + 1, n, i+1) ||
        findNext(board, word, visited, m - 1, n, i+1) ||
        findNext(board, word, visited, m, n+1, i+1) ||
        findNext(board, word, visited, m, n-1, i+1);
    board[m][n] = temp;
    return exist;
}
```

80. 从排序数组中删除重复元素，但是允许一个元素重复出现两次
------

巧妙地解法，和`i-2`的元素对比

```C
int removeDuplicates(int* nums, int numsSize) {
    if (!nums || numsSize < 1) return 0;
    int len = 0, counter = 0;
    for (int i = 0; i < numsSize; i++) {
        if (len < 2 || nums[i] != nums[len-2])
            nums[len++] = nums[i];
    }
    return len;
}
```

81. 在被翻转的数组中查找元素
------

经典题目，还是一个二分查找问题，只是要分很多种情况

```C
bool search(int A[], int n, int key) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (A[m] == key) return true; //return m in Search in Rotated Array I
        if (A[l] < A[m]) { //left half is sorted
            if (A[l] <= key && key < A[m])
                r = m - 1;
            else
                l = m + 1;
        } else if (A[l] > A[m]) { //right half is sorted
            if (A[m] < key && key <= A[r])
                l = m + 1;
            else
                r = m - 1;
        } else {
            l++;
        }
    }
    return false;
}
```

82. 从已经排序的链表中删除所有重复过的元素，只留下只出现一次的元素
------

考察链表操作

```C
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummy, *p = &dummy;
    dummy.next = head;
    while (p && p->next && p->next->next) {
        if (p->next->val == p->next->next->val) {
            struct ListNode* distinct = p->next;
            int dup = p->next->val;
            while (distinct && distinct->val == dup) {
                distinct = distinct->next; // TODO: fix mem leak
            }
            p->next = distinct;
        } else {
            p=p->next;
        }
    }
    return dummy.next;
}
```

83. 从已经排序的链表中删除所有重复过的元素，但是重复过的也留下一个，即，使新链表不重复
------

同样是考察链表基本操作

```C
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummy, *p = &dummy; dummy.next = head;
    while (p && p->next) {
        if (p->val == p->next->val) {
            int dup = p->val;
            while (p->next && p->next->val == dup)
                p->next = p->next->next; // TODO: fix mem leak
        } else
            p = p->next;
    }
    return dummy.next;
}
```

84. 在柱状图中查找最大的矩形
------

见注释

```C++
int largestRectangleArea(vector<int>& height) {
    stack<int> stk;
    height.push_back(0); // dummy end
    int result  =0;
    // 总结，对于需要查找上一次最大元素的问题，可以考虑使用栈存储
    for (int i = 0; i < height.size(); ) {
        // 当遇到更高的柱子时候，先存入堆栈
        if (stk.empty() || height[i] > height[stk.top()]) // meet higher
            stk.push(i++);
        // 当遇到低一些的柱子时候，计算这些柱子到上一个更矮的柱子之间的最大举行，如果已经清空，说明之前所有柱子都更低
        else { // lower
            int h = stk.top();
            stk.pop();
            result = max(result, height[h] * (stk.empty() ? i : i - stk.top() -1));
        }
    }
    return result;
}
```

86. 链表分区，要求把小于某个值得元素全都放到前面
------

对于链表这道题很简单，分两个列表在合并就好了，问题是当我们处理类似的数组问题时，也有一种巧妙地O(n)的解法

```C
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode small, *psmall = &small;
    struct ListNode big, *pbig = &big;
    psmall->next = pbig->next = NULL;
    
    while (head != NULL) {
        if (head->val < x) {
            psmall->next = head;
            psmall = psmall->next;
        } else {
            pbig->next = head;
            pbig = pbig->next;
        }
        head = head->next;
    }
    psmall->next = big.next;
    pbig->next = NULL;
    return small.next;
}
```

88. 合并已排序数组，要求合并到其中一个空间较大的数组中
------

对于这种要求 in-place的算法，从后往前往往可以解决

```C
void merge(int* nums1, int m, int* nums2, int n) {
    int len = m + n - 1;
    m--, n--;
    while (m >= 0 && n >= 0) {
        if (nums1[m] > nums2[n]) {
            nums1[len--] = nums1[m--];
        } else {
            nums1[len--] = nums2[n--];
        }
    }
    while (n >= 0) {
        nums1[n] = nums2[n];
        n--;
    }
    
}
```

89. 生成格雷码(Gray Code)
------

记住格雷码的生成规则

```C++
vector<int> grayCode(int n) {
    vector<int> v;
    for (int i = 0; i < (1 << n); i++) {
        v.push_back((i >> 1) ^ i);
    }
    return v;
}
```

90. 由给定元素生成子集，可能包含重复元素
------

使用了和手机键盘生成字符串号码类似的迭代算法，注意其中对重复元素的处理

```C++
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> sets;
    sets.push_back({});
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ) {
        int count = 0; // dup count
        while (count + i < nums.size() && nums[count+i] == nums[i])
            count++;
        int prev_n = sets.size();
        for (int j = 0; j < prev_n; j++) {
            vector<int> instance = sets[j];
            // put dup element `count` times
            for (int k = 0; k < count; k++) {
                instance.push_back(nums[i]);
                sets.push_back(instance);
            }
        }
        i += count;
        
    }
    return sets;
}
```

91. 给定一个数组只包含1-9，可以用1-26代表字母，求出从其中能都得到多少字符串
------

使用动态规划，但是注意其中0的处理，很玄妙

```C
int numDecodings(char* s) {
    if (!s || strlen(s) == 0 || s[0] == '0') return 0;
    int r1 = 1, r2 = 1; // r1: 前一个字符， r2：前两个字符
    char* p = s++; // 上一个字符

    while (*s) {
        if (*s == '0')
             r1 = 0; // 0 不能单独构成字母
        if (*p == '1' || *p == '2' && *s < '7') { // 形成两种可能
            int t = r1; 
            r1 = r2 + r1; 
            r2 = t;
        } else {
            r2 = r1; // 新加入的数字只能单独构成字母
        }
        
        p = s++;
    }
    return r1;
}
```

92. 在给定区间上翻转数组
------

同样是数组草错细节题

```C
struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    if (m == n) return head;
    struct ListNode dummy, *p = &dummy, * small_node, * big_node; // actually the prev ones
    dummy.next = head;
    n -= m;
    
    while (--m) // m starts from 1, so not m--
        p = p->next;
    struct ListNode* start = p->next;
    while (n--) {
        struct ListNode* next = start->next;
        start->next = next->next;
        next->next = p->next;
        p->next = next;
    }
    
    return dummy.next;
}
```

93. 恢复 IP 地址，给定一个字符串，适当插入点，一共有多少种方式构成 IP 地址
------

又是一道 DFS 的题，注意对于字符串问题如何处理

```C++
vector<string> restoreIpAddresses(string s) {
    vector<string> result;
    restore(result, s, "", 0, 0);
    return result;
}

void restore(vector<string>& result, string& s, string restored, int start, int dots) {
    if (dots > 4) return;
    if (dots == 4 && start == s.size())
        result.push_back(restored);
    
    for (int i = 1; i < 4; i++) {
        if (start + i > s.size())
            break;
        string part = s.substr(start, i);
        if (part[0] == '0' && part.size() > 1 || i == 3 && stoi(part) > 255)
            continue;
        restore(result, s, restored + part + (dots==3 ? "" : "."), start + i, dots + 1);
        
    }

}
```

94. 中序遍历二叉树
------

当然是使用栈了

```C++
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* current = root;
    
    while (!stk.empty() || current) {
        if (current) {
            stk.push(current);
            current = current->left;
        } else {
            current = stk.top();
            stk.pop();
            result.push_back(current->val);
            current = current->right;
        }
    }
    return result;
}
```


96. 给定数字n，从1到 n 作为节点有多少种方式生成二叉树
------

这道题看似是树，实际上是一个动态规划问题。

```C
int numTrees(int n) {
    if (n == 0) return 0;
    
    int* dp = malloc(sizeof(int) * (n+1));
    dp[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        int num = 0;
        for (int j = 0; j <= i; j++) // 依次选取第 k 个点作为根
            num += dp[j - 1] * dp[i - j];
        dp[i] = num;
    }
    return dp[n];
}
```

97. 给定两个字符串交叉是否能够构成第三个字符串
------

这道题是一道二维的 DP 问题，因为需要对于每个字符串的每个位置用另一个字符串尝试匹配

```C
bool isInterleave(char* s1, char* s2, char* s3) {
    int l1 = strlen(s1), l2 = strlen(s2), l3 = strlen(s3);
    if (l1 + l2 != l3) return false;
    // 在 i+j 位置 s1[i] s2[j] 是否能够构成s[i+j]
    bool** dp = malloc(sizeof(bool*) * (l1 + 1));
    for (int i = 0; i <= l1; i++)
        dp[i] = malloc(sizeof(bool) * (l2 + 1));
    
    for (int i = 0; i <= l1; i++)
        for (int j = 0; j <= l2; j++)
            if (i == 0 && j == 0)
                dp[i][j] = true;
            else if (i == 0)
                dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i+j-1]); // 注意：赋值的优先级更高
            else if (j == 0)
                dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
            else
                dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1] || dp[i][j-1] && s2[j-1] == s3[i+j-1]);
    return dp[l1][l2];
}
```

98. 验证二叉搜索树是否合法
------

先序遍历即可

```C
bool valid(struct TreeNode* root, long left, long right) {
    return root == NULL || root->val > left && root->val < right &&
        valid(root->left, left, root->val) &&
        valid(root->right, root->val, right);
}
 
bool isValidBST(struct TreeNode* root) {
    return valid(root, INT_MIN - 1l, INT_MAX + 1l);
}
```

99. 在二叉搜索树中有两个节点被调换了，找出这两个节点，并恢复该二叉树
------

```C
struct TreeNode* prev = NULL;
struct TreeNode* first = NULL;
struct TreeNode* second = NULL;

void traverse(struct TreeNode* root) {
    if (!root) return;
    traverse(root->left);
    if (prev && prev->val > root->val) {
         if (!first) first = prev;
         second = root;
    }
    prev = root;
    traverse(root->right);
}

void recoverTree(struct TreeNode* root) {
    prev = first = second = NULL;
    traverse(root);
    if (!first) return;
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
}
```

100. 判断是否是相同的树
------

```C
bool isSameTree(struct TreeNode *p, struct TreeNode *q) {
    if (p == NULL || q == NULL) {
        return p == q;
    } else {
        return p->val == q->val
            && isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
}
```

101. 判断是不是左右对称的树
------

```C
bool sym(struct TreeNode* left, struct TreeNode* right) {
    if (left && !right || !left && right)
        return false;
    return !left && !right ||
        left->val == right->val && 
        sym(left->left, right->right) &&
        sym(right->left, left->right);
}

bool isSymmetric(struct TreeNode* root) {
    if (!root) return true;
    return sym(root->left, root->right);
}
```

102. 二叉树层序遍历
------

```C++
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    vector<TreeNode*> current, next;
    current.push_back(root);
    while (!current.empty()) {
        next.resize(0);
        vector<int> vals;
        for (int i = 0; i < current.size(); i++) {
            if (current[i]->left)
                next.push_back(current[i]->left);
            if (current[i]->right)
                next.push_back(current[i]->right);
            vals.push_back(current[i]->val);
        }
        result.push_back(vals);
        current = next;
    }
    return result;
}
```

103. 二叉树 ZigZag 层序遍历
------

这道题更好的做法是使用一个栈，从而使得每行的顺序都是上一行的翻转

```C++
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    vector<TreeNode*> current, next;
    current.push_back(root);
    bool odd = true;
    while (!current.empty()) {
        next.resize(0);
        vector<int> vals;
        for (int i = 0; i < current.size(); i++) {
            if (current[i]->left)
                next.push_back(current[i]->left);
            if (current[i]->right)
                next.push_back(current[i]->right);
            vals.push_back(current[i]->val);
        }
        if (!odd) reverse(vals.begin(), vals.end());
        odd = !odd;
        result.push_back(vals);
        current = next;
    }
    return result;
}
```

104. 树的最大深度
------

```C
int maxDepth(struct TreeNode* root) {
    if (!root) return 0;
    int left = maxDepth(root->left), right = maxDepth(root->right);
    return (left > right ?left : right) + 1;
}
```

105. 从前序遍历和中序遍历生成生二叉树
------

```C
struct TreeNode* build(int* prestart, int* preend, int* instart, int* inend) {
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = *prestart;
    root->left = root->right = NULL;
    
    if (prestart == preend)
        return root;
    
    int* root_inorder = instart;
    while (root_inorder <= inend && *root_inorder != *prestart)
        root_inorder++;
    int left_len = root_inorder - instart;
    int right_len = inend - root_inorder;
    if (left_len > 0)
        root->left = build(prestart + 1, prestart + left_len, instart, root_inorder - 1);
    if (right_len > 0)
        root->right = build(prestart + left_len + 1, preend, root_inorder + 1, inend);
    return root;
}
// m always equals n, otherwise it's bad input
struct TreeNode* buildTree(int* preorder, int m, int* inorder, int n) {
    if (n==0) return NULL;
    return build(preorder, preorder + n - 1, inorder, inorder + n - 1);
}
```

106. 从中序遍历和后序遍历生成二叉树
------

```C
struct TreeNode* build(int* instart, int* inend, int* poststart, int* postend) {
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = *postend;
    root->left = root->right = NULL;
    
    if (poststart == postend)
        return root;
    
    int* root_inorder = instart;
    while (root_inorder <= inend && *root_inorder != *postend)
        root_inorder++;
    int left_len = root_inorder - instart;
    int right_len = inend - root_inorder;
    if (left_len > 0)
        root->left = build(instart, root_inorder - 1, poststart, poststart + left_len - 1);
    if (right_len > 0)
        root->right = build(root_inorder + 1, inend, poststart + left_len, postend - 1);
    return root;
}
struct TreeNode* buildTree(int* inorder, int m, int* postorder, int n) {
    if (n == 0) return NULL;
    return build(inorder, inorder + n - 1, postorder, postorder +n - 1);
}
```

107. 二叉树层序遍历，但要生成翻转的遍历序列
------

```C++
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    vector<TreeNode*> current, next;
    current.push_back(root);
    while (!current.empty()) {
        next.resize(0);
        vector<int> vals;
        for (int i = 0; i < current.size(); i++) {
            if (current[i]->left)
                next.push_back(current[i]->left);
            if (current[i]->right)
                next.push_back(current[i]->right);
            vals.push_back(current[i]->val);
        }
        result.push_back(vals);
        current = next;
    }
    reverse(result.begin(), result.end());
    return result;
}
```

108. 把排序数组转化为二叉树
------

```C
 struct TreeNode* bst(int* left, int* right) {
    int* mid = left + (right - left) / 2;
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = *mid;
    root->left = root->right = NULL;
    if (left < mid)
        root->left = bst(left, mid-1);
    if (mid < right)
        root->right = bst(mid+1, right);
    return root;
}
struct TreeNode* sortedArrayToBST(int* nums, int n) {
    if (n == 0) return NULL;
    return bst(nums, nums + n -1);
}
```

109. 把排序列表转化为二叉树
------

```C
struct ListNode* list;
int len(struct ListNode* head) {
    int l = 0;
    while (head)
        head = head->next, l++;
    return l;
}

struct TreeNode* bst(int n) {
    if (n == 0) return NULL;
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->left = bst(n/2);
    root->val = list->val;
    list = list->next;
    root->right = bst(n - n / 2 - 1);
    return root;
}
struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (!head) return 0;
    list = head;
    return bst(len(head));
}
```

110. 平衡二叉树
------

```C
int height(struct TreeNode* root) {
    if (!root) return 0;
    int left = height(root->left);
    int right = height(root->right);
    if (left > right + 1 || right > left + 1 || left == -1 || right == -1)
        return -1;
    return (left > right ? left : right) + 1;
}
bool isBalanced(struct TreeNode* root) {
    return height(root) != -1;
}
```

111. 二叉树最小高度
------

```C
int minDepth(struct TreeNode* root) {
    if (!root) return 0;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    if (!right) return left + 1;
    if (!left) return right + 1; // tricky here,当有空节点时，不能返回0，而是返回另一个值
    
    return (left < right ? left : right) + 1;
}
```

112. 二叉树中是否存在和为某个数的路径
------

```C
bool hasPathSum(struct TreeNode* root, int sum) {
    if (!root) return false;
    if (!root->left && !root->right) return sum == root->val;
    return hasPathSum(root->left, sum - root->val) ||
        hasPathSum(root->right, sum - root->val);
}
```

113. 接上题，把这个路径找出来
------

```C++
vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> result;
    vector<int> path;
    getPaths(result, path, root, sum);
    return result;
}

void getPaths(vector<vector<int>>& result, vector<int> path, TreeNode* root, int sum) {
    if (!root)
        return;
    path.push_back(root->val);
    if (!root->left && !root->right && sum == root->val) {
        result.push_back(path);
        return;
    }
    
    getPaths(result, path, root->left, sum - root->val);
    getPaths(result, path, root->right, sum - root->val);
}
```

114. 把二叉树扁平成列表
------

```C++
TreeNode* prev;
void flatten(TreeNode* root) {
    if (!root) return;
    flatten(root->right);
    flatten(root->left);
    root->right = prev;
    root->left = NULL;
    prev = root; // last flattened element
}
```

115. 买卖股票最佳时机，只能交易一次
------

```C
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize < 2) return 0;
    int profit = 0;
    int min = prices[0];
    // 从前到后依次遍历，如果有更好的收益更新，或者更新 min，限制条件是先出现最小值
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] > min) {
            if (prices[i] - min > profit)
                profit = prices[i] - min;
        } else {
            min = prices[i];
        }
    }
    return profit;
}
```

134. 加油站
------

```C
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int total = 0;
    int j = -1;
    
    for (int i = 0, sum = 0; i < gasSize; ++i) {
        sum += gas[i] - cost[i]; // 从此处经过能够净增多少汽油
        total += gas[i] - cost[i]; // 记录总的汽油量是否是正的
        if (sum < 0) { // 如果当前汽油量已经小于 0，说明之前的节点都是不行的，到下一个节点
            j = i;
            sum = 0; // 同时重新开始计数
        }
    }
    
    return total >= 0 ? j + 1 : -1;
}
```



136. 找出数组中只出现一次的数字
------

```C
int singleNumber(int* nums, int numsSize) {
    int result = nums[0];
    for (int i = 1; i < numsSize; i++)
        result ^= nums[i];
    return result;
}
```

139. 查找单词是否能组成句子
------

```C++
bool wordBreak(string s, unordered_set<string>& wordDict) {
    if (wordDict.empty()) return false;
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    // 动态规划，假设前 i 个字符已经匹配到了，尝试匹配 i 到 i+j，如果找到了，就匹配到了 i+j
    for (int i = 1; i <= s.size(); i++) {
        for (int j = i-1; j >= 0; j--) {
            if (dp[j]) {
                string word = s.substr(j, i-j);
                if (wordDict.find(word) != wordDict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    return dp[s.size()];
}
```

141. 列表是否有环
------

```C
bool hasCycle(struct ListNode *head) {
    struct ListNode* slow = head, * fast = head;
    while (fast && fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast)
            return true;
    }
    return false;
}
```

142. 列表是否有环？如果有找到环的开始
------

```C
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode* slow = head, * fast = head, *entry = NULL;
    int counter = 0;
    bool found = false;
    while (!found && fast && fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
        counter++;
        if (slow == fast)
            found = true;
    }
    
    if (!found) return NULL;
    
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}
```

143. 前序遍历
------

```C++
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        TreeNode* node  = stk.top();
        stk.pop();
        result.push_back(node->val);
        if (node->right)
            stk.push(node->right);
        if (node->left)
            stk.push(node->left);
        
    }
    
    return result;
        
}
```

144. 在旋转数组中查找最小值，可能有重复
------

```C
int findMin(int* A, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (A[mid] > A[right]) { // 当需要找的是 left，也就是较小的数字，使用 right 比较不需要等于号
            left = mid + 1;
        } else if (A[right] < A[mid]) {
            right = mid;
        } else {
            right--;
        }
    }
    return A[left];
}
```







155. 设计一个栈，在普通栈的基础上支持 getmin 操作
------

题目的要求是在O(1)时间内实现 getmin，使用另一个栈存储每个元素对应的最小值即可。
注意使用一个和原有栈大小相同的栈是浪费空间的，待更新！

```C++
class MinStack {
private:
    stack<int> m_stk;
    stack<int> m_min;
public:
    void push(int x) {
        m_min.push(m_stk.empty() ? x : min(x, m_min.top()));
        m_stk.push(x);
    }

    void pop() {
        m_min.pop();
        m_stk.pop();
    }

    int top() {
        return m_stk.top();
    }

    int getMin() {
        return m_min.top();
    }
};
```

156-159 Locked
------

160. 求两个链表的交叉点
------

分析题目可知，如果有一个交叉点，那么在这之后的所有点都是交叉的。这里有一个非常巧妙
的做法。使用两个指针，如果到达结尾就指向另一个链表，会产生一下三种情况：

1. 如果交叉点前面的节点数目相同，显然会返回正确节点。
2. 如果不同假设 A 的节点为 a + c，B 的节点为 b + c，则在下一次遍历时：
    a + c + b == b + c + a，恰好到达相同部分的第一个顶点 C1
3. 如果两个列表不相交，那么经过 a + b, b + a距离后，恰好都等于 NULL

```C
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (!headA || !headB) return NULL;
    struct ListNode *p1 = headA, *p2=headB;
    while (p1 != p2) {
        // 两个列表手尾相接，如果有一个点相同，一定会返回
        // a + c + b == b + c + a   --> C1
        // a + b == b + a    --> NULL
        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;
    }
    
    return p1;
}
```

161. Locked
------

162.  找到极大值，给定一个数组，可能有多个极大值，找到任意一个即可，给定数组中A[i] != A[i+1]
------

题目要求在对数时间内做出来，二分搜索，如果中间的数在左半部分，就向右找。

```C
int findPeakElement(int* nums, int numsSize) {
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[mid + 1]) // mid in left part of summit
            left = mid + 1;
        else                           // mid in right part of summit
            right= mid;
    }
    return left;
}
```

166. 分数生成小数
------

```C++
string fractionToDecimal(long numerator, long denominator) {
    if (numerator == 0) return "0";
    string result;
    
    // 符号
    if (numerator < 0 ^ denominator < 0)
        result += "-";
    long n = abs(numerator), d = abs(denominator);
    
    // 整数部分
    result += to_string(n / d);
    if (n % d == 0) return result;
    
    // 小数部分
    result+= ".";
    unordered_map<int, int> map;
    for (long r = n % d; r != 0; r %= d) { // 模拟手工除法
        if (map.count(r) > 0) {
            result.insert(map[r], 1, '(');
            result += ")";
            break;
        }
        
        map[r] = result.size(); // 记录对应的位置，以便插入括号
        r *= 10; // 从上借位
        result += to_string(r / d);
    }
    return result;
}
```





168. 生成 Excel 表格标题
------

注意 A 对应的是1而不是0

```C++
string convertToTitle(int n) {
    string title;
    while (n) {
        char c = (n-1) % 26 + 'A';
        n = (n-1) / 26;
        title = c + title;
    }
    return title;
}
```

169. 给定一个数组，有一个数字的出现频率超过了一半，找出这个数字
------

非常经典的一道题，首先我们假设拿到的数字就是目标，并记录他出现的次数，如果下一个
数字和他不一样，那么我们减一，当次数为0的时候，我们知道这个数字在已经便利过的数字
中出现小于一半了，这时候我们换下一个数字，最后剩下的一定是超过一半的数字。

```C
int majorityElement(int* nums, int numsSize) {
    int candidate = nums[0];
    int times = 1;
    for (int i = 1; i < numsSize; i++) {
        if (times == 0) {
            candidate = nums[i];
            times++;
        } else {
            if (nums[i] == candidate)
                times++;
            else
                times--;
        }
    }
    return candidate;
}
```

170. Locked
------

171. Excel 标题转换为数字
------

同样，我们需要注意 A 对应的是1，而不是0

```C
int titleToNumber(char* s) {
    int result = 0;
    while (*s)
        result = result * 26 + *s++ - 'A' + 1;
    return result;
}
```

172. 阶乘中能有几个0
------

```C
int trailingZeroes(int n) {
    int fives = 0;
    while (n) {
        fives += n / 5;
        n /= 5;
    }
    return fives;
}
```

173. 二叉树中序遍历迭代器
------

```C
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !m_stack.empty();
        
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* temp = m_stack.top();
        m_stack.pop();
        pushAll(temp->right);
        return temp->val;
    }
    
private:
    stack<TreeNode*> m_stack;
    void pushAll(TreeNode* root) {
        while (root) {
            m_stack.push(root);
            root = root->left;
        }
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
```

174. 地下城游戏
------

王子在格子的左上角，需要到右下角去救公主，在过程中王子不能死掉

```C++
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int row = dungeon.size();
    int col = dungeon[0].size();
    vector<vector<int>> bloods(row + 1, vector<int> (col + 1, INT_MAX));
    bloods[row][col-1] = bloods[row-1][col] = 1;
    for (int i = row-1; i >= 0; i--) {
        for (int j = col-1; j >= 0; j--) {
             int need = min(bloods[i+1][j], bloods[i][j+1]) - dungeon[i][j];
             bloods[i][j] = need > 0 ? need : 1;
        }
    }
    return bloods[0][0];
}
```

179. 最大的数字
------

神奇的排序方法

```C++
string largestNumber(vector<int>& nums) {
    vector<string> num_strings(nums.size());
    for (int i = 0; i < nums.size(); i++)
        num_strings[i] = to_string(nums[i]);
    auto comparator = [] (string& s1, string& s2) {
        return s1 + s2 > s2 + s1;
    };
    sort(num_strings.begin(), num_strings.end(), comparator);
    string result;
    for (auto& num_string: num_strings)
        result += num_string;
    int start = result.find_first_not_of("0");
    if (start == string::npos) return "0";
    return result.substr(start, result.size() - start);
}
```

翻转树组

```C
void reverse(int* nums, int left, int right) {
    while (left < right) {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        left++;
        right--;
    }

}

void rotate(int* nums, int numsSize, int k) {
    if (k >= numsSize) k %= numsSize;
    if (k <= 0) return;
    reverse(nums, 0, numsSize - k - 1);
    reverse(nums, numsSize - k, numsSize - 1);
    reverse(nums, 0, numsSize - 1);
}
```





196. 翻转二进制表示
------


```C
uint32_t reverseBits(uint32_t n) {
    uint32_t r = 0;
    int len = sizeof(n) * 8 - 1;
    while (len--) { // 31 times shift
        r |= n & 0x1;
        n >>= 1;
        r <<= 1; // only shift 31 times
    }
    
    r |= n & 0x1;
    return r;
}
```

197. 数字二进制表示中1的个数
------

我们知道n&(n-1)会把 n 中的最后一个1去掉，所以循环直到 n 为0即可

```C
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}
```

198.  有一排房子，每个房子中都有一定财产，但是不能偷相邻的两个房子，求能偷到的最大值
------

使用 DP，对于每个房子，可以选择不偷或者前 i-1个房子加上偷当前房子，即`dp[i+1]
= max(dp[i], dp[i-1] + A[i])`

```C
int rob(int* nums, int numsSize) {
    if (!nums) return 0;
    // 因为不能相邻，所以可以从相隔一个的取值
    // dp[n] = max(dp[n-1], dp[n-2] + A[n])
    int temp, m = 0, n = nums[0];
    for (int i = 1; i < numsSize; i++) {
        temp = n;
        if (m + nums[i] > n)
            n = m + nums[i];
        m = temp;
    }
    return n;
}
```

231. 2的次方
------

```
bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0;
}
```

H-Index
------

```
int hIndex(int* cites, int n) {
    int* hs = malloc(sizeof(int) * n + 1);
    for (int i = 0; i < n + 1; i++)
        hs[i] = 0;
    for (int i = 0; i < n; i++) {
        if (cites[i] > n)
            hs[n]++;
        else
            hs[cites[i]]++;
    }
    
    for (int i = n, papers = 0; i >= 0; i--) {
        papers += hs[i];
        if (papers >= i)
            return i;
    }
    
    return 0;
}
```


