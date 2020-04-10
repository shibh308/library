#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/splaytree_sset.cpp"


signed main(){
    int q;
    scanf("%d", &q);
    SplayTree<int> s;
    auto root = s.nil;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            root = s.lower_bound(root, x).first;
            if(root == s.nil || root->val != x)
                root = s.insert(root, x).first;
            printf("%d\n", root->size);
        }
        else if(t == 2){
            root = s.erase(root, x).first;
        }
        else{
            auto res = s.lower_bound(root, x);
            root = res.first;
            printf("%d\n", res.second && root->val == x);
        }
    }
}
