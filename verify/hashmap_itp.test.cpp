#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/hashmap.cpp"



signed main(){
    int q;
    scanf("%d", &q);
    HashMap<int,int> h;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            h.add(x, 1);
            printf("%lu\n", h.n);
        }
        else if(t == 2){
            h.erase(x);
        }
        else{
            printf("%d\n", h.find(x).first);
        }
    }
}
