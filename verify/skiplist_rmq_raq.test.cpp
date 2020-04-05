#include "bits/stdc++.h"

using namespace std;


#include "../lib/classes/lazyskiplist.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    SkipList<int,int> slist([](auto x, auto y){return min(x, y);}, [](auto x, auto y, int z){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    for(int i = 0; i < n; ++i)
        slist.insert_index(i, 0);
    for(int i = 0; i < q; ++i){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            slist.update(l, ++r, x);
        }else{
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", slist.get(l, ++r));
        }
    }
}

