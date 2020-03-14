#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/heavylightdecomposition.cpp"
#include "../lib/classes/segtree.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    HeavyLightDecomposition hld(edges);
    Segtree<i64> seg(n, 0L, [](auto x, auto y){return x + y;}, 0L);
    for(int i = 0; i < n; ++i)
        seg.set(hld.get_idx(i), a[i]);
    for(int i = 0; i < q; ++i){
        int t;
        cin >> t;
        if(t == 0){
            int u, x;
            cin >> u >> x;
            seg.update(hld.in[u], x);
        }
        else{
            int u;
            cin >> u;
            auto v = hld.subtree(u);
            cout << seg.get(v.first, v.second) << endl;
        }
    }
}

