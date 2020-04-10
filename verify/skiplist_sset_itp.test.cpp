#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/skiplist_sset.cpp"


signed main(){
    int q;
    scanf("%d", &q);
    SSet<int> s;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            auto ptr = s.lower_bound(x);
            if(ptr == s.back || ptr->val != x)
                s.insert(x);
            printf("%d\n", s.size());
        }
        else if(t == 2){
            s.erase_key(x);
        }
        else{
            auto ptr = s.lower_bound(x);
            printf("%d\n", ptr != s.back && ptr->val == x);
        }
    }
}
