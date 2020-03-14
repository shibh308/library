#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

#include "../lib/classes/modint.cpp"
#include "../lib/classes/segtree.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    vector<pair<mint,mint>> v(n);
    for(int i = 0; i < n; ++i)
        v[i] = make_pair(a[i], b[i]);
    auto func = [](auto p1, auto p2){
        mint a = p1.first;
        mint b = p1.second;
        mint c = p2.first;
        mint d = p2.second;
        return make_pair(c * a, c * b + d);
    };
    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1, 0));
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int p, c, d;
            cin >> p >> c >> d;
            seg.set(p, make_pair(c, d));
        }
        else{
            int l, r, x;
            cin >> l >> r >> x;
            auto ret = seg.get(l, r);
            cout << ret.first * x + ret.second << endl;
        }
    }
    return 0;
}

