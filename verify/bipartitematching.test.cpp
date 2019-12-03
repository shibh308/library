#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dinic.cpp"


signed main() {

    int l, r, m;
    cin >> l >> r >> m;
    Dinic<int> d(l + r + 2);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        d.add(a, l + b, 1);
    }
    for(int i = 0; i < l; ++i)
        d.add(l + r, i, 1);
    for(int i = 0; i < r; ++i)
        d.add(l + i, l + r + 1, 1);
    cout << d.solve(l + r, l + r + 1) << endl;
    for(int i = 0; i < l + r; ++i)
        for(auto& e : d.edges[i]){
            if(e.to >= l + r || i >= e.to)
                continue;
            if(e.cap == 0)
                cout << i << " " << e.to - l << endl;
        }
}

