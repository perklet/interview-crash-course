Cracking the code interview in C/C++
======

1.1 确定一个字符串中所有数字是否完全不同
------

首先应该询问面试官字符集的大小，是ASCII还是Unicode还是GBK，对于ASCII和GBK，
因为字符集大小有限，而且都不太大，可以使用一个数组统计，而对于Unicode，
显然只能使用Hash统计

```C++
bool isUniqueChars(const string& s) {
    if (s.size() > 256) return false;

    vector<bool> charSet(256);
    for (auto c : s)
        if (charSet[s])
            return false;
        else
            charSet[c] = true;
    return true;
}
```

注意：还可以使用位向量提高效率，但是C++的vector<bool>本身就是特质化的。

1.2 实现reverse(char* s)
------

```C
void reverse(char* s) {
    if (!s) return;
    char* end = s;
    while (*end++) ;
    end--; // back one

    while (s < end) {
        char t = *s;
        *s++ = *end;
        *end-- = t;
    }
}
```

1.3 判断两个词是否是变位词(Anagram)
------

LeetCode 242

1.4 编写一个方法，将字符串中的空格全部替换为`%20`，假设字符串结尾有足够空间
------

对于数组操作的好多题目，尝试从尾部做起一下子就简单多了。

```C
void replaceSpaces(char* s, int len) {
    int spaceCount = 0, newLength = 0;

    for (int i = 0; i < len; i++)
        if (isspace(s[i]))
            newLength++;

    newLength = len + spaceCount * 2;
    s[newLength] = '\0';

    for (int i = len - 1; i >= 0; i--) {
        if (isspace(s[i])) {
            s[--newLength] = '0';
            s[--newLength] = '2';
            s[--newLength] = '%';
        } else {
            s[--newLength] = s[i];
        }
    }
}
```

1.5 Pass
------

1.6 给定一幅由N＊N矩阵表示的图像，顺时针旋转90度
------

LeetCode 48

1.7 若m＊n矩阵中某个元素为0，就把这一行和这一列都清零
------

LeetCode 73 注意同样可以使用位向量提高效率

1.8 给定方法isSubstring()，判断s1是不是可以由s2旋转组成
------

假设s1 = xy, s2 = yx，yx一定是xyxy的字串，而且是中间部分。注意先判断长度，提高效率

```C++
bool isRotation(string& s1, string& s2) {
    if (s1.size() != s2.size())
        return false;

    string s1s1 = s1 + s1;
    return isSubstring(s1s1, s2);
}
```

2.1 移除未排序列表中的重复节点
------

因为是无序的，所以我们还是需要记录重复节点

```C++
// 显然第一个节点是不可能被移除的，所以不用返回新的头部
void removeDuplicates(ListNode* head) {
    unordered_set<int> vals;
    ListNode dummy, *p = dummy;
    dummy.next = head;
    while (p->next) {
        if (vals.find(p->next->val) != vals.end())
            ListNode* next = p->next;
            p->next = next->next;
            free(next);
        } else {
            vals.insert(p->next->val);
        }
    }
}
```

如果不允许使用额外空间，那么这个功能至少需要O(N^2)实现

2.2 实现一个算法，找出链表中倒数第K个元素
------

LeetCode 19 注意K是非法的情况

2.3 删除单向链表中的某个节点，假设你只有访问该节点的权限
------

LeetCode 237

2.4 以给定的值x分割列表，使得小于x的元素都排在x的前面
------

LeetCode 83

2.5 给定一个链表，每个链表节点存放一位数字，并且是反向存放的，求两个链表的和
------

LeetCode 2

如果是正向存放的呢？

先求出两个列表的长度，然后用零填充一个较短的链表，然后在从前往后相加。

2.6 给定一个有环链表，找到环的开头
------

LeetCode 141 142

2.7 判断链表是否是回文(Palindrome)
------

LeetCode 234

3.1 如何用一个数组实现3个栈
------

如果是实现两个堆栈，可以把两头作为栈底，向中间生长。

解法1: 固定分割，显然这样是不能让面试官满意的。。

解法2: 弹性分割，并把数组看成是环状的！


3.2 设计一个栈，支持min方法，返回栈中的最小值
------

LeetCode 155

3.3 实现SetOfStacks，由多个栈组成

