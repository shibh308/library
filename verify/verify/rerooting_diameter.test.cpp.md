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


# :heavy_check_mark: verify/rerooting_diameter.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/rerooting_diameter.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-30 02:03:55+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 170, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

