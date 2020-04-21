#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I"
#include "bits/stdc++.h"


using namespace std;

using i64 = long long;


#include "../lib/classes/memorypool.cpp"
#include "../lib/classes/redblacktree_lazy.cpp"




signed main(){
    int n, q;
    scanf("%d%d", &n, &q);
    RedBlackTree<int, int> s([](auto x, auto y){return x + y;}, [](auto x, auto y, int z){return y == 100000 ? x : y * z;}, [](auto x, auto y){return y == 100000 ? x : y;}, 0, 100000);
    auto root = s.nil;
    for(int i = 0; i < n; ++i)
        root = s.insert(root, i, 0);
    for(int i = 0; i < q; ++i){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            root = s.range_update(root, l, r + 1, x);
        }
        else{
            int l, r;
            scanf("%d%d", &l, &r);
            auto res = s.range_get(root, l, r + 1);
            root = res.second;
            printf("%d\n", res.first);
        }
    }
}
