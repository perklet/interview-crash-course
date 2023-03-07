#include <stdio.h>
#include <stdlib.h>

// 对于使用临街矩阵表示的图dist[n][n]，运行floyd算法后，更新每个坐标为两点之间的最近距离
int floyd(int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]); // dist[i][j]为i,j之间最短距离
}
