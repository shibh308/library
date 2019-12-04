#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/binaryindexedtree.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    BIT<i64> b(n);
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        b.add(i, a);
    }
    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            b.add(a, c);
        }
        else{
            cout << b.sum(a, c) << endl;
        }
    }
}

