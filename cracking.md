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

1.5 压缩字符串 `aabcccccaaa -> a2b1c5a3`如果压缩后变短，返回压缩后的字符串
------

首先要计算出新的长度，然后比较是否变短，如果变短，则执行压缩，否则返回

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
------

这实际上是一道OOD(面向对象设计)的题目

3.4 汉诺塔
------

经典问题了，考虑 n＝2的时候，把上面1块放到中间，然后把下面一块移动完成。那么对于n，我们把n-1块移到中间即可

```
void moveDisks(int n, tower_t origin, tower_t dest, tower_t buffer) {
    if (n <= 0) return;

    moveDisks(n-1, origin, buffer, dest); // 先把上面的n-1块放到中间
    moveBottom(origin, dest) // 把最底下的盘子直接放过去
    moveDisks(n-1, buffer, dest, origin) // 把中间的再放到最后

}
```

3.5 使用两个栈模拟一个队列
------

LeetCode 232

3.6 对栈进行排序，额外的数据只能使用栈
------

使用简单插入排序，在一个新的栈中保存排序好的数据，从unsorted中弹出以后，不断弹出sorted为新元素找到正确位置

```C
stack<int> sortStack(const stack<int>& unsorted) {
    stack<int> sorted;
    while (!unsorted.empty()) {
        int temp = unsorted.top(); // 待插入的新元素
        unsorted.pop();
        while (!sorted.empty() && sorted.top() > temp) { // 不断弹出，找到合适位置
            int big = sorted.top(); sorted.pop();
            unsorted.push(big);
        }
        sorted.push(temp); // 插入新元素
    }
    return sorted;
}
```

3.7 题目咩看懂
------

4.1 检查二叉树是否平衡: 任意两个节点之间的高度差不超过1
------

LeetCode 110

4.2 给定一个有向图，找出两个节点之间是否存在一条路径
------

> 碰到这类问题，有必要和面试官探讨一下DFS和BFS之间的利弊，例如，DFS实现起来比较简单，只需要简单的递归即可。BFS适合用来查找最短路径。
> 而DFS在访问临近借点之前可能会深度便利其中一个临近节点

🌲的遍历一定要注意visited数组或者集合，因为树中可能有几个节点指向同一个节点

```C++
bool search(Graph* graph, Node* start, Node* end) {
    queue<Node*> q;
    unordered_set<Node*> visited;

    q.push(start);
    while(!q.empty()) {
        auto node = q.pop();

        for (auto adj : q.adjs())
            if (visited.find(adj) == visited.end())
                if (adj == end)
                   return true;
                else
                    q.push(adj);
    }

    return false;
}

4.3 给定一个有序数组，元素各不相同且按升序排列，创建一颗高度最小的二叉查找树
------

LeetCode 108

4.4 给定一棵二叉树，创建层序访问的链表
------

LeetCode 102

4.5 检查一棵二叉树是否为二叉查找树
------

LeetCode 98

4.6 找到二叉查找树指定节点的下一个节点(中序后继)，假设每个节点都有指向父节点的指针
------

LeetCode 238, but locked

按照中序遍历，左子树，当前节点，右子树，显然下一个节点应该在右边。也就是右子树中最左边的节点。
考虑没有右子树的情况，如果当前节点是左子节点，下一个节点应该是父节点。如果是右节点，我们继续向上，如果到达了root，显然没有更多节点了。

对于树这种可以分情况的最好先把各种情况想好了，在写代码。

```C++
TreeNode* inorderSucc(TreeNode* n) {
    if (!n) return NULL;
    if (n->right) {
        TreeNode* right = n->right;
        while (right->left)
            right = right->left;
        return right;
    } else {
        TreeNode* q = n, * parent = q.parent;
        while (parent && parent->left != q) { // 找到当前节点可以作为左子节点的父节点
            q = parent;
            parent = parent->parent;
        }
        return parent;
    }
}
```

4.7 查找二叉树的公共祖先
------

LeetCode 236

4.8 又两棵非常大的二叉树：T1 有几百万个节点，T2，有几百个节点。判断T2是否是T1的子树
------

这道题并没有标准解法。值得和面试官探讨，详见树上的讲解（161页）。

4.9 打印节点数值总和为给定值的路径，路径可以从任意节点开始，任意节点结束
------

对于一个没有见过的问题，可以先简化，然后在推广。假设路径必须从root开始，那很简单。
如果路径可以从任意节点开始，那么我们需要向上检查是否得到了相符的总和，而不能假定root是起点

```C
void findSum(TreeNode* root, int sum) {
    int depth = depth(root);
    vector<int> path(depth);
    findSum(root, sum, path, 0);
}

