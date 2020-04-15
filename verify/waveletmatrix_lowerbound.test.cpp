#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/bitvector.cpp"
#include "../lib/classes/waveletmatrix.cpp"


signed main(){

    int n, q;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> q;
    WaveletMatrix<int, 31> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;
        auto res = wm.predecessor(l, r + 1, k);
        auto res2 = wm.successor(l, r + 1, k);
        cout << min(res.second ? res.first - k : INT_MAX, res2.second ? k - res2.first : INT_MAX) << endl;
    }
}

