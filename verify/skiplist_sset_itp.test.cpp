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
            s.insert(x);
            printf("%d\n", s.size());
        }
        else if(t == 2){
            s.erase(x);
        }
        else{
            auto ptr = s.lower_bound(s);
            printf("%d\n", ptr != s.back && ptr->val == key);
        }
    }
}
