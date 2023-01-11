#include "bits/stdc++.h" // Leonardo Su
#define ALL(x) x.begin(),x.end()
using namespace std;
struct UnionFind {
    vector<int> parent, level;
    UnionFind(int numberNodes) {
        parent.resize(numberNodes + 1);
        iota(ALL(parent), 0);
        level.resize(numberNodes + 1, 0);
    }

    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void join(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(level[x] < level[y]) swap(x,y);
        if(level[x] == level[y]) level[x]++;
        parent[y] = x;
    }
};

int main() {

}