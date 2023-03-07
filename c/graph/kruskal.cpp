#include "union_find.h"
#include <iostream>

struct Edge {
    int start;
    int end;
    int weight;
};

int kruskal(vector<Edge> edges) {
    int sum = 0;
    sort(edges.begin(), edges.end(), [] (const Edge& a, const Edge& b) {return a.weigth < b.weight;});
    UnionFind uf(N);
    for (int i = 0; i < n; i++) {
        if (uf.find(edges[i].start) != uf.find(edges[i].end)) {
            uf.unionify(edges[i].start, edges[i].end);
            sum += edges[i].weight;
        }
    }
    return sum;
}



