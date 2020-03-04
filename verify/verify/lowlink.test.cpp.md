---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: verify/lowlink.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/lowlink.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 09:29:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 182, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 77, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

