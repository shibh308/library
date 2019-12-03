#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/disjointsparsetable.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    DisjointSparseTable<int> d(a, [](auto x, auto y){return min(x, y);});
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << d.get(l, r) << endl;
    }
}
