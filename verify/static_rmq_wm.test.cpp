#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/waveletmatrix.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    WaveletMatrix<int> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << wm.kth_min(l, r, 0) << endl;
    }
}
