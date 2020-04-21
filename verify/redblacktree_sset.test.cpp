#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/memorypool.cpp"
#include "../lib/classes/redblacktree_sset.cpp"


signed main(){
    int q;
    scanf("%d", &q);
    RedBlackTree<int> s;
    auto root = s.nil;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            int idx = s.lower_bound(root, x);
            if(idx == s[root].siz || s[s.access(root, idx)].key != x)
                root = s.insert(root, x);
            printf("%d\n", s.get(root).siz);
        }
        else if(t == 2){
            root = s.erase_key(root, x);
        }
        else{
            int idx = s.lower_bound(root, x);
            printf("%d\n", idx != s[root].siz && s[s.access(root, idx)].key == x);
        }
    }
}