11.1 合并两个有序数组
------

LeetCode 88

11.2 对一个字符串数组排序，把变位词(Anagram)放在一起
------

LeetCode 49

11.3 在已经被旋转过的排序数组中，查找元素
------

LeetCode 81

11.4 有一个20GB的文件，每行一个字符串，如何排序
------

20GB暗示无法放入内存中，把文件分块后，分别载入内存中，采用归并排序

11.5 

13.1 使用 C++ 写个方法，打印输入文件的最后 K 行
------

使用循环数组，容量设为 K，同时记录当前的最早元素

```C++
void printLastKLines(char* filename) {
    const int K = 10;
    ifstream file(filename);
    string lines[K];
    int size = 0;

    while (file.good())
        getline(file, lines[size++ % K];

    int start = size > K ? (size % K) : 0;
    int count = min(K, size);

    for (int i = 0; i < count; i++) 
        cout << lines[(start + i) % K] << endl;
}
`

17.1 不用中间变量，直接交换两个数字
------

想像把 a 和 b 都放在数轴上，假设 a0，b0分别是初值，那么有 diff = a - b。我们把
diff 保存在 a 中，然后 b = b0 + diff 也就是 a0 ，而再另 a = b - diff，也就是 b0。

```C++
void swap(int& a, int& b) {
    a = a - b;
    b = b + a;
    a = b - a;
}
```

更巧妙的是，我们还可以使用异或 XOR 在解。假设 a = a0 ^ b0，那么 b = a ^ b0 = a0 ^ b0 ^ b0 = a0，然后 a = a ^ b = a0 ^ b0 ^ a0 = b0。完美解决！
值得注意的是，因为使用异或不考虑变量的实际类型，只是粗暴地按 bit 位交换，因此适用于各种类型

```C++
template<typename T>
void swap(T& a, T& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}
```

17.2 判断玩家是否赢了井字棋游戏
------

Fuck， 什么是井字棋。。。


17.3 n! 结尾有多少个零
------

LeetCode 172

17.4 找出两个数字中较大的一个，但不得使用判断语句
------

判断a>b就是判断a-b的正负号，显然我们可以使用bit运算

```C++
int flip(int a) { // flip last bit
    return 1 ^ a;
}

int sign(int a) {
    return flip((a >> 31) & 0x1);
}

int get

17.7 把数字转换为英文单词
------

LeetCode 
注意Cracking上的解法并不是最精妙的。

17.7a 把数字转换为汉语句子
------

思路应该差不多

17.8 数组最大序列和
------

LeetCode 53

17.9 


17.11 给定产生数字概率相同的rand5()，实现一个方法rand7()，要求产生每个数字的概率相同
------

扩大rand5产生随机数的范围，然后对舍去一定范围的数字，对剩下的数字取模，虽然这样会导致调用次数不固定，但实现了效果
对于randx，扩大范围的方法是 x * randx() + randx()

```C
int rand7() {
    while (1) {
        int num = 5 * rand5() + rand5();
        if (num < 21)
            return num % 7;
    }
}
```

该问题可以拓展到对于 x < y，由randx() 构造 randy()

17.12 在数组中找到两个数字，是的他们的和为指定的数字
------

LeetCode 1

17.13 把二叉树转化为双向链表
------

先把二叉树变成一个环形链表，然后再从头部解开即可

```C

void concat(struct tree_node* x, struct tree_node* y) {
    x->right = y;
    y->left = x;
}

struct tree_node* convert_circular(struct tree_node* root) {
    if (!root)
        return NULL;
    struct tree_node* left = convert_circular(root->left);
    struct tree_node* right = convert_circular(root->right);

    if (!left && !right) {
        root->left = root;
        root->right = root;
        return root;
    }

    struct tree_node* tail_right = right ? right->left : NULL;

    // 把左边添加到根部
    if (!left)
        concat(right->left, root);
    else
        concat(left->left, root);

    // 把右边添加到根部
    if (!right)
        concat(root, left);
    else
        concat(root, right);

    // 把右边和左边链接
    if (left && right)
        concat(tail_right, left);

    return left ? left : root;
}

struct tree_node* convert(struct tree_node* root) {
    struct tree_node* head = convert_circular(root);
    head->left->right = NULL;
    head->left = NULL;
    return head;
}
```


