#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075"
#include "bits/stdc++.h"

using namespace std;

#include "../lib/functions/scc.cpp"
#include "../lib/functions/scc_dag.cpp"

using i64 = long long;

const i64 MOD = 1e9 + 7;


template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


signed main(){
    int n, m;
    cin >> n >> m;
    vector<int> x(n), y(n), z(n);
    vector<vector<int>> v(n, vector<int>(8, 0));
    for(int i = 0; i < n; ++i){
        cin >> x[i] >> y[i] >> z[i];
        for(int j = 0; j < 8; ++j){
            v[i][j] += x[i] * (j & 1 ? -1 : 1);
            v[i][j] += y[i] * (j & 2 ? -1 : 1);
            v[i][j] += z[i] * (j & 4 ? -1 : 1);
        }
    }
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; ++i){
        int p, q;
        cin >> p >> q;
        --p, --q;
        edges[q].push_back(p);
    }
    Result res = scc_dag(edges);
    int k = res.dag_size;
    vector<vector<int>> dp(k, vector<int>(8, -MOD));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 8; ++j)
            chmax(dp[res.elements[i]][j], v[i][j]);

    for(auto i : res.tps_order){
        for(int j = 0; j < 8; ++j){
            for(auto nex : res.dag_graph[i]){
                chmax(dp[nex][j], dp[i][j]);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        int dist = 0;
        for(int j = 0; j < 8; ++j){
            chmax(dist, dp[res.elements[i]][j] - v[i][j]);
        }
        cout << dist << endl;
    }
}
