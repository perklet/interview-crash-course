#ifndef UNION_FIND_H
#define UNION_FIND_H

/**
 * http://www.cnblogs.com/cherish_yimi/archive/2009/10/11/1580839.html
 */
typedef struct union_find {
    int* father;
    int* rank;
    int* capacity;
} UnionFind;

/**
 * Create a union find
 */
struct union_find* create_unionfind(int capacity) {
    struct union_find* uf = malloc(sizeof(struct union_find));
    uf->capacity = capacity;
    uf->father = malloc(sizeof(int) * capacity);
    uf->rank = malloc(sizeof(int) * capacity);
    for (int i = 0; i < capacity; i++)
        uf->father[i] = uf->rank[i] = 0;

    return uf;
}

/**
 * 初始化一个集合，根指向自己
 */
int make_set(struct union_find* uf, int x) {
    if (x >= uf->capacity) return -1;
    uf->father[x] = x;
    uf->rank[x] = 0;
    return 0;
}

/**
 * 查找所在集合，也就是根节点
 */
int find_set(struct union_find* uf, int x) {
    if (x >= capacity) return -1;
    if (x != uf->father[x])
        uf->father[x] = find_set(uf, uf->father[x]); // 回溯时更新路径上所有节点，指向根节点
    return uf->father[x];
}

/**
 * 合并x, y所在的两个集合
 */
void unionify(struct union_find* uf, int x, int y) {
    x = find_set(uf, x);
    y = find_set(uf, y);

    if (x == y) return;

    // 秩大的作为根
    if (uf->rank[x] > uf->rank[y]) {
        uf->father[y] = x;
    } else {
        if (rank[x] == rank[y]) 
            uf->rank[y]++;
        uf->father[x] = y;
    }
}

#endif
