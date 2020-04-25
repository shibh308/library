#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "bits/stdc++.h"


using namespace std;

using i64 = long long;


#include "./lib/classes/memorypool.cpp"
#include "./lib/classes/dynamicbitvector.cpp"
#include "./lib/classes/dynamicwaveletmatrix.cpp"

signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    WaveletMatrix<int, 31> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;
        cout << wm.kth_min(l, r, k) << endl;
    }
}

