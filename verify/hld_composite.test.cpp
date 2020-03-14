#define PROBLEM "https://judge.yosupo.jp/problem/point_set_path_composite"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}

#include "../lib/classes/heavylightdecomposition.cpp"
#include "../lib/classes/modint.cpp"
#include "../lib/classes/segtree.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    vector<vector<int>> edges(n);
    for(int i = 0; i < n - 1; ++i){
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    HeavyLightDecomposition hld(edges);
    vector<pair<mint, mint>> v(n);
    for(int i = 0; i < n; ++i)
        v[hld.get_idx(i)] = make_pair(a[i], b[i]);
    auto func = [](auto p1, auto p2){
        mint a = p1.first;
        mint b = p1.second;
        mint c = p2.first;
        mint d = p2.second;
        return make_pair(c * a, c * b + d);
    };

    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1, 0));
    Segtree<pair<mint,mint>> seg_rev(n, v, [&func](auto x, auto y){return func(y, x);}, make_pair(1, 0));
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int p, c, d;
            cin >> p >> c >> d;
            seg.set(hld.get_idx(p), make_pair(c, d));
            seg_rev.set(hld.get_idx(p), make_pair(c, d));
        }
        else{
            int u, v, x;
            cin >> u >> v >> x;
            auto res = hld.two_point_path(u, v);
            pair<mint,mint> l(1, 0), r(1, 0);
            for(auto p : res.first){
                l = func(l, seg_rev.get(p.first, p.second));
            }
            for(auto p : res.second){
                r = func(seg.get(p.first, p.second), r);
            }
            auto ret = func(l, r);
            cout << ret.first * x + ret.second << endl;
        }
    }
}

