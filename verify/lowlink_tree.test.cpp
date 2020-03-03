#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/classes/lowlink.cpp"
#include "../lib/functions/twoedgeconnectedcomponents_tree.cpp"

signed main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> u(m), v(m);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; ++i){
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        edges[u[i]].push_back(v[i]);
        edges[v[i]].push_back(u[i]);
    }
    auto res = two_edge_connected_components_tree(edges);
    int k = res.group_cnt;
    vector<int> values(k, 0);
    for(int i = 0; i < n; ++i)
        values[res.group[i]] += a[i];

    auto& par = res.par;
    auto& childs = res.childs;
    vector<int> dp(k, 0);
    vector<unordered_map<int, int>> dp2(k);
    function<void(int)> f = [&](int x){
        int val = 0;
        for(auto y : childs[x]){
            f(y);
            chmax(val, dp[y]);
        }
        dp[x] = values[x] + val;
    };
    f(0);

    int ans = 0;
    function<void(int)> g = [&](int x){
        multiset<int> v{0, 0};
        for(auto y : childs[x]){
            v.insert(dp[y]);
            v.erase(v.begin());
            g(y);
        }
        chmax(ans, values[x] + *prev(v.end()) + *prev(v.end(), 2));
    };
    g(0);
    cout << ans << endl;

    return 0;
}
