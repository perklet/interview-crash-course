Beauty of Programming
======

2.1 LeetCode
2.2 LeetCode
2.3 LeetCode 1/4 如何解？
2.4 LeetCode
*2.5 看下讲解
2.6 LeetCode

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

拓展问题，如果是前三项相加的数列呢






2.10 稍微看下
2.11 最近点对问题
------


2.12 LeetCode
2.13 LeetCode
2.14 LeetCode
2.15 看下讲解
2.16 LeetCode？

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
