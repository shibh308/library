#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dynamicsegmenttree.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    Segtree<i64> seg(1e9, [](auto x, auto y){return x + y;}, 0);
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        seg.set(i, a);
    }
    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            seg.update(a, c);
        }
        else{
            cout << seg.get(a, c) << endl;
        }
    }
}

