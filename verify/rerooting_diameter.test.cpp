#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/functions/rerooting.cpp"


signed main(){
    int n;
    cin >> n;
    vector<int> a(n - 1), b(n - 1), c(n - 1);
    vector<vector<int>> edges(2 * n - 1);
    vector<int> v(2 * n - 1, 0);
    for(int i = 0; i < n - 1; ++i){
        cin >> a[i] >> b[i] >> c[i];
        edges[a[i]].emplace_back(n + i);
        edges[n + i].emplace_back(b[i]);
        edges[b[i]].emplace_back(n + i);
        edges[n + i].emplace_back(a[i]);
        v[i + n] = c[i];
    }

    function<int(int,int)> f = [&](int x, int y){return max(x, y);};
    function<int(int,int)> g = [&](int x, int idx){return x + v[idx];};

    auto res = rerooting(edges, v, f, g, 0);
    cout << *max_element(res.begin(), next(res.begin(), n)) << endl;
}