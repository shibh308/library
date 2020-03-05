#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/eulertour.cpp"
#include "../lib/classes/segtree.cpp"

signed main(){
    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int p;
        cin >> p;
        edges[p].push_back(i);
        edges[i].push_back(p);
    }
    EulerTour et(edges);
    vector<i64> b(n);
    for(int i = 0; i < n; ++i)
        b[et.get_pos(i)] = a[i];
    Segtree<i64> seg(n, b, [](auto x, auto y){return x + y;}, 0LL);
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int u, x;
            cin >> u >> x;
            seg.update(et.get_pos(u), x);
        }
        else{
            int u;
            cin >> u;
            auto p = et.get_subtree(u);
            cout << seg.get(p.first, p.second) << endl;
        }
    }
}
