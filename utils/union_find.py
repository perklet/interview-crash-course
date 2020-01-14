class UnionFind:
    def __init__(self, count):
        self.count = count
        self.parents = list(range(count))  # 初始化时 parent 指针指向自己
        self.ranks = [1] * count  # 记录每棵树的大小

    def union(self, p, q):
        """把 p, q 两个节点连通起来"""
        p_root = self.find(p)
        q_root = self.find(q)
        if p_root == q_root:
            return
        if self.ranks[p_root] > self.ranks[q_root]:
            self.parents[q_root] = p_root
        else:
            if self.ranks[p_root] == self.ranks[q_root]:
                self.ranks[q_root] += 1
            self.parents[p_root] = q_root
        self.count -= 1

    def find(self, p):
        """找到 p 节点的根节点"""
        while self.parents[p] != p:
            # 神奇的路径压缩
            self.parents[p] = self.parents[self.parents[p]]
            p = self.parents[p]
        return p

    def is_connected(self, p, q):
        p_root = self.find(p)
        q_root = self.find(q)
        return p_root == q_root


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid or not grid[0]:
            return 0

        m = len(grid)
        n = len(grid[0])

        uf = UnionFind(m * n + 1)
        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    up = max(i - 1, 0)
                    if grid[up][j] == "1":
                        uf.union(i * n + j, up * n + j)
                    left = max(j - 1, 0)
                    if grid[i][j - 1] == "1":
                        uf.union(i * n + j, i * n + left)
                else:
                    uf.union(i * n + j, m * n)
        return uf.count - 1
