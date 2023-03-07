#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define N 5

/* 算法思想，找到距离当前树最近的点，然后更新每个点的最近距离。
 * 用于求解一个点到所有点的最近距离
 */ 

int* dijkstra(int G[][N], int n, int start) {

    // path sum
    int sum = 0;

    // visit table
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int cur = start;
    visited[cur] = true;

    // min dist to start point
    int* dist = malloc(sizeof(int) * n);

    // init dist table
    for (int i = 0; i < n; i++)
        dist[i] = G[cur][i];

    // for other n-1 nodes
    for (int i = 1; i < n; i++) {
        int min_cost = INT_MAX;
        int next;
        // find nearest node
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_cost) {
                min_cost = dist[j];
                next = j;
            }
        }

        // set next visited
        visited[next] = true;

        // update dist table by new element
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] > dist[next] + G[next][j])
                dist[j] = dist[next] + G[next][j];
        }
    }
}

int main() {
    int n = 5;
    int G[5][5] = {{1, 1, 1, 1, 1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1},{1,1,1,1,1}};
    printf("%d", prime(G, 5, 0));
    return 0;
}
