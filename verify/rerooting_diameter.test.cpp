#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

template <typename T>
// T f(T, T): 子の累積に使うもの 直径ならf(x, y): max(x, y)
// T g(T, int): 子の累積を元に適用する際に使うもの 直径ならg(x, idx): x + 1
vector<T> rerooting(vector<vector<int>>& edges, vector<T> v, function<T(T, T)> f, function<T(T, int)> g, T op){
    int n = edges.size();
    vector<int> visit(n, 0);
    vector<T> dp1(v), dp2(n);
    vector<vector<int>> childs(n);
    vector<vector<T>> child_val(n), child_l(n), child_r(n);
    function<void(int)> f1 = [&](int x){
        visit[x] = true;
        T res = op;
        for(auto y : edges[x]){
            if(visit[y])
                continue;
            f1(y);
            childs[x].push_back(y);
            child_val[x].push_back(dp1[y]);
            res = f(res, dp1[y]);
        }
        dp1[x] = g(res, x);
        child_l[x].push_back(op);
        child_r[x].push_back(op);
        for(int i = 0; i < childs[x].size(); ++i){
            child_l[x].push_back(f(child_l[x].back(), child_val[x][i]));
            child_r[x].push_back(f(child_r[x].back(), child_val[x][childs[x].size() - i - 1]));
        }
    };
    f1(0);
    function<void(int, T)> f2 = [&](int x, T par_val){
        T res = par_val;
        for(int i = 0; i < childs[x].size(); ++i){
            int y = childs[x][i];
            auto p = f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1]));
            T val = g(f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1])), y);
            res = f(res, dp1[y]);
            f2(y, val);
        }
        dp2[x] = g(res, x);
    };
    f2(0, op);
    return dp2;
};

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