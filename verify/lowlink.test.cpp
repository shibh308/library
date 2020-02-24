#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"
#include "bits/stdc++.h"
using namespace std;
using i64 = long long;
const i64 MOD = 1e9+7;
const i64 INF = 1e18+7;


template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}

struct UnionFind{
    vector<i64> par;
    i64 count;
    UnionFind(i64 n) : par(n, -1), count(0){}
    i64 Find(i64 x){return par[x] < 0 ? x : Find(par[x]);}
    i64 Size(i64 x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    bool Unite(i64 x, i64 y){
        x = Find(x);
        y = Find(y);
        if(x == y)
            return false;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return ++count;
    }
};


struct LowLink{
    vector<vector<int>>& edges;
    // 関節点
    vector<int> art;
    vector<pair<int,int>> bridge;

    vector<int> used, ord, low;
    int k;

    void dfs(int idx, int par){
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_art = false;
        int cnt = 0;
        for(auto& to : edges[idx]){
            if(ord[to] == -1){
                ++cnt;
                dfs(to, idx);
                low[idx] = min(low[idx], low[to]);
                is_art |= par != -1 && low[to] >= ord[idx];
                if(ord[idx] < low[to])
                    bridge.emplace_back(idx, to);
            }else if(to != par)
                low[idx] = min(low[idx], ord[to]);
        }
        is_art |= (par == -1 && cnt > 1);
        if(is_art)
            art.emplace_back(idx);
    }

    LowLink(vector<vector<int>>& edges) :
        edges(edges),
        ord(edges.size(), -1),
        low(edges.size(), 0),
        k(0)
    {
        for(int i = 0; i < edges.size(); ++i)
            if(ord[i] == -1)
                dfs(i, -1);
        for(auto& b : bridge)
            b = make_pair(min(b.first, b.second), max(b.first, b.second));
        sort(art.begin(), art.end());
        sort(bridge.begin(), bridge.end());
    }
};



signed main(){
    i64 n, m;
    cin >> n >> m;
    vector<i64> v(n);
    for(auto& x : v)
        cin >> x;
    vector<i64> s(m), t(m);
    vector<vector<int>> graph_edges(n);
    for(i64 i = 0; i < m; ++i){
        cin >> s[i] >> t[i];
        --s[i], --t[i];
        graph_edges[s[i]].emplace_back(t[i]);
        graph_edges[t[i]].emplace_back(s[i]);
    }
    LowLink ll(graph_edges);
    auto is_bridge = [&](int i, int j){
        if(i > j)
            swap(i, j);
        auto iter = lower_bound(ll.bridge.begin(), ll.bridge.end(), make_pair(i, j));
        if(iter != ll.bridge.end() && *iter == make_pair(i, j))
            return true;
        return false;
    };

    vector<i64> flag(n, false);
    vector<vector<i64>> ori_childs(n);

    function<void(i64)> f = [&](i64 x){
        for(auto& y : graph_edges[x]){
            if(flag[y])
                continue;
            flag[y] = true;
            if(is_bridge(x, y))
                ori_childs[x].emplace_back(y);
            f(y);
        }
    };

    flag[0] = true;
    f(0);

    UnionFind uf(n);
    for(int i = 0; i < m; ++i)
        if(!is_bridge(s[i], t[i]))
            uf.Unite(s[i], t[i]);

    vector<i64> union_par;
    for(i64 i = 0; i < n; ++i)
        if(uf.Find(i) == i)
            union_par.emplace_back(i);
    i64 k = union_par.size();
    auto getidx = [&](int i){
        int id = uf.Find(i);
        return distance(union_par.begin(), lower_bound(union_par.begin(), union_par.end(), id));
    };
    vector<i64> val(k, 0);
    for(i64 i = 0; i < n; ++i)
        val[getidx(i)] += v[i];

    vector<vector<i64>> childs(k);
    for(i64 x = 0; x < n; ++x)
        for(auto& y : ori_childs[x])
            childs[getidx(x)].emplace_back(getidx(y));

    i64 ans = 0;
    function<i64(i64)> g = [&](i64 x){
        vector<i64> values;
        for(auto& y : childs[x])
            values.emplace_back(g(y));
        sort(values.begin(), values.end(), greater<i64>());
        i64 res = val[x];
        for(i64 i = 0; i < min(2LL, i64(values.size())); ++i)
            res += values[i];
        chmax(ans, res);
        return (values.size() ? values[0] : 0) + val[x];
    };
    g(0);
    cout << ans << endl;
}