void depth(TreeNode* root) {
    if (!root) return 0;
    return max(depth(root->left), depth(root->right)) + 1;
}

void findSum(TreeNode* root, int sum, vector<int> path, int level) {
    if (!root)
        return;

    path[level] = root->val;
    for (int i = level, t= 0; i >= 0; i--) {
        t += path[i];
        if (t == sum)
            print(path, i ,level); // printing out path from i to level
    }

    findSum(root->left, sum, path, level + 1);
    findSum(root->right, sum, path, level + 1);
}
```

5.1 给定一个数n，和另一个数字m，然后给定区间(i, j)，区间保证可以大于m的二进制长度，把m的二进制表示插入到n的区间内
------

示例：n=100/000/00, m = 101, i = 2, j = 4 -> 100/101/00

1. 把n中对应位置清零
2. 把m移动到对应的位置
3. 合并

```C
int merge(int n, int m, int i, int j) {
    int left_mask = ~0 << (j+1);
    int right_mask = (1 << i) - 1
    int mask = left_mask | right_mask;

    n &= mask;
    m <<= i;

    return n | m;
}
```

5.2 给定一个0和1之间的实数，打印他的二进制表示，如果32位以内无法表示，打印error
------

我们知道 (0.101)2 = 1 * 2^-1 + 0 * 2^-2 + 1 * 2^-3，我们只要让这个数字不断的乘2，然后看它是否大于1，然后就可以得到第一位是不是1了

```C++
string printBinary(double num) {
    if (num >= 1 || num <= 0)
        return "error";

    string result;
    result += ".";
    while (num > 0) {
        if (result.size() >= 32)
            return "error";
        num *= 2;
        if (num >= 1) {
            result += "1";
            num -= 1;
        } else {
            result += "0";
        }
    }

    return result;
}
```

5.3 给定一个正整数，找出和其二进制表示中一的数字相同的数字，并且最接近，一共两个
------

我们需要把某个0反转为1，把某个1反转为0。
0 -> 1在1->0 左边，数字变大，在右边数字变小。
如果想变大，反转的0需要在1的左边。

把p位置1；把0到p之间请0；在添加ending1 - 1个1。

```C
int getNext(int n) {
    int c = n, ending0 = 0, ending1 = 0;
    while ((c & 1 == 0) && c != 0) {
        ending0++;
        c >>= 1;
    }

    while (c & 1) {
        ending1++;
        c >>= 1;
    }

    return n + (1 << ending0) + (1 << (ending1 - 1)) - 1;
}
```

把位p值0；把位p右边的位值1，再把0到ending0-1置0
```C
int getPrev(int n) {
    int c = n, ending0 = 0, ending1 = 0;
    while (c & 1) {
        ending1++;
        c >>= 1;
    }
    if (c == 0) return -1;
    while ((c & 1) == 0 && c != 0) {
        ending0++;
        c >>= 1;
    }
    return n - (1 << ending1) - (1 << (ending0 - 1)) + 1;
}
```

5.4 解释`n & (n-10) == 0`
------

LeetCode 231

5.5 A和B之间有多少位不相同/需要改变多少位，才能把A变成B
------

使用XOR找出不同的位，然后统计1的个位数。需要注意的是不同的题目

```C
int bitSwapRequired(int a, int b) {
    int diff = a ^ b, count = 0;
    while (diff) {
        diff &= diff - 1;
        count++;
    }
    return count;
}
```

5.6 交换一个整数的奇数位和偶数位
------

这道题很有趣，选取特殊的掩码即可

```C
// 考虑32bit int
int32_t swapBits(int32_t x) {
    int32_t odd_bits = x & 0xAAAAAAAA; // 0xAA as 10101010
    int32_t even_bits = x & 0x55555555; // 0x55 as 01010101
    return (odd_bits >> 1) | (even_bits << 1);
}
```

5.7 没看懂题目
------

5.8 单色屏幕存贮在一维字节数组中，每个字节存储八个像素，屏幕宽度为w px，绘制从x1到达x2的水平线
------

显然可以逐bit设定，然而这样是拿不到offer的。更好的做法是逐字节设定。

```C
void drawHorizentalLine(uint8_t * screen, int width, int x1, int x2, int y) {

    int start_offset = x1 % 8;
    int start_full_byte = x1 / 8; // x1 所在字节
    if (start_offset != 0)
        start_full_byte++;

    int end_offset = x2 % 8;
    int end_full_byte = x2 / 8; // x2 所在字节
    if (end_offset != 7)
        end_full_byte--;

    // 逐字节设定
    for (int i = start_full_byte; i <= end_full_byte; i++)
        screen[width / 8 * y + i] = (uint8_t)0xff;

    uint8_t start_mask = (uint8_t) (0xff >> start_offset);
    uint8_t end_mast = (uint8_t) ~(0xff >> end_offset + 1);

    if ((x1 / 8) == (x2 / 8)) {
        uint8_t mask = (uint8_t)(start_mask & end_mask);
        screen[(width / 8) * y + x1 / 8] |= mask;
    } else {
        if (start_offset != 0) {
            int byte_number = (width / 8) * y + start_full_byte - 1;
            screen[byte_number] |= start_mask;
        }
        if (end_offset != 7) {
            int byte_number = (width / 8) * y + end_full_byte + 1;
            screen[byte_number] |= end_mask;
        }
    }

```

6.1 - 6.6 智力题
------

见OneNote笔记

7.3 给定直角坐标系的两条线，确定他们会不会相交
------

我们知道在二维平面上两条线的关系不外乎：平行，相交，重合。问题是两条线重合算不算相交呢，需要问清楚。
对于两条线如何表示，这又是面向对象设计的问题，需要讨论。

```C++
class Line {
private:
    static double EPSILON;
    double m_slope; // 斜率
    double m_y_intercept; // y轴交点

public:
    Line(double s, double y): m_slope(s), m_y_intercept(y) {};
    // 重合视作相交
    bool intersect(const Line& other) {
        return abs(slope() - other.slope()) > EPSILON || // 斜率不同
            abs(y_intercept() - other.y_intercept()) < EPSILON; // y轴交点相同
    }
    double slope() {return m_slope;}
    double y_intercept() {return m_y_intercept;}
};

double Line::EPSILON = 0.00001;
```

遇到这类问题，务必：

1. 多问，面试官可能故意模糊问题
2. 仔细设计数据结构，权衡利弊，和面试官讨论
3. 千万不要用＝＝判定浮点数

7.4 只使用加号实现减法和乘除法
------

```C
int neg(int a) {
    int result = 0;
    int d = a < 0 ? 1 : -1;
    while (a) {
        result += d;
        a += d;
    }
    return result;
}

int abs(int a) {
    return a > 0 ? a : neg(a);
}

int minus(int a, int b) {
    return a + neg(b);
}

int multiply(int a, int b) {
    int sign = (a > 0) == (b > 0) ? 1 : -1;
    a = abs(a);
    b = abs(b);
    int result = 0;
    while (b--)
        result += a;
    return sign == 1 ? result : neg(result);
}

int devide(int a, int b) {
    // see leetcode
}
```

7.7 找出第k个丑数
------

LeetCode 264

8.x OOD, see OneNote
------

9.1 小孩上楼梯，楼梯有n阶，小孩可以一次上1，2，3步，请问一共有多少种方法
------

 注意如果只能1或2就是斐波那契数列。

```C++
// 递归
int countSteps(int n) {
    static vector<int> steps(1000, 1);
    if (n < 0)
        return 0;
    if (n > 1 && steps[n] == 1)
        steps[n] = countSteps(n -1) + countSteps(n - 2) + countSteps(n - 3);
    return steps[n];
}
```

```C
// 迭代
int countSteps(int n) {
    int n3 = 1; // starts from n = 0
    int n2 = 1; // starts from n = 1
    int n1 = 2; // starts from n = 2

    if (n < 0)
        return 0;
    if (n == 0 || n == 1)
        return 1;
    int steps = 0;
    for (int i = 3; i <= n; i++) {
        steps = n3 + n2 + n1;
        n3 = n2;
        n2 = n1;
        n1 = steps;
    }
    return steps;
}
```

9.2 设计一种算法，机器人只能向右向下移动，从(0, 0)移动到(x, y)有几种走法
------

LeetCode 62 63

9.3 在有序数组A[0...n-1]中存在A[i] == i，找出该数字。如果存在重复值，又该如何做
------

```C
int magic(int* A, n) {
    int left = 0; right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == mid)
            return mid;
        else if (A[mid] < mid)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
```

9.4 返回一个集合的所有子集
------

LeetCode 78

9.5 全排列
------

LeetCode

9.6 生成n对括号的全部有效集合
------

LeetCode

9.7 实现填充颜色功能
------

```C++
void paintFill(vector<vector<int>> screen, int x, int y, int color) {
    if (screen[y][x] == color)
        return;
    paintFill(screen, int x, int y, screen[y][x], int color);
}

void paintFill(vector<vector<int>> screen, int x, int y, int start, int color) {
    if (x < 0 || x >= screen[0].size() || y < 0 || y >= screen.size())
        return;
    if (screen[y][x] == start) {
        screen[y][x] == color;
        paintFill(screen, int x-1, int y, start, color);
        paintFill(screen, x+1, y, start, color);
        paintFill(screen, x, y+1, start, color);
        paintFill(screen, x, y-1, start, color);
    }
}
```

9.8 给定数量不限的硬币，编写代码计算有几种表示方法
------

```C
vector<int> makeChange(vector<int> coins, int target) {
    vector<vector<int>> result;
    vector<int> solution(coins.size(), 0)
    make(result, coins, solution, 0, target);
    return result; 
}

void make(vector<vector<int>>& result, vector<int>& coins, vector<int> solution, int start, int target) {
    if (target <= 0 || start >= coins.size()) {
        if (target == 0)
            result.push_back(solution);
        return;
    }
    for (int i = 0; i *coins[start] < target ; i++) {
        solution[start] = i;
        make(result, coins, solution, start + 1, target - i * coins[start]);
}
}

```

9.9 N-Queen问题
------

LeetCode

9.10 给你一堆箱子，上面的箱子的长宽高要求小于下面的箱子，实现一个方法，搭出最高的箱子
------

注意缓存结果

9.11 添加括号，使得结果成立
------

LeetCode

10.x 系统设计题
------

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

12.x 测试

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
```

13.9 编写malloc_aligned

13.10 malloc2d函数，分配二维数组，返回int**可以通过a[i][j]访问，并且尽量少调用malloc
------
    
前面rows大小的区域用作存储指针，后面存储数据。

    hhh|ddddd|ddddd|ddddd

```C
void** malloc2d(int rows, int cols) {
    int header = rows * sizeof(void*);
    void** ptr = (void**)malloc(header + rows * cols);
    if (!ptr)
        return NULL;
    void* buf = (void*)(rawptr + rows);
    for (int i = 0; i < rows; i++)
         ptr[i] = buf + i * cols;
    return ptr;
}

void free2d(void** ptr) {
    void* p = void* p;
    free(p);
}

13.x C++ 14.x JAVA 15.x SQL
------

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
值得注意的是，因为使用异或不考虑变量的实际类型，只是粗暴地按 bit 位交换，因此适用于各种类型。不过值得注意的是千万不要用这种方法去交换变量的值，当x==y的时候会有灾难性后果。

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

18.1 实现加法
------

显然是使用位运算。

```
int add(int a, int b) {
    while (b) {
        int sum = a ^ b;
        int carry = (a & b) << 1;
        a = sum, b = carry;
    }
    return a;
}
```

18.2 完美洗牌，使得一副牌中任意一种排列出现的概率都相等
------

显然全排列是n!个，那么我们保证每一个全排列都可能出现就好了。

```C
void shuffle(int* A, int n) {
    for (int i = 0; i < n; i++) {
        int k = rand(i);
        swap(A[k], A[i]);
    }
}
```

18.3 从n个数组中选出m个，要求被选中概率一样
------

```C
vector<int> pink_k(vector<int> nums, int k) {
    vector<int> result(k);

}
```

18.4 小于 n 的数字中出现2的个数
------

LeetCode 

