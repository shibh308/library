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
            root = s.insert(root, s)
            printf("%d\n", root->val);
        }
        else if(t == 2){
            root = s.erase(root, x);
        }
        else{
            auto res = s.lower_bound(s);
            root = res.first;
            printf("%d\n", res.second && root->val == key);
        }
    }
}
