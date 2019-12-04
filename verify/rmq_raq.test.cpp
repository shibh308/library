#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/lazysegtree.cpp"


signed main() {
    int n, q;
    cin >> n >> q;
    Segtree<int,int> seg(n, 0, [](auto x, auto y){return min(x, y);}, [](auto x, auto y, int){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    for(int i = 0; i < q; ++i){
        int ty;
        cin >> ty;
        if(ty == 0){
            int s, t, x;
            cin >> s >> t >> x;
            seg.update(s, ++t, x);
        }
        else{
            int s, t;
            cin >> s >> t;
            cout << seg.get(s, ++t) << endl;
        };
    }
}
