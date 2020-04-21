#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/memorypool.cpp"
#include "../lib/classes/redblacktree.cpp"


signed main(){
    RedBlackTree<i64> rb;
    int n, q;
    cin >> n >> q;
    auto root = rb.nil;
    vector<i64> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    root = rb.build(a);
    for(int i = 0; i < q; ++i){
        int t, k, x;
        cin >> t >> k >> x;
        if(t == 0){
            rb.set(root, k, x, [](auto x, auto y){return x + y;});
        }
        else{
            auto res = rb.range_get(root, k, x);
            root = res.second;
            printf("%lld\n", res.first);
        }
    }
}