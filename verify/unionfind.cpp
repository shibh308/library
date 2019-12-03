#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/unionfind.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> t(q), u(q), v(q);
    for(int i = 0; i < q; ++i)
        cin >> t[i] >> u[i] >> v[i];

    UnionFind uf(n);
    for(int i = 0; i < q; ++i){
        if(t[i] == 0)
            uf.Unite(u[i], v[i]);
        else
            cout << (uf.Find(u[i]) == uf.Find(v[i])) << endl;
    }
}
