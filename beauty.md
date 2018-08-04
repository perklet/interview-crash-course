编程之美
======

1.2 中国象棋将帅问题
------

```C
struct {
    unsigned char a:4;
    unsigned char b:4;
};

for (i.a = 1; i.a <= 9; i.a++)
    for (i.b = 1; i.b <= 9; i.b++)
        if (i.a % 3 != i.b % 3)
            printf("%u:%u", i.a, i.b);
```

1.14 连连看
------

```C
Grid* preClick = NULL, * curClick = NULL;
while(true) {
    // listen user event
    if (点击格子 xy 非空) {
        preClick = curClick;
        curClick.pos = x, y;
    }

    if (preClick && curClick && findPath(preClick, curClick)) {
        显示路径
        消去
        preClick = curClick = NULL;
    }
}
```

2.1 - 2.6 LeetCode
------

2.7 最大公约数
------

辗转相除法，如果一个数能够整除x,y，那么他也能够整除x,x%y。

```C
int gcd(int x, int y) {
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
```

```
// iterative
int gcd(int x, int y) {
    while (y) {
        int t = x;
        x = y
        y = t % y;
    }
    return x;
}

取模运算开销较大，但如下方法在y比较小时，求解次数过多，容易溢出

```C
int gcd(int x, int y) {
    if (x < y)
        return gcd(y, x);
    if (y == 0)
        return x;
    return gcd(x - y, y);
}
```

```C
int gcd(int x, int y) {
    if (x < y)
        return gcd(y, x);
    if (y == 0)
        return x;
    if (x & 0x1 == 0)
        if (y & 0x1 == 0)
            return gcd(x>>1, y>>1) << 1;
        else
            return gcd(x >>1, y);
    else
        if (y & 0x1 == 0)
            return gcd(x, y>>1);
        else
            return gcd(y, x-y);
}
```




2.8 看下讲解
------


2.9 斐波那契数列
------

使用动态规划(Memoization)的算法不在赘述O(n)。

O(logn)的解法

通项公式

    f(n), f(n-1) = (f(n-1), f(n-2)) * A

    A = |1  1|
        |1  0| 

    f(n), f(n-1) = (f(n-1), f(n-2)) * A = ... = (f1, f0) * A^(n-1)

下面我们计算`A^n-1`，太简单了，使用`A^(2n) = A^n * A^n`

```
// pesudo code
int fib(int n) {
    Matrix factor = matrixPow(A, n-1);
    return f1*factor + f0*factor;
}

Matrix matrixPow(Matrix m, int n) {
    Matrix result = Matrix::Identity;
    while (n) {
        if (n & 1)
            result *= m;
        m *= m;
        n >>= 1;
    }
    return result;
}
```

拓展问题，如果是前三项相加的数列呢，依然可以求出转移矩阵

2.11 最近点对问题
------


2.12-2.14 LeetCode 2.15 Cracking 2.16 2.17 LeetCode
------

2.18 数组分割
------

2.19 LeetCode
------

3.1 有时间可以尝试写一下
------

3.2 电话号码对应英文单词
------

递归写法

3.3 Edit Distance
------

3.4 删除链表节点
------

3.5 最短摘要的生成
------

问题转化为，在一个单词词组中，找出包含所有给定单词的最短区间。

```C++
pair<int, int> abstract(vector<string> article, unordered_set<string> keywords) {
    int start = 0, end = 0, range = INT_MAX;
    unordered_map<string, int> indecies;
    unordered_set<string> having;
    pair<int, int> result;
    while (end < article.size()) {
        while (end < article.size() && !isContain(keywords, having)) {
            indecies[articel[end]] = end;
            end++;
        }
        while (isContain(keywords, having)) {
            if (end - start + 1 < range) {
                range = end - start + 1;
                result.first = start;
                result.second = end;
            }
            if (indecies[aritcle[start]] == start)
                having.erase[article[start]];
            start++;
        }
    }
    return result;
}
```

3.6 判断两个链表是否相交
------

如果链表中有环呢？

3.7 队列中取最大值
------

使用连个minstack模拟队列

3.8 二叉树中两个节点之间的最远距离
------

显然，对一个根节点，最远距离有两种情况：

1. 左子树或者右子树中的最远距离
2. 左子树最长路径＋有子树最长路径+1

```C
typedef struct {
    int max_distance;
    int max_depth;
} result_t;

