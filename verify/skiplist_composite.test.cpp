#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;


#include "../lib/classes/skiplist.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    vector<i64> a(n), b(n);
    for(int i = 0; i < n; ++i)
        scanf("%lld%lld", &a[i], &b[i]);
    auto f = [&](auto p1, auto p2){
        i64 a = p1.first;
        i64 b = p1.second;
        i64 c = p2.first;
        i64 d = p2.second;
        return make_pair((c * a) % MOD, (c * b + d) % MOD);
    };
    SkipList<pair<i64,i64>> slist(f, make_pair(1LL, 0LL));

    for(int i = 0; i < n; ++i)
        slist.insert_index(i, make_pair(a[i], b[i]));
    for(int i = 0; i < q; ++i){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int p;
            i64 c, d;
            scanf("%d%lld%lld", &p, &c, &d);
            slist.erase_index(p);
            slist.insert_index(p, make_pair(c, d));
        }
        else{
            int l, r;
            i64 x;
            scanf("%d%d%lld", &l, &r, &x);
            auto p = slist.get(l, r);
            printf("%lld\n", (p.first * x + p.second) % MOD);
        }
    }
}

