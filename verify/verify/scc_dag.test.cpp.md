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


# :heavy_check_mark: verify/scc_dag.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/scc_dag.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-25 06:59:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/functions/scc.cpp.html">lib/functions/scc.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/functions/scc_dag.cpp.html">lib/functions/scc_dag.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075"
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

const i64 MOD = 1e9 + 7;

#include "../lib/functions/scc.cpp"
#include "../lib/functions/scc_dag.cpp"


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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 399, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 258, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

