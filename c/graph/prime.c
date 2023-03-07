#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define N 5

int prime(int G[][N], int n, int start) {

    // path sum
    int sum = 0;

    // visit table
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    int cur = start;
    visited[cur] = true;

    // min dist to current tree
    int dist[n];

    // init dist table
    for (int i = 0; i < n; i++)
        dist[i] = G[cur][i];

    // for other n-1 nodes
    for (int i = 1; i < n; i++) {
        int min_cost = INT_MAX;
        int next;
        // add nearest node to tree
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_cost) {
                min_cost = dist[j];
                next = j;
            }
        }

        // set next visited and add path sum
        visited[next] = true;
        sum += min_cost;

        // update dist table by new element
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] > G[next][j])
                dist[j] = G[next][j];
        }
    }
    return sum;
}

int main() {
    int n = 5;
    int G[5][5] = {{1, 1, 1, 1, 1}, {1,1,1,1,1}, {1,1,1,1,1}, {1,1,1,1,1},{1,1,1,1,1}};
    printf("%d", prime(G, 5, 0));
    return 0;
}