// get max distance of two nodes in a tree
result_t get_max(tree_node_t* root) {
    result_t result;
    if (!root) {
        result.max_distance = 0;
        result.max_depth = -1;
        return result;
    }

    result_t left = get_max(root->left);
    result_t right = get_max(root->right);

    result.max_depth = max(left.max_depth, right.max_depth) + 1;
    result.max_distance = max(max(left.max_distance, right.max_distance), left.max_depth + right.max_depth + 2);
    return result;
}
```

对于递归问题，书上的心得：

1. 在递归的实现中，往往假设后续的调用已经完成，在此基础上，才能实现递归的逻辑。
2. 分析清楚递归体的逻辑。
3. 考虑清楚递归退出的边界条件，也就是return的地方。

3.9 重建二叉树
------

拓展问题，如何判断前序遍历和中序遍历是合理的？

测试用例：
非完全二叉树，退化的二叉树，满二叉树，普通二叉树，空树。。。

3.10 层序遍历
------

注意把LeetCode上的ZigZag层序都看一遍。

递归的遍历需要先计算level

3.11 注意问题
------

对于询问知识点，要答得*正确*，*有条理*。最后写出来的程序已定要是*没有严重错误*，*完整*，并尝试用一些测试用例。

4.1 金刚
------

询问李博士

4.2 瓷砖覆盖地板
------

斐波那契额数列

1x2覆盖8x8？从小到大，先找出2x2有多少种，再找出4x4有多少种，再找出8x8有多少种。还有考虑好多种，注意不要有重复
pxq覆盖mxn？

4.3  Catalan数
------

4.4 点是否在三角形内部
------

给定 ABC，逆时针顺序，判断 D 是否在 ABC 内部

```
// 利用面积，如果 D 和 ABC 分别构成的三角形的面积小于 ABC 的面积，那么 D 在三角形内部
double area(Point A, Point B, Point, C) {
    double a, b, c;
    b = distance(A, C);
    a = distance(B, C);
    c = distance(A, B);

    double p = (a + b + c) / 2;
    return sqrt((p-a) * (p-b) * (p-c) * p);
}

bool isInTriangle(A, B, C, D) {
    return area(A, B, D) + area(A, C, D) + area(B, C, D) <= area(A, B, C);
} 
```

```
// 根据角度考虑，如果两个向量叉积为正，那么 P3 在P1P2的左边，如果一个点同时在 AB，BC，CA 的左边
double cross(Point A, Point B, Point X) {
    return (B.x - A.x) * (X.y - A.y) - (X.x - A.x) * (B.y - A.y);
}

bool isInTriangle(A, B, C, D) {
    return cross(A, B, D) >= 0 && cross(B, C, D) >= 0 && cross(C, A, D) >= 0;
}
```

4.5 磁带文件存储优化
------

只考虑长度，按照文件长度由短到长存放。
只考虑访问频率，按照访问频率由高到低存放。
综合考虑，按照频率/长度由高到低

4.6 桶中取黑白球
------

相当于使用 XOR，可以解任意问题

4.7 蚂蚁爬杆
------

相当于穿越

4.8 三角形测试用例
------

`int isTriangle(int a, int b, int c);`

1. 用一个字节编码各种情况。

用不同的位表示不同的结果，注意要正交

2. 测试用例

    1. 合法输入，各种三角形的形状，以及不是三角形的，还需要考虑交换不同边的顺序；

    2. 非法输入，负数，0，类型错误等等；

    3. 边界值，一般程序可能在`< <= > >=`上犯错误；

    4. 很大的数，很小的数，等等。

一般需要给出15-20个用例

4.10 数字哑谜
------

列出方程，使用深度优先搜索，注意剪枝

4.11 扫雷游戏的概率
------




