#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

#include "../lib/classes/avl.cpp"

signed main(){

    int n, q;
    scanf("%d%d", &n, &q);

    AVL<i64> avl([](auto x, auto y){return x + y;}, 0);
    auto root = avl.nil;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        root = avl.insert(root, i, a);
    }

    vector<int> t(q), a(q), c(q);
    for(int i = 0; i < q; ++i)
        cin >> t[i] >> a[i] >> c[i];
    for(int i = 0; i < q; ++i){
        if(t[i] == 0){
            i64 res = avl.getNode(root, a[i])->val;
            root = avl.erase(root, a[i], false);
            root = avl.insert(root, a[i], res + c[i]);
        }else{
            cout << avl.get(root, a[i], c[i]) << endl;
        }
    }

}
