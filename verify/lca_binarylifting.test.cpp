#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/binarylifting.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    BinaryLifting tree(edges);
    for(int i = 0; i < q; ++i){
        int u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << endl;
    }
}

