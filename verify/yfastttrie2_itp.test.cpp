#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/hashmap.cpp"
#include "../lib/classes/splaytree_sset.cpp"
#include "../lib/classes/xfasttrie_yft.cpp"
#include "../lib/classes/yfasttrie2.cpp"


signed main(){
    int q;
    scanf("%d", &q);
    YFastTrie2<int, 31> s;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            auto ptr = s.lower_bound(x);
            if(ptr == s.splay.nil || ptr->val != x)
                s.insert(x);
            printf("%d\n", s.n - 1);
        }
        else if(t == 2){
            s.erase(x);
        }
        else{
            auto ptr = s.lower_bound(x);
            printf("%d\n", ptr != s.splay.nil && ptr->val == x);
        }
    }
}
