#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B"
#include "bits/stdc++.h"


using namespace std;

using i64 = long long;

const i64 MOD = i64(1e9) + 7;
const i64 INF = i64(1e18) + 7;


#include "library/lib/classes/memorypool.cpp"
#include "library/lib/classes/zdd.cpp"


signed main(){
    int n, k;
    cin >> n >> k;
    vector<i64> v(n), w(n);
    for(int i = 0; i < n; ++i)
        cin >> v[i] >> w[i];
    auto f = [&](int p, int i, bool fl){
        if(fl)
            p += w[i];
        if(p > k)
            return make_pair(0, 0);
        if(i + 1 == n)
            return make_pair(0, int(p <= k));
        return make_pair(p, -1);
    };
    ZDD zdd;
    auto root = zdd.build<int>(f, 0);
    cout << zdd.linear_func_max(root, v) << endl;
}

