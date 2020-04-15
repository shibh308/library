#define PROBLEM "https://yukicoder.me/problems/1937"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/bitvector.cpp"
#include "../lib/classes/waveletmatrix.cpp"


signed main(){

    int n;
    cin >> n;
    vector<i64> a(n);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        a[i] += 2000000000;
    }
    vector<i64> l(n), r(n);
    for(int i = 0; i < n; ++i){
        cin >> l[i] >> r[i];
        l[i] = a[i] - l[i];
        r[i] = a[i] + r[i];
    }

    WaveletMatrix<i64, 35> l_wm(l);
    WaveletMatrix<i64, 35> r_wm(r);

    i64 ans = 0;
    for(int i = 0; i < n; ++i){
        int l_idx = distance(a.begin(), lower_bound(a.begin(), a.end(), l[i]));
        int r_idx = distance(a.begin(), upper_bound(a.begin(), a.end(), r[i])) - 1;
        ans += r_wm.count_range(l_idx, i, a[i], (1LL << 34));
        ans += l_wm.count_range(i + 1, r_idx + 1, 0, a[i] + 1);
    }
    cout << (ans >> 1) << endl;

}
