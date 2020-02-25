#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

#include "../lib/classes/avl.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    AVL<i64> avl([](auto x, auto y){return x + y;}, 0);
    auto root = avl.nil;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        root = avl.insert(root, i, a);
    }

    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            avl.update(root, a, c);
        }
        else{
            cout << avl.get(root, a, c) << endl;
        }
    }

}

