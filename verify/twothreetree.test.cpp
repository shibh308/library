#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

#include "../lib/classes/memorypool.cpp"
#include "../lib/classes/twothreetree.cpp"

signed main(){
    TwoThreeTree<int> bt;
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i){
        int t, x;
        cin >> t >> x;

        auto res = bt.lower_bound(x);

        if(t == 0){
            if(!(res.second && x == res.first))
                bt.insert(x);
            printf("%d\n", bt.size());
        }
        else if(t == 1){
            printf("%d\n", res.second && x == res.first);
        }
        else{
            if(res.second && x == res.first){
                bt.erase(x);
            }
        }
    }
}