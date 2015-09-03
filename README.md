LeetCode Complete
======


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

