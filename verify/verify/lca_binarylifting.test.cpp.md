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


# :heavy_check_mark: verify/lca_binarylifting.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/lca_binarylifting.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-14 13:51:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/lca">https://judge.yosupo.jp/problem/lca</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/binarylifting.cpp.html">lib/classes/binarylifting.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/binarylifting.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    BinaryLifting tree(edges);
    for(int i = 0; i < q; ++i){
        int u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << endl;
    }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/lca_binarylifting.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#line 1 "verify/../lib/classes/binarylifting.cpp"
struct BinaryLifting{
    int n;
    vector<vector<int>> next;
    vector<int> par;
    vector<vector<int>> childs;
    vector<int> depth;

    BinaryLifting(vector<vector<int>>& edges, int root = 0) : n(edges.size()), depth(n, -1), par(n, -1), childs(n){
        function<void(int)> dfs = [&](int x){
            for(auto y : edges[x])
                if(depth[y] == -1){
                    depth[y] = depth[x] + 1;
                    par[y] = x;
                    childs[x].push_back(y);
                    dfs(y);
                }
        };
        depth[root] = 0;
        dfs(0);

        next.push_back(move(par));
        for(int k = 0;; ++k){
            bool fl = false;
            next.emplace_back(n, -1);
            for(int i = 0; i < n; ++i){
                next[k + 1][i] = (next[k][i] == -1 ? -1 : next[k][next[k][i]]);
                if(next[k + 1][i] != -1)
                    fl = true;
            }
            if(!fl)
                break;
        }
    }
    // kth_next(x, 0) => x
    int kth_next(int x, int k){
        for(int i = 0; i < next.size() && k; ++i){
            if(k & (1 << i)){
                x = next[i][x];
                if(x == -1)
                    break;
            }
        }
        return x;
    }

    int lca(int x, int y){
        int min_depth = min(depth[x], depth[y]);
        x = kth_next(x, depth[x] - min_depth);
        y = kth_next(y, depth[y] - min_depth);
        if(x == y)
            return x;
        for(int i = next.size() - 1; i >= 0; --i)
            if(next[i][x] != next[i][y]){
                x = next[i][x];
                y = next[i][y];
            }
        return next[0][x];
    }
};

#line 9 "verify/lca_binarylifting.test.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    BinaryLifting tree(edges);
    for(int i = 0; i < q; ++i){
        int u, v;
        cin >> u >> v;
        cout << tree.lca(u, v) << endl;
    }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

