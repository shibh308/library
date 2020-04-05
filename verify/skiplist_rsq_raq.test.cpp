#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"
#include "bits/stdc++.h"

using namespace std;


#include "../lib/classes/lazyskiplist.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    SkipList<i64,i64> slist([](auto x, auto y){return x + y;}, [](auto x, auto y, int z){return x + y * z;}, [](auto x, auto y){return x + y;}, 0, 0);
    for(int i = 0; i < n; ++i)
        slist.insert_index(i, 0);
    for(int i = 0; i < q; ++i){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            slist.update(--l, r, x);
        }else{
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", slist.get(--l, r));
        }
    }
}


