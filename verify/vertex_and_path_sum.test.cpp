#define PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../../library/lib/classes/segtree.cpp"
#include "../../library/lib/classes/heavylightdecomposition.cpp"


const i64 MOD = 1e9 + 7;
const i64 INF = i64(1e18) + 7;


template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}



signed main(){

    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for(auto& x : a)
        cin >> x;
    vector<int> u(n - 1), v(n - 1);
    for(int i = 0; i < n - 1; ++i)
        cin >> u[i] >> v[i];
    vector<tuple<int,int,int>> querys;
    for(int i = 0; i < q; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        querys.emplace_back(a, b, c);
    }
    Segtree<i64> seg(n, a, [](auto x, auto y){return x + y;}, 0L);
    vector<vector<int>> edges(n);
    for(int i = 0; i < n - 1; ++i) {
        edges[u[i]].emplace_back(v[i]);
        edges[v[i]].emplace_back(u[i]);
    }
    HeavyLightDecomposition hld(edges);

    for(auto& query : querys){
        int a, b, c;
        tie(a, b, c) = query;
        if(a == 0){
            seg.update(hld.in[b], c);
        }else{
            vector<pair<int,int>> l, r;
            tie(l, r) = hld.two_point_path(b, c);
            i64 sum = 0;
            for(auto& p : l){
                sum += seg.get(p.first, p.second);
            }
            for(auto& p : r){
                sum += seg.get(p.first, p.second);
            }
            cout << sum << endl;
        }
    }

    return 0;
}
